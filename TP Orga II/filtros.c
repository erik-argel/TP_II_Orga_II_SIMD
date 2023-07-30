#include "filtros.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// intel simd
#if defined(__SSE2__)
#include <emmintrin.h>
#endif

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

extern void asm_blend(char* img1, char* img2, int tamanio);

FILTRO SEPIA = { 
	.393, .760, .189,
	.349, .686, .168,
	.272, .534, .131
};

/******************************************************************************/

void filtro (BMPDATA *bmpData, FILTRO filtro) {

	for (int i=0; i<cantPixels(bmpData); i++) {

		unsigned char r = bmpData->red[i];
		unsigned char g = bmpData->green[i];
		unsigned char b = bmpData->blue[i];
		bmpData->red[i]   = min (r * filtro.RR + g * filtro.RG + b * filtro.RB, 255);
		bmpData->green[i] = min (r * filtro.GR + g * filtro.GG + b * filtro.GB, 255);
		bmpData->blue[i]  = min (r * filtro.BR + g * filtro.BG + b * filtro.BB, 255);
	}
}

/******************************************************************************/

void blancoYNegro (BMPDATA *bmpData) {
	
	for (int i=0; i<cantPixels(bmpData); i++) {
	
		unsigned char y = bmpData->red[i] * 0.11448f + bmpData->green[i] * 0.58661f + bmpData->blue[i] * 0.29891f;
		bmpData->red[i]   = y;
		bmpData->green[i] = y;
		bmpData->blue[i]  = y;
	}	
}

/******************************************************************************/

void aclarar(unsigned char* red, unsigned char* green, unsigned char* blue, int n){
		unsigned char r = *red;
		unsigned char g = *green;
		unsigned char b = *blue;
		*red = min (r + n, 255);
		*green = min (g + n, 255);
		*blue = min (b + n, 255);
}

/******************************************************************************/

void aclararimagen (BMPDATA *bmpData, int nivel) {
	for (int i=0; i<cantPixels(bmpData); i++) {
		aclarar(&bmpData->red[i],&bmpData->green[i],&bmpData->blue[i],nivel);
	}	
}
/******************************************************************************/

void corromperC(unsigned char *red, unsigned char *green, unsigned char *blue, int c) {
		unsigned char r = *red;
		unsigned char g = *green;
		unsigned char b = *blue;
		*red   = c;
		*green = c;
		*blue  = c;
}

void corromper(BMPDATA *bmpData) {
	srand(time(NULL));
	for (int i = 0; i < cantPixels(bmpData); i++) {

		unsigned char *red 		= &bmpData->red[i];
		unsigned char *green 	= &bmpData->green[i];
		unsigned char *blue 	= &bmpData->blue[i];

		int r = rand() %10;
		if(r == 1){
			corromperC(red, green, blue, 0);
		}
		if(r == 2){
			corromperC(red, green, blue, 255);
		}
	}	
}

/******************************************************************************/

unsigned char mediana (unsigned char *histo, int imediana) {

	int k, aux=0;
	for (k=0; k<255 && aux<=imediana; k++)
		aux += histo[k];

	return k;
}

/******************************************************************************/

int cantPixels(BMPDATA *bmpData) {

	return bmpData->infoHeader.biWidth * bmpData->infoHeader.biHeight;
}
	

void multiplyBlend (BMPDATA *bmpData, BMPDATA *bmpData2) {
	for (int i=0; i<cantPixels(bmpData); i++) {
		if (bmpData->red[i] > 127.5 ){
			bmpData->red[i] = bmpData2->red[i]+(255-bmpData2->red[i])*(((bmpData->red[i]-127.5)/127.5)*(0.5-abs(bmpData2->red[i])/255));
		}else{
			bmpData->red[i]= bmpData2->red[i]-bmpData2->red[i]*(((127.5-bmpData->red[i])/127.5)*(0.5-abs(bmpData2->red[i])/255));
		}
		if (bmpData->blue[i] >127.5){
			bmpData->blue[i] = bmpData2->blue[i]+(255-bmpData2->blue[i])*(((bmpData->blue[i]-127.5)/127.5)*(0.5-abs(bmpData2->blue[i])/255));
		}else{
			bmpData->blue[i]= bmpData2->blue[i]-bmpData2->blue[i]*(((127.5-bmpData->blue[i])/127.5)*(0.5-abs(bmpData2->blue[i])/255));
		}
		if (bmpData->green[i] > 127.5){
			bmpData->green[i] = bmpData2->green[i]+(255-bmpData2->green[i])*(((bmpData->green[i]-127.5)/127.5)*(0.5-abs(bmpData2->green[i])/255));
		}else{
			bmpData->green[i]= bmpData2->green[i]-bmpData2->green[i]*(((127.5-bmpData->green[i])/127.5)*(0.5-abs(bmpData2->green[i])/255));
		}
	} 
}

/******************************************************************************/

void pixelPorPixel(unsigned char *red, unsigned char *green, unsigned char *blue, int ired, int igreen, int iblue) 
{
		*red   = ired;
		*green = igreen;
		*blue  = iblue;
}

void mfilterPixel (int pixel, BMPDATA *bmpData, int ventana, int x, int y)
{	
	int alto	= bmpData->infoHeader.biHeight;
	int ancho 	= bmpData->infoHeader.biWidth;

	int cantP = cantPixels(bmpData);

	/*creo dos arreglos para guardar los valores de la ventana, uno con la suma los valores 
	RGB de cada pixel y otro con el indice de cada pixel en la imagen*/

	int ventanaValores[((ventana * 2) + 1) * ((ventana * 2) + 1)];
	int ventanaIndices[((ventana * 2) + 1) * ((ventana * 2) + 1)];
	
	/*reviso que los valors no se exedan del limite*/
	/*no se extiende la imagen cuando se llega al borde, solo se achica la ventanta */
	/*estos indices se usan para recorrer la ventana del pixel actual*/
	
	int inicioY = max(y - ventana , 0);
	inicioY		= min(inicioY, alto);
	int finY	= min(y + ventana, alto);
	finY		= max(finY, 0);

	int inicioX = max(x - ventana, 0);
	inicioX		= min(inicioX, ancho);
	int finX	= min(x + ventana, ancho);
	finX		= max(finX, 0);

	/*lleno los arreglos con los pixeles correspondientes a la ventana*/
	int k = 0;

	for (int j = inicioY; j <= finY; j++)
	{
		for (int i = inicioX; i <=  finX; i++)
		{	
			int indice = (j * ancho) + i;

			if( indice < cantP)
			{
				ventanaIndices[k] 	= indice;
				ventanaValores[k]	= bmpData->red[indice] + bmpData->green[indice] + bmpData->blue[indice];
			}
			
			k++;
		}
	}

	/*Ordeno ambos arreglos al mismo tiempo*/

	for (int j = 0; j < (((ventana * 2) + 1) * ((ventana * 2) + 1) + 1) / 2 ; j++)
	{
		int min = j;
		for (int l = j + 1; l < ((ventana * 2) + 1) * ((ventana * 2) + 1); l++)
		{
			if (ventanaValores[l] < ventanaValores [min])
			{
				min = l;
			}
		}
		int valTemp = ventanaValores[j];
		int indTemp = ventanaIndices[j];
		ventanaValores[j] = ventanaValores[min];
		ventanaIndices[j] = ventanaIndices[min];
		ventanaValores[min] = valTemp;
		ventanaIndices[min] = indTemp;
	}

	/*reemplazo el pixel en la imagen por el valor medio del arreglo*/
	int indiceMedia = ventanaIndices[((((ventana * 2) + 1) * ((ventana * 2) + 1)) - 1) / 2];

	if( indiceMedia < cantP && pixel < cantP)
	{
		int redC 	= bmpData->red[indiceMedia];
		int greenC 	= bmpData->green[indiceMedia];
		int blueC 	= bmpData->blue[indiceMedia];

		unsigned char *red 		= &bmpData->red[pixel];
		unsigned char *green 	= &bmpData->green[pixel];
		unsigned char *blue 	= &bmpData->blue[pixel];

	pixelPorPixel(red, green, blue, redC, greenC, blueC);
	}


}

void medianFilter(BMPDATA *bmpData, int ventana)
{	
	int alto	= bmpData->infoHeader.biHeight;
	int ancho 	= bmpData->infoHeader.biWidth;
	/*
	printf("alto: %d ", alto);
	printf("ancho: %d", ancho);
	*/
	for (int y = 0; y < alto; y++)
	{	for (int x = 0; x < ancho; x++)
		{		
			mfilterPixel((y * ancho) + x, bmpData, ventana, x, y);
		}
	} 
}

/******************************************************************************/

void blendBmpAsm (BMPDATA *bmpData1, BMPDATA *bmpData2)
{	
	asm_blend(bmpData1->red, bmpData2->red, cantPixels(bmpData1) - 4);
	asm_blend(bmpData1->blue, bmpData2->blue, cantPixels(bmpData1) - 4);
	asm_blend(bmpData1->green, bmpData2->green, cantPixels(bmpData1) - 4);
}	

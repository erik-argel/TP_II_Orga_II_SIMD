#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "lectorBmp.h"
#include "filtros.h"


/*
 * Funciones en asembler
 */
//extern void blendAsm (char *, char *, char *, int, int, int, int);


// DOC_HELP



extern int asmPrint
(char * msg, int lenght);

int asm_Print(char * msg){
  return asmPrint(msg,strlen(msg));
}
/******************************************************************************/

/******************************************************************************/
/*******************************ParseInt**********************************/

int parseInt(char* chars)
{
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++)
    {
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}

int powInt(int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}
/*****************************Fin ParseInt*************************************/
/******************************************************************************/

int main (int argc, char* argv[]) {
	asm_Print("Organización del Computador 2.\nTrabajo Práctico Nro. 2\nPrograma para procesamiento de imágenes BMP.\n");
	int resolucion = 1080;
	BMPDATA bmpData;
	BMPDATA bmpData2;
	int i;
	int metodo;
	unsigned char* nombreImagen;
	int nivel;
	int sizeVent;
	unsigned char* nombreImagen2;

	if(argc<2) {
    	printf("No igreso que funcion desea realizar.\n");
    	exit(1);
	}
	/*printf("Ejecutando con parametros: ");*/
	for (i=1 ; i<argc; i++){
		/*printf("%s ", argv[i]);*/
		//if(i==1) metodo = (int) *argv[i] - '0';
		if(i==1) metodo = parseInt(argv[i]);	
		if(i==2) nombreImagen = argv[i];
		if(i==3){
			if(metodo==2)nivel = parseInt(argv[i]);
			if(metodo==4)sizeVent = parseInt(argv[i]);
			if(metodo==5||metodo==6)nombreImagen2 = argv[i];
		}
	}
	printf("Funcion: %i ", metodo);
	printf("\n");
	printf("NombreImagen: %s ", nombreImagen);
	printf("\n");
	printf("Nivel: %i ", nivel);
	printf("\n");
	printf("Tamaño ventana: %i ", sizeVent);
	printf("\n");
	if(metodo==5)printf("NombreImagen: %s ", nombreImagen2);
	// carga el archivo bmp
	if (loadBmpFile (nombreImagen, &bmpData) != 0) {

		printf ("Error al leer el archivo %s\n\n", nombreImagen);
		return 1;
	}
	if(metodo==5||metodo==6){
		if (loadBmpFile (nombreImagen2, &bmpData2) != 0) {
			printf ("Error al leer el archivo %s\n\n", nombreImagen2);
			return 1;
		}
	}
	clock_t start, end;
	
	// comienza a medir el tiempo
	start = clock();

	// tonos de grises
	//blancoYNegro (&bmpData);
	//aclararimagen (&bmpData, 10);
	if(metodo==1)blancoYNegro (&bmpData);
	if(metodo==2)aclararimagen (&bmpData, nivel);
	if(metodo==3)corromper (&bmpData);
	if(metodo==4)medianFilter (&bmpData, sizeVent);
	if(metodo==5)multiplyBlend (&bmpData,&bmpData2);
	if(metodo==6)blendBmpAsm (&bmpData, &bmpData2);
	
	end = clock();
	FILE *out = fopen("results.csv", "a");  
	int tiempo = end-start;
	fprintf(out, "%d %s %d", resolucion, " tiempo: ", tiempo );
  	fclose(out); 

	// imprime tiempo
	
	printf("\nTiempo de proceso: %ld ticks.\n\n", end-start);

	if (saveBmpFile (nombreImagen, &bmpData) != 0)
		asm_Print("Error al grabar el archivo!");
	if(metodo==5||metodo==6){
		if (saveBmpFile (nombreImagen2, &bmpData2) != 0)
			asm_Print("Error al grabar el archivo!");
	}
	// libera memoria
	limpiarBmpData(&bmpData);
	if(metodo==5||metodo==6)limpiarBmpData(&bmpData2);
	return 0;
}

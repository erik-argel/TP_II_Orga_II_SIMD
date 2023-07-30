#ifndef FILTROS_H
#define FILTROS_H

#include "bmp.h"

typedef struct tagFILTRO {

	float RR, RG, RB;
	float GR, GG, GB;
	float BR, BG, BB;
} FILTRO;

FILTRO SEPIA;

void asm_blend(char*, char*, int);

void filtro (BMPDATA*, FILTRO);
void blancoYNegro (BMPDATA*);
void aclararimagen (BMPDATA*, int);
void corromper (BMPDATA*);
void medianFilter (BMPDATA*, int);
void multiplyBlend (BMPDATA*, BMPDATA*);
void blendBmpAsm (BMPDATA*, BMPDATA*);
int cantPixels (BMPDATA*);
unsigned char mediana (unsigned char*, int);
void pruebaBmpAsm(BMPDATA* , BMPDATA* );
#endif

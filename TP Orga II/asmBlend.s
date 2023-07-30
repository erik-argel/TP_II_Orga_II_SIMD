INICIO	equ	0
const2   dd 2
section .text
	global asm_blend
	;; asm_blend(char *a, char *b, int cant)
asm_blend:
	push	ebp
	mov	    ebp, esp
	push	ebx
parametros:
    mov	            eax, [esp + 12] ; imagen A
	mov	            ebx, [esp + 16]	; imagen B
	mov             ecx, [esp + 20]	; tamaño de ambas
start:
    mov             esi, INICIO
    MOVSS          xmm2, [const2]
    cvtdq2ps       xmm2, xmm2
    shufps         xmm2, xmm2, 0
loop:

    PMOVZXBD       xmm0, [eax + esi]
    cvtdq2ps       xmm0, xmm0
    PMOVZXBD       xmm1, [ebx + esi]
    cvtdq2ps       xmm1, xmm1

    ADDPS          xmm0, xmm1
    DIVPS          xmm0, xmm2

    cvtps2dq       xmm0, xmm0
    ;cvtps2dq       xmm1, xmm1



    MOVSS	       [eax + esi], xmm0
    SHUFPs         xmm0, xmm0, 10010011b
    MOVSS          [eax + esi + 1], xmm0
    SHUFPs        xmm0, xmm0,  10010011b
    MOVSS          [eax + esi + 2], xmm0
    shufps         xmm0, xmm0, 10010011b
    MOVSS          [eax + esi + 3], xmm0
    
    add esi, 4
    cmp esi, ecx
    jne loop

exit:
    pop ebx
    pop ebp
    ret
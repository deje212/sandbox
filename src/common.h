#ifndef __COMMON_INCLUDED__
#define __COMMON_INCLUDED__

#include <malloc.h>

/* Macete: Caso uma função tenha parâmetros e
   um ou mais desses parâmetros não sejam usados,
   usar essa macro evita que o compilador emita
   um 'warning'. */
#define UNUSED_PARAM(x) { (x) = (x); }

/* Macete: Obtem o número de itens de um array. */
#define ARRAY_ITEMS(array) ( sizeof((array)) / sizeof(&(array)[0]) )

/* Testa se um dos bits em 'bits' estão setados em 'x'. */
#define MASK_BITS(x,bits) ((x) & (bits))
#define TEST_BITS(x,bits) ((MASK_BITS((x),(bits))) != 0)

/* NEW() e DELETE() C style.

	 WARNING: Cuidado com a passagem de parametros para essas macros! */
#define NEW(type, n) malloc(sizeof(type)*(n))
#define DELETE(p) { free((p)); }

/* COMPARE returna 1 para "maior que", -1 para "menor que" e 0 para "igual a".

   WARNING: Usar essas macros pode ser perigoso!
	 Acho que a especificação da linguagem C dita que qualquer valor diferente
   de zero é TRUE. As macros abaixo supõem que TRUE é 1.

	 Na arquitetura Intel (x86 e x86_64) isso parece ser verdadeiro, já que
   o compilador tende a zerar um resitrador e usar a instrução "set al,1"
   para denotar TRUE. 

	 Está dado o aviso! */

#define COMPARE(x,y) (((x) > (y)) - ((x) < (y)))
#define SIGN(x) COMPARE((x), 0)

#endif

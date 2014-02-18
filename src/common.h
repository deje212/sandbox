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

/* NEW() e DELETE() C++ style for C (be careful!) */
#define NEW(type, n) malloc(sizeof(type)*(n))
#define DELETE(p) { free((p)); }

#endif

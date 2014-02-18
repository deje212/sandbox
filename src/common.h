#ifndef __COMMON_INCLUDED__
#define __COMMON_INCLUDED__

/* Macete: Caso uma função tenha parâmetros e
   um ou mais desses parâmetros não sejam usados,
   usar essa macro evita que o compilador emita
   um 'warning'. */
#define UNUSED_PARAM(x) { (x) = (x); }

/* Macete: Obtem o número de itens de um array. */
#define ARRAY_ITEMS(array) ( sizeof((array)) / sizeof(&(array)[0]) )

#endif

#ifndef __COMMON_INCLUDED__
#define __COMMON_INCLUDED__

/* Macete: Caso uma função tenha parâmetros e
   um ou mais desses parâmetros não sejam usados,
   usar essa macro evita que o compilador emita
   um 'warning'. */
#define UNUSED_PARAM(x) { (x) = (x); }

#endif

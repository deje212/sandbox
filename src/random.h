#ifndef __RANDOM_INCLUDED__
#define __RANDOM_INCLUDED__

#include <stdlib.h>

/*
  Um fato que me foi apontado por Nelson Brito, desenvolvedor do T50,
  é que os bits menos significativos de um gerador de números pseudo
  aleatórios, baseado numa equação linear, são "pouco aleatórios".

  Assim, ao tentar obter valores aleatórios de 8, 16 ou 32 bits, através
  de uma simples máscara, usando AND, pode nos dar a falsa ilusão de
  aleatoriedade... Para "garantir" maior aleatoriedade é conveniente
  usar os bits superiores...
*/

#define _RND_UPPER_BITS(x,bits) ((x) >> (sizeof(long int) - (bits))

#define _CHAR_RND(x)  _RND_UPPER_BITS((x),sizeof(char))
#define _SHORT_RND(x) _RND_UPPER_BITS((x),sizeof(short))

int read_random_array(void *data, size_t size);

#endif

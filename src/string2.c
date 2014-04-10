#include <stdlib.h>
#include "string2.h"

/* strncpy() modificada.
   Esta versão garante que '\0' será colocado no final de 'dest'. */
char *strncpy_z(char* dest, const char* src, size_t size)
{
  char *cptmp;

  if ((cptmp = dest) == NULL || src == NULL)
    return NULL;

  while (size-- && (*dest++ = *src++))
    ;

  *cptmp = '\0';

  return dest;
}

/* Copia substring do offset 'from' até o offset 'to' da string 'src'
   para a string 'dest', colocando '\0' no final de 'dest'. 

   Retorna a quantidade de caracteres copiados (excluindo o '\0'). */
int   strcpy_range(char* dest, const char* src, int from, int to)
{
  int i, size;

  if (src == NULL || dest == NULL)
    return -1;

  if ((size = to - from) < 0)
    return -1;

  src += from;
  for (i = 0; (i < size) && (*dest++ = *src++); ++i)
    ;

  *dest = '\0';

  return i;
}


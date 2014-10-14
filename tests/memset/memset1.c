#include <stdlib.h>

void bzero_loop(void *buffer, size_t size)
{
  char *p = buffer;

  while (size--) *p++ = 0;
}


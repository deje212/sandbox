#include <stdio.h>

int write_pgm(char *filename, int width, int height, void *ptr)
{
  int i;
  unsigned char *p = ptr;
  FILE *f;

  if ((f = fopen(filename, "wt")) == NULL)
    return -1;

  fprintf(f, "P2\n%d %d\n255\n",
    width, height);

  for (i = 0; i < width*height; i++)
    fprintf(f, "%d\n", *p++);

  fclose(f);
  return 0;
}

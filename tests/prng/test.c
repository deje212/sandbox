#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char pixelmap[512*512];

void main(void)
{
  int pos, i;

  memset(pixelmap, 0xff, sizeof(pixelmap));

  for (i = 0; i < 300000; i++)
  {
    pos = (int)(512*512)*((double)rand() / (RAND_MAX + 1.0));
    pixelmap[pos] = 0;
  }

  write_pgm("pixels.pgm", 512, 512, pixelmap);
}

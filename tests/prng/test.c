#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../../src/cycle_counting.h"

#define GRAPH_WIDTH   512
#define GRAPH_HEIGHT  512
#define ARRAY_SIZE (GRAPH_WIDTH * GRAPH_HEIGHT)
#define MAX_SAMPLES (ARRAY_SIZE / 2)

unsigned char pixelmap[ARRAY_SIZE];

static unsigned long _seed;
unsigned int __attribute__((noinline)) RANDOM(void)
{
  return _seed = 0x41c64e6dUL * _seed + 12345UL;
}

static unsigned long s[2] = { 0x748bd5a53132b, 0x41c6e6d32143a1c7UL };
unsigned long __attribute__((noinline)) next(void)
{
  unsigned long s1 = s[0];
  const unsigned long s0 = s[1];
  s[0] = s0;
  s1 ^= s1 << 23; // a
  s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
  return s[1] + s0;
}

void main(void)
{
  int pos, i;
  unsigned int seed, value;
  unsigned long value2;
  unsigned long c1, c2;
  unsigned long c[3];

  seed = (unsigned int)time(NULL);

  /* Fundo branco. */
  memset(pixelmap, 0xff, sizeof(pixelmap));
  //srand(seed);
  c[0] = 0;
  for (i = 0; i < MAX_SAMPLES; i++)
  {
    c1 = START_CYCLE_COUNT();
    value = rand();
    c[0] += STOP_CYCLE_COUNT() - c1;
    

    pos = (int)(ARRAY_SIZE * ((double)value / (RAND_MAX + 1.0)));
    pixelmap[pos] = 0;
  }

  write_pgm("rand.pgm", 512, 512, pixelmap);

  /* Fundo branco. */
  memset(pixelmap, 0xff, sizeof(pixelmap));
  //_seed = seed;
  c[1] = 0;
  for (i = 0; i < MAX_SAMPLES; i++)
  {
    c1 = START_CYCLE_COUNT();
    value = RANDOM();
    c[1] += STOP_CYCLE_COUNT() - c1;

    pos = (int)(ARRAY_SIZE * ((double)value / (UINT_MAX + 1.0)));
    pixelmap[pos] = 0;
  }

  write_pgm("lcg.pgm", 512, 512, pixelmap);

  /* Fundo branco. */
  memset(pixelmap, 0xff, sizeof(pixelmap));
  //s[0] = seed;
  c[2] = 0;
  for (i = 0; i < MAX_SAMPLES; i++)
  {
    c1 = START_CYCLE_COUNT();
    value2 = next();
    c[2] += STOP_CYCLE_COUNT() - c1;

    pos = (int)(ARRAY_SIZE * ((double)(value2 >> 32) / (UINT_MAX + 1.0)));
    pixelmap[pos] = 0;
  }

  write_pgm("xorshift128plus.pgm", 512, 512, pixelmap);

  printf("Tempos: rand()       - %lld ciclos.\n"
         "        LCG          - %lld ciclos.\n"
         "        XORSHIFT128+ - %lld ciclos.\n",
         c[0] / MAX_SAMPLES, c[1] / MAX_SAMPLES, c[2] / MAX_SAMPLES);

}


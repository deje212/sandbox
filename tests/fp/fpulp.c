#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef union {
  float f;
  unsigned int i;
  struct {
    unsigned int mantissa:23;
    unsigned int expoent:8;
    unsigned int sign:1;
  } s;
} f32_t;

/* Compara os floats como se fossem inteiros. 
   Não leva em consideração NaN's e infinitos. */
int compare_floats2(float x, float y)
{
  /* Verifica o sinal */
  if (((f32_t *)&x)->s.sign != ((f32_t *)&y)->s.sign)
  {
    /* Cerca a possibilidade de compara +0 com -0. */
    if (x == y)
      return 1;
    return 0;
  }

  return abs(((f32_t *)&x)->i - ((f32_t *)&y)->i) <= 1;
}

int main(int argc, char **argv)
{
  float x = 67329.234;
  float y = 67329.242;

  printf("(%g == %g) = %s\n",
    x, y,
    compare_floats2(x,y) ? "true" : "false");

  return 0;
}

#include <stdio.h>
#include <math.h>
#include "../src/cycle-counting.h"

float division(float a, float b)
{
  return a/b;
}

int main(int argc, char **argv)
{
  float f1;

  f1 = division(0.0f, 0.0f);

  if (isinf(f1))
    printf("Inifinity!\n");
  else
  if (isnan(f1))
    printf("Not a number!\n");
  else
    printf("%.10g\n", f1);

  return 0;
}

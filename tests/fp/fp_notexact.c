#include <stdio.h>

int main(int argc, char **argv)
{
  int i;
  float f, sum;

  f = 0.1f;
  sum = 0.0f;
   
  for (i = 0; i < 10; ++i)
      sum += f;

  printf("sum = %1.15f, product = %1.15f\n", sum, f * 10.0f);
}

#include <stdio.h>
#include <math.h>
#include <values.h>

typedef union {
  float f;
  unsigned int i32;
  struct {
    unsigned int mantissa:23;
    unsigned int expoent:8;
    unsigned int sign:1;
  } s;
} f32_t;

void showFloatStructure(float x)
{
  printf("%.15g (0x%08X; mantissa: 0x%0X, expoent: 0x%0X, sign: %c\n",
         x, 
         ((f32_t *)&x)->i32,
         ((f32_t *)&x)->s.mantissa,
         ((f32_t *)&x)->s.expoent,
         ((f32_t *)&x)->s.sign ? '-' : '+');
}

int main(int argc, char **argv)
{
  int i;
  float values[] = { 0.0f, 1.0f, -1.0f, M_PI, FLT_EPSILON };

  for (i = 0; i < (sizeof(values) / sizeof(values[0])); i++)
    showFloatStructure(values[i]);

  return 0;
}

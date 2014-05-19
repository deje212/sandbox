#include <stdio.h>
#include <math.h>
#include <values.h>

typedef union {
  float f;
  unsigned long i;
  struct {
    unsigned long m:23;
    unsigned long e:8;
    unsigned long s:1;
  };
} sfp_t;

int main(int argc, char **argv)
{
  /* Demonstra que compara com FLT_EPSILON, para valores pequenos, pode ser
     enganoso... */
  float f1, f2;
  
  printf("FLT_EPSILON = %.10g\n\n", FLT_EPSILON);

  /* Note que para todos os valores de f1 [1e-1, 1.5], o "epsilon" é
     menor que FLT_EPSILON, exceto para f1 = 1.5f!... Para f1 maior que 2.0f,
     "epsilon" é maior que FLT_EPSILON. */

  /* O uso de valor não divisível por 2 é porque, neste caso, a "mantissa" será zero.
     Ao subtrair 1 ULP, podemos obter um valor "maluco". */
  for (f1 = 1.5f; f1 > 1e-10f; f1 /= 2.0f)
  {
    f2 = f1;
    ((sfp_t *)&f2)->i--; /* Subtrai 1 ULP */

    /* Mostra a subtração e a representação de f1 (mantissa, expoente). */
    printf("%.10g - %.10g = %.10g [f1 = (0x%x,0x%x)]\n", f1, f2, (f1 - f2), ((sfp_t *)&f1)->m, ((sfp_t *)&f1)->e);
  }

  return 0;
}

#include <stdio.h>
#include <cpuid.h>
#include <x86intrin.h>

int main(int argc, char *argv[])
{
  unsigned int a, b, c, d;
  unsigned long long r;
  int ok;

  __get_cpuid(1, &a, &b, &c, &d);

  if (!(b & 0x00040000))
  {
    fprintf(stderr, "Unsupported RDSEED instruction.\n");
  }

  if (!(c & bit_RDRND))
  {
    fprintf(stderr, "Unsupported RDRAND instruction.\n");
    return 1;
  }

  __asm__ volatile ("rdrand %0; setc %1" : "=r" (r), "=m" (ok));

  if (ok)
    printf("Random Value = 0x%llX\n", r);
  else
    fprintf(stderr, "RDRAND return invalid value.\n");

  return 0;
}

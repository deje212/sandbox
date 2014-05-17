#include <stdio.h>
#include <malloc.h>
#include "cycle-counting.h"

int main(void)
{
  long long t;
  char *p[1000];
  int i;

  START_CYCLE_COUNT(t);
  for (i = 0; i < 1000; i++)
    p[i] = malloc(1000);
  STOP_CYCLE_COUNT(t);

  printf("%lld ciclos de máquina.\n", t / 1000);
}

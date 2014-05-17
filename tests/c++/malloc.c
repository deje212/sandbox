#include <stdio.h>
#include <malloc.h>
#include "../../src/cycle-counting.h"

int main(void)
{
  long long t1, t2;
  char *p[1000];
  int i;

  START_CYCLE_COUNT(t1);
  for (i = 0; i < 1000; i++)
    p[i] = malloc(1000);
  STOP_CYCLE_COUNT(t2);

  printf("%lld ciclos de máquina.\n", (t2 - t1) / 1000);
}

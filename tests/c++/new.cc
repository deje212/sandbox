#include <iostream>
#include "../../src/cycle-counting.h"

using namespace std;

int main(void)
{
  long long t1, t2;
  char *p[1000];

  START_CYCLE_COUNT(t1);
  for (int i = 0; i < 1000; i++)
    p[i] = new char [1000];
  STOP_CYCLE_COUNT(t2);

  cout << ((t2 - t1) / 1000) << " ciclos de máquina.\n";

  return 0;
}

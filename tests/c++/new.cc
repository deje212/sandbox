#include <iostream>
#include "cycle-counting.h"

using namespace std;

int main(void)
{
  long long t;
  char *p[1000];

  START_CYCLE_COUNT(t);
  for (int i = 0; i < 1000; i++)
    p[i] = new char [1000];
  STOP_CYCLE_COUNT(t);

  cout << (t / 1000) << " ciclos de máquina.\n";

  return 0;
}

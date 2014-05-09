#include <stdio.h>

__attribute__((visibility("default"))) void MyFunc(int x)
{
  printf("%d\n", x);
}

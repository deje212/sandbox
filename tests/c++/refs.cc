#include <iostream>
#include <stddef.h>

int main()
{
  int *p = NULL;
  int& r = *p;

  std::cout << r << '\n';
  
  return 0;
}

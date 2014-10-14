#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char buffer[1000];

extern void bzero_loop(void *, size_t);
extern void bzero_sse(void *, size_t);
extern void bzero_asm(void *, size_t);

extern unsigned long long start_cycle_count(void);
extern unsigned long long end_cycle_count(void);

int main(int argc, char *argv[])
{
  unsigned long long t1, t2, t3, t4, t5;
  int i;

  i = 1000;
  t1 = start_cycle_count();
  while (i--) bzero_loop(buffer, sizeof(buffer));
  t1 = end_cycle_count() - t1;

  i = 1000;
  t2 = start_cycle_count();
  while (i--) bzero_asm(buffer, sizeof(buffer));
  t2 = end_cycle_count() - t2;

  i = 1000;
  t3 = start_cycle_count();
  while (i--) bzero_sse(buffer, sizeof(buffer));
  t3 = end_cycle_count() - t3;

  i = 1000;
  t4 = start_cycle_count();
  while (i--) bzero(buffer, sizeof(buffer));
  t4 = end_cycle_count() - t4;

  i = 1000;
  t5 = start_cycle_count();
  while (i--) memset(buffer, 0, sizeof(buffer));
  t5 = end_cycle_count() - t5;

  printf("bzero_loop: %llu cycles.\n"
         "bzero_asm: %llu cycles.\n"
         "bzero_sse: %llu cycles.\n"
         "bzero: %llu cycles.\n"
         "memset: %llu cycles.\n", t1, t2, t3, t4, t5);

  return 0;
}

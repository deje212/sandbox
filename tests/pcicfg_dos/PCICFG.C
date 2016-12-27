#include <stdio.h>

#define CFGREG(b,d,f,o) \
  ((1UL << 31) | \
  ((unsigned long)((b) & 0xff) << 16) | \
  ((unsigned long)((d) & 0x1f) << 11) | \
  ((unsigned long)((f) & 0x07) << 8)  | \
  (o & 0xfc))

extern unsigned long inpd(unsigned short);
extern void outpd(unsigned short, unsigned long);

void main(void)
{
  int i;

  for (i = 0; i < 256; i += 4)
  {
    outpd(0xcf8, CFGREG(0,0,0,i));
    printf("%02x: %08lx\n", i, inpd(0xcfc));
  }
}

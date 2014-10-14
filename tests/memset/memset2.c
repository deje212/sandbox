#include <x86intrin.h>

void bzero_sse(void *buffer, size_t size)
{
  size_t sztmp;
  __m128i mzero;
  __m128i *p16b = buffer;
  unsigned long long *pll;
  unsigned long *pdw;
  unsigned short *pw;
  unsigned char *pb;

  mzero = _mm_setzero_si128();
  sztmp = size % sizeof(__m128i);
  while (sztmp--) { *p16b++ = mzero; size -= sizeof(__m128i); }

  pll = (void *)p16b;
  sztmp = size % sizeof(unsigned long long);
  while (sztmp--) { *pll++ = 0; size -= sizeof(unsigned long long); }

  pdw = (void *)pll;
  sztmp = size % sizeof(unsigned long);
  while (sztmp--) { *pdw++ = 0; size -= sizeof(unsigned long); }

  pw = (void *)pdw;
  sztmp = size % sizeof(unsigned short);
  while (sztmp--) { *pw++ = 0; size -= sizeof(unsigned short); }

  pb = (void *)pw;
  while (size--) { *pb++ = 0; }
}

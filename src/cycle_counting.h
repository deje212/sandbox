#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

/* ==========================================
    Quick & Dirty cycle counting...

    begin_tsc() e end_tsc()

    são usadas para contar a quantidade de ciclos
    de máquina gastos num bloco de código.

    Exemplo de uso:

      unsigned long long t;

      begin_tsc();      
      f();
      t = end_tsc();

    É conveniente compilar o código sob teste com a
    opção -O0, já que o compilador poderá 'sumir' com
    o código, por causa da otimização.

    As macros, em si, não são "otimizáveis", por assim dizer.
   ========================================== */

static unsigned long long _tsc;

inline void begin_tsc(void)
{
  unsigned int a, d;

  asm volatile ( "mfence\nxorl %%eax,%%eax\ncpuid\nrdtsc"
      : "=a" (a), "=d" (d) : : 
#ifdef __x86_64
      "rbx"
#else
      "edx"
#endif      
      );

  _tsc = ((unsigned long long)d << 32) | (unsigned long long)a;
}

inline unsigned long long end_tsc(void)
{
  unsigned int a, d;

  asm volatile ( "rdtscp"
      : "=a" (a), "=d" (d) : : 
#ifdef __x86_64
      "rcx" 
#else
      "ecx"
#endif
      );

  return (((unsigned long long)d << 32) | (unsigned long long)a) - _tsc;
}

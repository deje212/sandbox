#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

/* ==========================================
    Quick & Dirty cycle counting...

    START_CYCLE_COUNT() e STOP_CYCLE_COUNT()

    são usadas para contar a quantidade de ciclos
    de máquina gastos num bloco de código.

    Exemplo de uso:

      uint64_t cycles;

      START_CYCLE_COUNT(cycles);
      f();
      STOP_CYCLE_COUNT(cycles);

      // Neste ponto 'cycles' conterá a 
      // quantidade de ciclos gastos por f().

    É conveniente compilar o código com a
    opção -O0, já que podemos ter alguns
    problemas com as macros com código otimizado.

    Para resolver isso, compile a função sob
    teste em um módulo separado, com a opção
    -O3, e o módulo testador com -O0.
   ========================================== */

#include <x86intrin.h>
#include <cpuid.h>

/* NOTE: A "variável x" deve ser do tipo uint64_t e deve ser a mesma entre uso dos macros */

/* __cpuid() é chamada porque ela "limpa" as linhas de cache. */

#define START_CYCLE_COUNT(x) { \
  int a, b, c, d; \
\
  __cpuid(0, a, b, c, d); \
  (x) = _rdtsc(); \
}

#define STOP_CYCLE_COUNT(x) { (x) = _rdtsc() - (x); }

#endif

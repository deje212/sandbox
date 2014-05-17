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

#define START_CYCLE_COUNT(x) \
  { \
    unsigned long lo, hi; \
    \
    __asm__ volatile ( \
      "cpuid; \
       rdtsc; \
       rdtsc; \
       rdtsc; \
       rdtsc; \
       rdtsc; \
       rdtsc; \
       rdtsc; \
       rdtsc; \
       rdtsc;" \
      : "=a" (lo), "=d" (hi) : : "%rbx", "%rcx" \
    ); \
  \
    (x) = ((unsigned long long)hi << 32) + lo; \
  }

/* From INTEL paper. */
#define STOP_CYCLE_COUNT(x) \
  { \
    unsigned long lo, hi; \
    \
    __asm__ volatile ( \
      "rdtscp;" \
      : "=a" (lo), "=d" (hi) : : "%rcx" \
    ); \
  \
    (x) = ((unsigned long long)hi << 32) + lo; \
  }

#endif

#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

/* ==========================================
    Quick & Dirty cycle counting...

    START_CYCLE_COUNT() e STOP_CYCLE_COUNT()

    são usadas para contar a quantidade de ciclos
    de máquina gastos num bloco de código.

    Exemplo de uso:

      uint64_t t1, t2;

      t1 = START_CYCLE_COUNT();
      f();
      t2 = STOP_CYCLE_COUNT();

      // Neste ponto (t2 - t1) conterá a
      // quantidade de ciclos gastos por f().

    É conveniente compilar o código sob teste com a
    opção -O0, já que o compilador poderá 'sumir' com
    o código, por causa da otimização.

    As macros, em si, não são "otimizáveis", por assim dizer.
   ========================================== */

#define START_CYCLE_COUNT() \
  ({ unsigned long tmp; \
     __asm__ __volatile__ ( \
      "mfence\n" \
      "rdtsc\n" \
      "shlq $32,%%rdx\n" \
      "orq %%rdx,%%rax" \
      : "=a" (tmp) : : "rdx" \
    ); \
  \
    tmp; })

#define STOP_CYCLE_COUNT(x) \
  ({  unsigned long tmp; \
      __asm__ volatile ( \
        "rdtscp;" \
        "shlq $32,%%rdx\n" \
        "orq %%rdx,%%rax" \
        : "=a" (tmp) : : "rcx", "rdx" \
      ); \
      tmp; })

#endif

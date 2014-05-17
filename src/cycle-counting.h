#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

/* ==========================================
    Quick & Dirty cycle counting...

    START_CYCLE_COUNT() e STOP_CYCLE_COUNT()

    são usadas para contar a quantidade de ciclos
    de máquina gastos num bloco de código.

    Exemplo de uso:

      uint64_t t1, t2;

      START_CYCLE_COUNT(t1);
      f();
      STOP_CYCLE_COUNT(t2);

      // Neste ponto (t2 - t1) conterá a
      // quantidade de ciclos gastos por f().

    É conveniente compilar o código sob teste com a
    opção -O0, já que o compilador poderá 'sumir' com
    o código, por causa da otimização.

    As macros, em si, não são "otimizáveis", por assim dizer.
   ========================================== */

/* Diversas instruções rdtscp para serialização e warmup. */
/* Infelizmente o assembly inline do GCC não permite usar
   a restrição "=A" para atualizar um 'unsigned long long'
   de uma só vez! */
#define START_CYCLE_COUNT(x) \
  { \
    unsigned long __lo, __hi; \
    \
    __asm__ volatile ( \
      "rdtscp; \
       rdtscp; \
       rdtscp; \
       rdtscp; \
       rdtscp; \
       rdtscp; \
       rdtscp; \
       rdtscp; \
       rdtscp;" \
      : "=a" (__lo), "=d" (__hi) : : "%rcx" \
    ); \
  \
    (x) = ((unsigned long long)__hi << 32) + __lo; \
  }

#define STOP_CYCLE_COUNT(x) \
  { \
    unsigned long __lo, __hi; \
    \
    __asm__ volatile ( \
      "rdtscp;" \
      : "=a" (__lo), "=d" (__hi) : : "%rcx" \
    ); \
  \
    (x) = ((unsigned long long)__hi << 32) + __lo; \
  }

#endif

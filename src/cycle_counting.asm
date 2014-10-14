; NASM code instead of inline code.
bits 64
section .text

; unsigned long long start_cycle_count(void);
global start_cycle_count:function
start_cycle_count:
  times 16 rdtscp ; 16 rdtscp instructions for warm-up.
  shl rdx,32
  or  rax,rdx
  ret

; unsigned long long end_cycle_count(void);
global end_cycle_count:function
end_cycle_count:
  rdtsc
  shl rdx,32
  or  rax,rdx
  ret

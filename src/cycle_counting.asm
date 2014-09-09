; NASM code instead of inline code.
bits 64
section .text

; unsigned long long start_cycle_count(void);
global start_cycle_count:function
start_cycle_count:
  push rcx
  %rep 16       ; using 16 instructions for warm-up.
    rdtscp
  %endrep
  shl rcx,32
  and rax,0xffffffff
  or  rax,rcx
  pop rcx
  ret

; unsigned long long end_cycle_count(void);
global end_cycle_count:function
end_cycle_count:
  push rcx
  rdtsc
  shl rcx,32
  and rax,0xffffffff
  or  rax,rcx
  pop rcx
  ret

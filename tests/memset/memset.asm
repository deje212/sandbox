bits 64
section .text

global bzero_asm:function
bzero_asm:
  xor rax,rax
  mov rcx,rsi
  repnz stosb
  ret

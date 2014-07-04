	.file	"ack.c"
	.intel_syntax noprefix
# GNU C (Ubuntu 4.8.2-19ubuntu1) version 4.8.2 (x86_64-linux-gnu)
#	compiled by GNU C version 4.8.2, GMP version 5.1.3, MPFR version 3.1.2-p3, MPC version 1.0.1
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu ack.c
# --param l1-cache-size=32 --param l1-cache-line-size=64
# --param l2-cache-size=8192 -mtune=core-avx2 -masm=intel -march=x86-64 -O3
# -fverbose-asm -fstack-protector -Wformat -Wformat-security
# options enabled:  -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
# -fcaller-saves -fcombine-stack-adjustments -fcommon -fcompare-elim
# -fcprop-registers -fcrossjumping -fcse-follow-jumps -fdefer-pop
# -fdelete-null-pointer-checks -fdevirtualize -fdwarf2-cfi-asm
# -fearly-inlining -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffunction-cse -fgcse -fgcse-after-reload -fgcse-lm
# -fgnu-runtime -fguess-branch-probability -fhoist-adjacent-loads -fident
# -fif-conversion -fif-conversion2 -findirect-inlining -finline
# -finline-atomics -finline-functions -finline-functions-called-once
# -finline-small-functions -fipa-cp -fipa-cp-clone -fipa-profile
# -fipa-pure-const -fipa-reference -fipa-sra -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -fmath-errno -fmerge-constants
# -fmerge-debug-strings -fmove-loop-invariants -fomit-frame-pointer
# -foptimize-register-move -foptimize-sibling-calls -foptimize-strlen
# -fpartial-inlining -fpeephole -fpeephole2 -fpredictive-commoning
# -fprefetch-loop-arrays -free -freg-struct-return -fregmove
# -freorder-blocks -freorder-functions -frerun-cse-after-loop
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-insns2 -fshow-column -fshrink-wrap
# -fsigned-zeros -fsplit-ivs-in-unroller -fsplit-wide-types
# -fstack-protector -fstrict-aliasing -fstrict-overflow
# -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop
# -ftree-copyrename -ftree-cselim -ftree-dce -ftree-dominator-opts
# -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-distribute-patterns
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-partial-pre
# -ftree-phiprop -ftree-pre -ftree-pta -ftree-reassoc -ftree-scev-cprop
# -ftree-sink -ftree-slp-vectorize -ftree-slsr -ftree-sra
# -ftree-switch-conversion -ftree-tail-merge -ftree-ter
# -ftree-vect-loop-version -ftree-vectorize -ftree-vrp -funit-at-a-time
# -funswitch-loops -funwind-tables -fvect-cost-model -fverbose-asm
# -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -maccumulate-outgoing-args -malign-stringops -mfancy-math-387
# -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4
# -mpush-args -mred-zone -msse -msse2 -mtls-direct-seg-refs

	.text
	.p2align 4,,15
	.globl	ack
	.type	ack, @function
ack:
.LFB24:
	.cfi_startproc
	test	edi, edi	# m
	je	.L49	#,
	push	r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	lea	eax, [rdi-1]	# ivtmp.48,
	push	r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 24	#,
	.cfi_def_cfa_offset 80
	mov	DWORD PTR [rsp+4], eax	# %sfp, ivtmp.48
	jmp	.L4	#
	.p2align 4,,10
	.p2align 3
.L51:
	mov	eax, DWORD PTR [rsp+4]	# m, %sfp
	mov	sil, 1	#,
	sub	DWORD PTR [rsp+4], 1	# %sfp,
	test	eax, eax	# m
	je	.L50	#,
.L4:
	test	esi, esi	# n
	je	.L51	#,
	mov	eax, DWORD PTR [rsp+4]	# ivtmp.48, %sfp
	sub	esi, 1	# n,
	mov	DWORD PTR [rsp+8], eax	# %sfp, ivtmp.48
	jmp	.L7	#
	.p2align 4,,10
	.p2align 3
.L53:
	mov	eax, DWORD PTR [rsp+8]	# m, %sfp
	mov	sil, 1	#,
	sub	DWORD PTR [rsp+8], 1	# %sfp,
	test	eax, eax	# m
	je	.L52	#,
.L7:
	test	esi, esi	# n
	je	.L53	#,
	mov	ebx, DWORD PTR [rsp+8]	# ivtmp.43, %sfp
	lea	eax, [rsi-1]	# n,
	mov	DWORD PTR [rsp+12], ebx	# %sfp, ivtmp.43
	jmp	.L11	#
.L55:
	mov	edx, DWORD PTR [rsp+12]	# m, %sfp
	mov	al, 1	#,
	sub	DWORD PTR [rsp+12], 1	# %sfp,
	test	edx, edx	# m
	je	.L54	#,
.L11:
	test	eax, eax	# n
	je	.L55	#,
	sub	eax, 1	# n,
	mov	r13d, DWORD PTR [rsp+12]	# ivtmp.33, %sfp
	jmp	.L15	#
.L57:
	mov	edx, r13d	# m, ivtmp.33
	sub	r13d, 1	# ivtmp.33,
	mov	al, 1	#,
	test	edx, edx	# m
	je	.L56	#,
.L15:
	test	eax, eax	# n
	je	.L57	#,
	sub	eax, 1	# n,
	mov	r12d, r13d	# ivtmp.28, ivtmp.33
	jmp	.L19	#
.L59:
	mov	edx, r12d	# m, ivtmp.28
	sub	r12d, 1	# ivtmp.28,
	mov	al, 1	#,
	test	edx, edx	# m
	je	.L58	#,
.L19:
	test	eax, eax	# n
	je	.L59	#,
	sub	eax, 1	# n,
	mov	ebp, r12d	# ivtmp.23, ivtmp.28
	jmp	.L23	#
	.p2align 4,,10
	.p2align 3
.L61:
	mov	edx, ebp	# m, ivtmp.23
	sub	ebp, 1	# ivtmp.23,
	mov	al, 1	#,
	test	edx, edx	# m
	je	.L60	#,
.L23:
	test	eax, eax	# n
	je	.L61	#,
	sub	eax, 1	# n,
	mov	ebx, ebp	# ivtmp.18, ivtmp.23
	jmp	.L27	#
	.p2align 4,,10
	.p2align 3
.L63:
	mov	edx, ebx	# m, ivtmp.18
	sub	ebx, 1	# ivtmp.18,
	mov	al, 1	#,
	test	edx, edx	# m
	je	.L62	#,
.L27:
	test	eax, eax	# n
	je	.L63	#,
	sub	eax, 1	# n,
	mov	r14d, ebx	# ivtmp.13, ivtmp.18
	jmp	.L31	#
	.p2align 4,,10
	.p2align 3
.L65:
	mov	edx, r14d	# m, ivtmp.13
	sub	r14d, 1	# ivtmp.13,
	mov	al, 1	#,
	test	edx, edx	# m
	je	.L64	#,
.L31:
	test	eax, eax	# n
	je	.L65	#,
	sub	eax, 1	# n,
	mov	r15d, r14d	# ivtmp.7, ivtmp.13
	jmp	.L35	#
	.p2align 4,,10
	.p2align 3
.L67:
	mov	ecx, r15d	# m, ivtmp.7
	sub	r15d, 1	# ivtmp.7,
	mov	al, 1	#,
	test	ecx, ecx	# m
	je	.L66	#,
.L35:
	lea	edi, [r15+1]	# D.2516,
	test	eax, eax	# n
	je	.L67	#,
	lea	esi, [rax-1]	# D.2516,
	call	ack	#
	mov	ecx, r15d	# m, ivtmp.7
	sub	r15d, 1	# ivtmp.7,
	test	ecx, ecx	# m
	jne	.L35	#,
.L66:
	mov	edx, r14d	# m, ivtmp.13
	add	eax, 1	# n,
	sub	r14d, 1	# ivtmp.13,
	test	edx, edx	# m
	jne	.L31	#,
.L64:
	mov	edx, ebx	# m, ivtmp.18
	add	eax, 1	# n,
	sub	ebx, 1	# ivtmp.18,
	test	edx, edx	# m
	jne	.L27	#,
.L62:
	mov	edx, ebp	# m, ivtmp.23
	add	eax, 1	# n,
	sub	ebp, 1	# ivtmp.23,
	test	edx, edx	# m
	jne	.L23	#,
.L60:
	mov	edx, r12d	# m, ivtmp.28
	add	eax, 1	# n,
	sub	r12d, 1	# ivtmp.28,
	test	edx, edx	# m
	jne	.L19	#,
.L58:
	mov	edx, r13d	# m, ivtmp.33
	add	eax, 1	# n,
	sub	r13d, 1	# ivtmp.33,
	test	edx, edx	# m
	jne	.L15	#,
.L56:
	mov	edx, DWORD PTR [rsp+12]	# m, %sfp
	add	eax, 1	# n,
	sub	DWORD PTR [rsp+12], 1	# %sfp,
	test	edx, edx	# m
	jne	.L11	#,
.L54:
	lea	esi, [rax+1]	# n,
	mov	eax, DWORD PTR [rsp+8]	# m, %sfp
	sub	DWORD PTR [rsp+8], 1	# %sfp,
	test	eax, eax	# m
	jne	.L7	#,
.L52:
	mov	eax, DWORD PTR [rsp+4]	# m, %sfp
	add	esi, 1	# n,
	sub	DWORD PTR [rsp+4], 1	# %sfp,
	test	eax, eax	# m
	jne	.L4	#,
.L50:
	lea	eax, [rsi+1]	# ans,
	add	rsp, 24	#,
	.cfi_def_cfa_offset 56
	pop	rbx	#
	.cfi_restore 3
	.cfi_def_cfa_offset 48
	pop	rbp	#
	.cfi_restore 6
	.cfi_def_cfa_offset 40
	pop	r12	#
	.cfi_restore 12
	.cfi_def_cfa_offset 32
	pop	r13	#
	.cfi_restore 13
	.cfi_def_cfa_offset 24
	pop	r14	#
	.cfi_restore 14
	.cfi_def_cfa_offset 16
	pop	r15	#
	.cfi_restore 15
	.cfi_def_cfa_offset 8
	ret
.L49:
	lea	eax, [rsi+1]	# ans,
	ret
	.cfi_endproc
.LFE24:
	.size	ack, .-ack
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"ackerman (%d, %d) is: %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	push	rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xor	ecx, ecx	# j
	.p2align 4,,10
	.p2align 3
.L69:
	lea	ebx, [rcx+1]	# j,
	xor	edx, edx	#
	mov	esi, OFFSET FLAT:.LC0	#,
	mov	r8d, ebx	#, j
	mov	edi, 1	#,
	xor	eax, eax	#
	call	__printf_chk	#
	mov	ecx, ebx	# j, j
	jmp	.L69	#
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits

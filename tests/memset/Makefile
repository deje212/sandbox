all: memset_test

memset_test: memset_test.o cycle_counting.o memset.o memset1.o memset2.o
	gcc -o memset_test memset_test.o cycle_counting.o memset.o memset1.o memset2.o

cycle_counting.o: cycle_counting.asm
	nasm -f elf64 cycle_counting.asm -o cycle_counting.o

memset.o: memset.asm
	nasm -f elf64 memset.asm -o memset.o

memset1.o: memset1.c
	gcc -O2 -c -mtune=native -o memset1.o memset1.c

memset2.o: memset2.c
	gcc -O3 -c -mtune=native -o memset2.o memset2.c

memset_test.o: memset_test.c
	gcc -O2 -c -mtune=native -o memset_test.o memset_test.c




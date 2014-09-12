all: test

test: test.o
	gcc -o test test.o -lm -lopenal -lalut

test.o: test.c
	gcc -c test.c -o test.o

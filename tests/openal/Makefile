.PHONY: all clean

all: test

test: test.o
	gcc -o test test.o -lm -lopenal -lalut

test.o: test.c
	gcc -Wdeprecated-declarations -g -c test.c -o test.o

clean:
	rm *.o test

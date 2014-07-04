CC=gcc
CFLAGS=-O3 -mtune=native -fomit-frame-pointer
LIBS=-lm -lGL -lglfw

all: test

test: test.o
	$(CC) -o test test.o $(LIBS)

test.o: test.c

clean:
	rm -f test *.o

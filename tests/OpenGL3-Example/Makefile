.PHONY: all clean

CC=gcc
CFLAGS=-O3 -mtune=native -fomit-frame-pointer
LDFLAGS=-O3 -lm -lGL -lglfw

all: main

main: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c

clean:
	@-rm -f *.o

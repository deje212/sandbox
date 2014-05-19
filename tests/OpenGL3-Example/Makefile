CC=gcc
CFLAGS=-O3 -mtune=native -fomit-frame-pointer
LDFLAGS=-O3 -lm -lGL -lglfw

.PHONY: all clean

all: main

# gcc parece ter um bug onde as opções -l precisam vir por último!
main: main.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c

clean:
	@-rm -f *.o

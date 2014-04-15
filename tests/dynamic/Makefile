.PHONY: all clean

all: libmodule.so test

libmodule.so: module.c
	gcc -O3 -mtune=native -shared -o libmodule.so -fpic module.c

test: test.c
	gcc -O3 -mtune=native -o test test.c -ldl

clean:
	@rm libmodule.so test

test: test.o pgm.o
	gcc -o $@ $^

%.o: %.c
	gcc -O3 -mtune=native -c -o $@ $<

clean:
	rm *.o test

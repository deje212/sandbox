test: test.o pgm.o
	gcc -o $@ $^

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm *.o test

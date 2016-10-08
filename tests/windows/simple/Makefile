CC=x86_64-w64-mingw32-gcc

app.exe: main.o winproc.o
	$(CC) -s -o $@ $^ -Wl,-subsystem=windows -lgdi32

%.o: %.c
	$(CC) -O3 -c -o $@ $<

.PHONY: clean

clean:
	-rm *.o

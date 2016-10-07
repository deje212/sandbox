i2c.exe: main.o winproc.o
	i586-mingw32msvc-gcc -s -o $@ $^ -Wl,-subsystem:windows

%.o: %.c
	i586-mingw32msvc-gcc -O3 -c -o $@ $<

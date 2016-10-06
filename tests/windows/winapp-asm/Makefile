winapp.exe: winapp.o
	i586-mingw32msvc-cc -s -o $@ $^

winapp.o: winapp.asm win32.inc
	nasm -f win32 -o $@ $<

.PHONY: clean

clean:
	-rm *.o

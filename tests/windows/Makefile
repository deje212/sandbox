CC = i586-mingw32msvc-cc
RC = i586-mingw32msvc-windres
CFLAGS = -O3 -mtune=native -D__SINGLE_INSTANCE__

winapp.exe: winapp.o winappres.o
	$(CC) -O3 -s -o $@ $^ -Wl,-subsystem=windows

winapp.o: winapp.c

winappres.o: winapp.rc
	$(RC) $< $@

winapp.c: winapp.c.in
	sed "s/@uniqueid@/$$(uuidgen -r)/" winapp.c.in > winapp.c

.PHONY: clean

clean:
	-rm *.c *.o *.exe

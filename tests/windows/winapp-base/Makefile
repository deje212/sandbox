CC = x86_64-w64-mingw32-gcc
RC = x86_64-w64-mingw32-windres
CFLAGS = -O3 

winapp-base.exe: winapp-base.o winapp-baseres.o
	$(CC) -O3 -s -o $@ $^ -Wl,-subsystem=windows

winapp-base.o: winapp-base.c winapp-resources.h

winapp-baseres.o: winapp-base.rc winapp-resources.h
	$(RC) $< $@

.PHONY: clean

clean:
	-rm *.o *.exe

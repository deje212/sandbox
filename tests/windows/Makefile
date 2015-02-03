# Meu MinGW é o do Linux... substitua por gcc se seu MinGW estiver no Windows.
CC = i586-mingw32msvc-gcc
CFLAGS = -O3 -mtune=native -c

# Temos que passar a opção --subsystem,windows para o linker!
winapp.exe: winapp.o
	$(CC) -s -o $@ $^ -Wl,--subsystem,windows

winapp.o: winapp.c

.PHONY: clean

# Substitua 'rm' por 'del' se seu ambiente é Windows.
clean:
	@rm *.exe
	@rm *.o  


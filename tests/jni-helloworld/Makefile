LIBSPATH=/usr/lib/jvm/default-java/include

all: libHello.so HelloWorld.class

libHello.so: libHello.o
	$(CC) -shared -o $@ $^

HelloWorld.class: HelloWorld.java
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. javac $<

libHello.o: libHello.c
	$(CC) -I$(LIBSPATH) -I$(LIBSPATH)/linux -fPIC -O3 -c -mtune=native -o $@ $<

clean:
	rm *.o *.so *.class

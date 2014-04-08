LIBSPATH=/usr/lib/jvm/java-7-openjdk-amd64/include

all: libHello.so HelloWorld.class

libHello.so: libHello.o
	$(CC) libHello.o -shared -o libHello.so

HelloWorld.class: HelloWorld.java
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. javac HelloWorld.java

libHello.o: libHello.c
	$(CC) -I$(LIBSPATH) -I$(LIBSPATH)/linux -fPIC -O3 -c -mtune=native libHello.c -o libHello.o

clean:
	rm *.o *.so *.class

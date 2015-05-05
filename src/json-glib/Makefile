json_example: json_example.o
	gcc -o $@ $^ `pkg-config --libs glib-2.0 json-glib-1.0`

json_example.o: json_example.c
	gcc -O3 -c -mtune=native -o $@ $< `pkg-config --cflags glib-2.0 json-glib-1.0`

.PHONY: clean
clean:
	rm *.o json_example

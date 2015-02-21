CFLAGS = -O3 -mtune=native
LDFLAGS = -lpcap

send_arp: send_arp.o

send_arp.o: send_arp.c

clean:
	-@if [ -f send_arp.o ]; then rm send_arp.o; fi

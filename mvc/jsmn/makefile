CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: jsmn.c jsm.c
	$(CC) $(CFLAGS) $(PKGCONFIG) jsmn.c jsm.c

clean:
	rm -rf *o ~* all

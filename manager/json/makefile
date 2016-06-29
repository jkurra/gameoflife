CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: jsmn.c json.c
	$(CC) $(CFLAGS) $(PKGCONFIG) jsmn.c json.c

clean:
	rm -rf *o ~* all

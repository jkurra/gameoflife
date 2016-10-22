CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: jsmn.c json.c file.c
	$(CC) $(CFLAGS) $(PKGCONFIG) jsmn.c json.c file.c

clean:
	rm -rf *o ~* all

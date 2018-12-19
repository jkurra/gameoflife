CC = gcc -g
CFLAGS = -Wall -c
LDFLAGS = -DJSMN_STRICT=1
PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: jsmn.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(PKGCONFIG) jsmn.c

clean:
	rm -rf *o ~* all

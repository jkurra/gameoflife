CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: position.c
	$(CC) $(CFLAGS) $(PKGCONFIG) position.c

clean:
	rm -rf *o ~* all

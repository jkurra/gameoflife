CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: log.c
	$(CC) $(CFLAGS) $(PKGCONFIG) log.c

clean:
	rm -rf *o ~* all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: gameengine.c node.c
	$(CC) $(CFLAGS) $(PKGCONFIG) gameengine.c node.c

clean:
	rm -rf *o ~* all

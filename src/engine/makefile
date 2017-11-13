CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: gameengine.c gamearea1.c idspace.c node.c board.c
	$(CC) $(CFLAGS) $(PKGCONFIG) gameengine.c gamearea1.c idspace.c node.c board.c

clean:
	rm -rf *o ~* all

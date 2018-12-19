CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: node.c board.c idspace.c
	$(CC) $(CFLAGS) $(PKGCONFIG) node.c board.c idspace.c

clean:
	rm -rf *o ~* all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: bmodel.c
	$(CC) $(CFLAGS) $(PKGCONFIG) bmodel.c

clean:
	rm -rf *o ~* all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: gamearea.c graphics.c
	$(CC) $(CFLAGS) $(PKGCONFIG) gamearea.c graphics.c

clean:
	rm -rf *o *~ all

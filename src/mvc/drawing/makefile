CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: gamearea.c draw.c
	$(CC) $(CFLAGS) $(PKGCONFIG) gamearea.c draw.c

clean:
	rm -rf *o *~ all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config  --cflags --libs gtk+-3.0`

all: gamearea.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -DGTK_COMPILATION gamearea.c

clean:
	rm -rf *o *~ all

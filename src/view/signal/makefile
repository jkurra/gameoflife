CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config  --cflags --libs gtk+-3.0`

all: signal.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -DGTK_COMPILATION signal.c

clean:
	rm -rf *o *~ all

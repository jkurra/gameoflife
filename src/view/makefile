CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config  --cflags --libs gtk+-3.0`

all: gamearea_src signal_src view_src

gamearea_src:
	cd gamearea && $(MAKE)

signal_src:
	cd signal && $(MAKE)

view_src: view.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -DGTK_COMPILATION view.c

clean:
	cd gamearea && $(MAKE) clean
	cd signal && $(MAKE) clean
	rm -rf *o *~ all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config  --cflags --libs gtk+-3.0`

all: model.c gameobject.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -DGTK_COMPILATION model.c gameobject.c

clean:
	rm -rf *o *~ all

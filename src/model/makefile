CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config  --cflags --libs gtk+-3.0`

all: model.c viewobject.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -DGTK_COMPILATION model.c viewobject.c

clean:
	rm -rf *o *~ all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: manag

manag: manager.c config.c theme.c
	$(CC) $(CFLAGS) $(PKGCONFIG) manager.c config.c theme.c

clean:
	rm -rf *o ~* all

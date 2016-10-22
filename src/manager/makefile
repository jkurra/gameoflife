CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: subsystem manag

subsystem:
	cd json && $(MAKE)

manag: manager.c config.c theme.c log.c
	$(CC) $(CFLAGS) $(PKGCONFIG) manager.c config.c theme.c log.c

clean:
	cd json && $(MAKE) clean
	rm -rf *o ~* all

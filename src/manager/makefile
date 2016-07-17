CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: subsystem manager

subsystem:
	cd json && $(MAKE)

manager: config.c theme.c file.c
	$(CC) $(CFLAGS) $(PKGCONFIG) config.c theme.c file.c

clean:
	rm -rf *o ~* all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: subsystem engine

engine: gameengine.c script.c
	$(CC) $(CFLAGS) $(PKGCONFIG) gameengine.c script.c

subsystem:
	cd board && $(MAKE)
	cd math && $(MAKE)
	cd datamodel && $(MAKE)

clean:
	cd board && $(MAKE) clean
	cd math && $(MAKE) clean
	cd datamodel && $(MAKE) clean
	rm -rf *o ~* all

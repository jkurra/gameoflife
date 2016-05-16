CC = gcc
CFLAGS = -Wall -c

OBJECTS = jsmn.o jsm.o
PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)

jsmn.o: jsmn.c jsmn.h
	$(CC) $(CFLAGS) jsmn.c

jsm.o: jsm.c jsm.h
	$(CC) $(CFLAGS) $(PKGCONFIG) jsm.c

clean:
	rm -rf *o ~*

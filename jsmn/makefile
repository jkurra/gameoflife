CC = gcc
CFLAGS = -c -Wall

OBJECTS = jsmn.o jsm.o
PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`

all: jsmn.o jsm.o
	$(CC) $(CFLAGS) -g jsmn.o jsm.o ${PKGCONFIG}

%.o : %.c
	$(CC) $(CFLAGS) -c $< ${PKGCONFIG}

clean:
	rm -rf *o

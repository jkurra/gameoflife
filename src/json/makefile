CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: jsmn_parser jsonvalue.c objectbase.c
	$(CC) $(CFLAGS) $(PKGCONFIG) jsonvalue.c objectbase.c

jsmn_parser:
	cd jsmn && $(MAKE)

clean:
	rm -rf *o ~* all

CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: configmng.c file.c
	$(CC) $(CFLAGS) $(PKGCONFIG) configmng.c file.c 
clean:
	rm -rf *o ~* all

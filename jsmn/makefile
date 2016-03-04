CC = gcc
CFLAGS = -c -Wall
OBJECTS = jsmn.o

all: jsmn.o
	$(CC) $(CFLAGS) jsmn.o
%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *o

CC = gcc -g
CFLAGS = -Wall -c

all: gridsystem subsystem

subsystem:
	cd array && $(MAKE)

gridsystem: cell.c grid.c
	$(CC) $(CFLAGS) cell.c grid.c

clean:
	rm -rf *o *~ all

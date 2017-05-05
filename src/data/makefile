CC = gcc -g
CFLAGS = -Wall -c

all: gridsystem subsystem

subsystem:
	cd array && $(MAKE)

gridsystem: cell.c grid.c ruleset.c
	$(CC) $(CFLAGS) cell.c grid.c ruleset.c

clean:
	rm -rf *o *~ all

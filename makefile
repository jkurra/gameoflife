CC = gcc
CFLAGS= -Wall

INCDIR = ./jsmn

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS   = cell.o grid.o model.o view.o controller.o main.o jsmn/jsmn.o jsmn/jsm.o

all: subsystem gameoflife

subsystem:
	cd jsmn && $(MAKE) $(CFLAGS)

gameoflife: $(OBJECTS)
	$(CC) $(CFLAGS) -g $(OBJECTS) -o gameoflife ${PKGCONFIG}

%.o : %.c
	$(CC) $(PKGCONFIG) $(CFLAGS) -c $<

clean:
	rm -rf *o subsystem gameoflife

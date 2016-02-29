CC=gcc
CFLAGS= -Wall

INCDIR = ./jsmn
OPENSSLDIR = /usr/include/glut/
GLLDIR = /usr/include/GL/
GLUDIR = /usr/include/glu/
PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`

RPATH = -R${OPENSSLDIR}/lib
LD = -L${OPENSSLDIR} -lglut

OBJECTS = cell.o grid.o model.o jsm.o view.o controller.o main.o jsmn/jsmn.o

all: subsystem gameoflife

subsystem:
	cd jsmn && $(MAKE) $(CFLAGS)

gameoflife: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o gameoflife -L${PKGCONFIG} -L${GLLDIR} -L{GLUDIR}

%.o : %.c
	$(CC) $(PKGCONFIG) $(CFLAGS) -c $<

clean:
	rm -rf *o gameoflife

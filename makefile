CC = gcc -g
CFLAGS = -Wall

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS   = mvc/model.o mvc/view.o mvc/controller.o main.o \
			mvc/jsmn/jsmn.o mvc/jsmn/jsm.o \
			board/cell.o board/grid.o manager/configmng.o manager/file.o

all: subsystem gameoflife

subsystem:
	cd board && $(MAKE)
	cd mvc && $(MAKE)
	cd manager && $(MAKE)

gameoflife: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(PKGCONFIG) -o bin/gameoflife

%.o : %.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -c $<

clean:
	rm -rf *o *~ gameoflife
	cd board && $(MAKE) clean
	cd mvc  && $(MAKE) clean
	cd manager && $(MAKE) clean

CC = gcc -g
CFLAGS = -Wall

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS   = src/model/model.o src/view/view.o main.o src/view/gamearea/gamearea.o\
			src/manager/json/jsmn.o src/manager/json/json.o src/manager/log.o \
			src/data/cell.o src/data/grid.o src/manager/config.o src/manager/theme.o \
			src/manager/json/file.o src/view/signal/signal.o

all: subsystem gameoflife

subsystem:
	cd src/data && $(MAKE)
	cd src/manager && $(MAKE)
	cd src/view && $(MAKE)
	cd src/model && $(MAKE)
	cd src/output && $(MAKE)
gameoflife: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(PKGCONFIG) -o bin/gameoflife

%.o : %.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -c $<

clean:
	rm -rf *o *~ bin/gameoflife
	cd src/data && $(MAKE) clean
	cd src/manager && $(MAKE) clean
	cd src/view && $(MAKE) clean
	cd src/model && $(MAKE) clean
	cd src/output && $(MAKE) clean

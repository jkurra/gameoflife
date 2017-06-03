CC = gcc -g
CFLAGS = -Wall

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0 `
OBJECTS   = src/model/model.o src/view/view.o main.o src/view/gamearea/gamearea.o\
			src/manager/json/jsmn.o src/manager/json/json.o src/output/log.o \
			src/data/cell.o src/data/grid.o src/data/ruleset.o src/manager/config.o src/manager/theme.o \
			src/manager/json/file.o src/view/signal/signal.o src/model/viewobject.o \
			src/data/array/basearray.o src/data/array/cellarray.o src/data/array/gridarray.o \
			src/model/gamemodel.o src/model/menumodel.o src/model/prefmodel.o

all: subsystem gameoflife

subsystem:
	cd src/data && $(MAKE)
	cd src/manager && $(MAKE)
	cd src/view && $(MAKE)
	cd src/model && $(MAKE)
	cd src/output && $(MAKE)

gameoflife: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(PKGCONFIG) -lpthread -lglut -lGLU -lGL -o bin/gameoflife

%.o : %.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -c $<

clean:
	rm -rf *o *~ bin/gameoflife
	cd src/data && $(MAKE) clean
	cd src/manager && $(MAKE) clean
	cd src/view && $(MAKE) clean
	cd src/model && $(MAKE) clean
	cd src/output && $(MAKE) clean

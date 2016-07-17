CC = gcc -g
CFLAGS = -Wall

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS   = src/mvc/model.o src/mvc/view.o src/mvc/controller.o main.o \
			src/manager/json/jsmn.o src/manager/json/json.o \
			src/data/cell.o src/data/grid.o src/manager/config.o src/manager/theme.o src/manager/file.o

all: subsystem gameoflife

subsystem:
	cd src/data && $(MAKE)
	cd src/mvc && $(MAKE)
	cd src/manager && $(MAKE)

gameoflife: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(PKGCONFIG) -o bin/gameoflife

%.o : %.c
	$(CC) $(CFLAGS) $(PKGCONFIG) -c $<

clean:
	rm -rf *o *~ gameoflife
	cd src/data && $(MAKE) clean
	cd src/mvc && $(MAKE) clean
	cd src/manager && $(MAKE) clean

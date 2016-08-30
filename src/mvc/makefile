CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: draw mvc

draw:
	cd drawing && $(MAKE)

mvc: model.c view.c controller.c
	$(CC) $(CFLAGS) $(PKGCONFIG) model.c view.c controller.c

clean:
	cd drawing && $(MAKE) clean
	rm -rf *o *~ all

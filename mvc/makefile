CC = gcc -g
CFLAGS = -Wall -c

PKGCONFIG = `pkg-config --cflags --libs gtk+-3.0`

all: subsystem mvc

subsystem:
	cd jsmn && $(MAKE)

mvc: model.c view.c controller.c
	$(CC) $(CFLAGS) $(PKGCONFIG) model.c view.c controller.c

clean:
	rm -rf *o *~ all
	cd jsmn && $(MAKE) clean


CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses

prog: main.o text.o
	$(CC) -o prog main.o text.o $(LDFLAGS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
text.o: text.c text.h
	$(CC) $(CFLAGS) -c text.c

clean:
	rm -f main.o text.o prog

.PHONY: clean


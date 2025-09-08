
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses

prog: main.o
	$(CC) -o prog main.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main.o prog

.PHONY: clean


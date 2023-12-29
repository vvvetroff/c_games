.PHONY: all
CC=cc
CFLAGS=-lncurses

all: snake

snake: snake.c snakefuncs.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o snake
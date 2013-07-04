CC=gcc

all: shell1 process

shell1: shell1.c error.c
	$(CC) -o $@ $^

process: process.c
	$(CC) -o $@ $<

clean:
	rm -rf shell1 process *.o

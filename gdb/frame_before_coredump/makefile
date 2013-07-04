CC=gcc -Wall -g -O0
#CC=arm-linux-gcc -Wall -g -O0

all: before_die test_corruption
	$(CC) -o test test_corruption.o before_die.o -pthread

before_die : before_die.c
	$(CC) -c before_die.c

test_corruption : test_corruption.c
	$(CC) -pthread -finstrument-functions -c test_corruption.c

clean :
	rm -rf *.o test core*

.PHONY:all clean


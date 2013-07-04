TARGET=mycat getcputc
CC=gcc

all: $(TARGET)

mycat: mycat.c error.c
	$(CC) -o mycat mycat.c error.c

getcputc: getcputc.c error.c
	$(CC) -o getcputc getcputc.c error.c

clean:
	rm -rf $(TARGET) *.o

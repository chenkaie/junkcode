#
# JoTV - Video Streaming Systems
# (c) 2001 Jollen <jollen@o3.net>
#
# Makefile for v4l library
#

CC = gcc
CFLAGS = -mpentiumpro -O3 -fomit-frame-pointer -funroll-loops
LIBS =

%.o: %.c
	$(CC) $(CFLAGS) -Wall -c -o $@ $<

all-recursive: all
all: libv4l.a

install: libv4l.a
	cp -f libv4l.a /usr/local/lib/
	cp -f v4l.h /usr/include/

libv4l.a: v4l.o
	ar rc libv4l.a v4l.o

v4l.o: v4l.c v4l.h

clean:
	rm -f *.o libv4l.a

#!/bin/sh

gcc g.c -Wall -shared -fPIC -ldl -o libg.so

export LD_PRELOAD=`pwd`/libg.so
/bin/kill 1234


#!/bin/bash
#define cpp #
cpp $0 2> /dev/null | /bin/bash; exit $?
#undef cpp

#define HELLO_WORLD echo "hello, world"
HELLO_WORLD

#ifndef _OV7725
    echo "NotOV7725";
#else
    echo "OV7725";
#endif


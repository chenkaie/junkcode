#!/bin/sh

NEED=10000
[ ${NEED} -gt 111000 ] ? echo 'c'; : echo 'd';
if [ ${NEED} -gt 111000 ]; then
    echo 'a'; 
else 
    echo 'b'; 
fi

if [ ${Test} ]; then
    echo "ohya"
fi

if [ "$1" != "/mnt/samba/link0/" ] && [ `ls "$1" | wc -l` -eq 0 ] ; then 
    echo "OHya"
else
    echo "shit"
fi



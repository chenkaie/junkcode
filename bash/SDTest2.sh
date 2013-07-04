#!/bin/sh
set -a
PATH=/sbin:/bin:/usr/bin:/usr/sbin

#Testing unit size (KB)
unitsize=2000

mkdir -p /mnt/auto/CF/testcp

dd if=/dev/urandom of=/mnt/ramdisk/testfile0 bs=1k count=$unitsize > /dev/null 2>&1
dd if=/dev/urandom of=/mnt/ramdisk/testfile1 bs=1k count=$unitsize > /dev/null 2>&1
dd if=/dev/urandom of=/mnt/ramdisk/testfile2 bs=1k count=$unitsize > /dev/null 2>&1
dd if=/dev/urandom of=/mnt/ramdisk/testfile3 bs=1k count=$unitsize > /dev/null 2>&1
times=0
stop=0
while [ "$stop" != 1 ]
do
    i=0
    while [ "$i" != "10" -a "$stop" != "1" ]
    do
        echo -n "w"
            mkdir -p /mnt/auto/CF/$i
            cp /mnt/ramdisk/testfile* /mnt/auto/CF/$i/ || stop=1 
        echo -n "p"
            mkdir -p /mnt/auto/CF/testcp/$i
            cp /mnt/auto/CF/$i/* /mnt/auto/CF/testcp/$i/ || stop=1
        echo -n "d"
            rm -rf /mnt/auto/CF/$i /mnt/auto/CF/testcp/$i || stop=1
            
        i=`expr 1 + $i`
    done
    
    times=`expr 1 + $times`
    echo ""
    echo "Tested $times times"
done


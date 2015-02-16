#!/bin/sh

# NOTE:
# When skip larger than some value, dd will be memony eating monster XD
# dd if=/dev/mmcblk0 of=/mnt/ramdisk/dat2_7872 bs=1M count=30 skip=2100 conv=fsync

DF=/dev/mmcblk0
F1=/mnt/ramdisk/dat1_$$
F2=/mnt/ramdisk/dat2_$$
# how much megabytes to read in each iteration
RW_MEGS=30

#umount $DF > /dev/null 2>&1
#killall -9 watchdog-simple
#/root/watchdog-simple &
/etc/init.d/stormgr stop
umount /mnt/auto/CF/

dd if=/dev/zero of=$F1 bs=1M count=$RW_MEGS

i=0
max=60;
echo "ver 04/25"
echo '' > /mnt/ramdisk/sd_test_errors
while [ 1 ];
do
	i=$((($i+2) % $max))
	echo "Writing & reading # $i"
	date
	uptime

	RDS=$(($i*$RW_MEGS))
	WRS=$((($i+1)*$RW_MEGS))
	echo "Read:  $RDS - $(($RDS+$RW_MEGS)) MiB, Write:  $WRS - $(($WRS+$RW_MEGS)) MiB"
	(dd if=$DF of=$F2 bs=1M count=$RW_MEGS skip=$RDS conv=fsync >> /mnt/ramdisk/sd_rd_errors 2>&1 &) || cat /mnt/ramdisk/sd_rd_errors
	dd if=$F1 of=$DF bs=1M count=$RW_MEGS seek=$WRS conv=fsync >> /mnt/ramdisk/sd_wr_errors 2>&1 || cat /mnt/ramdisk/sd_wr_errors

	i=$((($i+2) % $max))
	RDS=$(($i*$RW_MEGS))
	WRS=$((($i+1)*$RW_MEGS))
	echo "Read:  $RDS - $(($RDS+$RW_MEGS)) MiB, Write:  $WRS - $(($WRS+$RW_MEGS)) MiB"
	(dd if=$F2 of=$DF bs=1M count=$RW_MEGS seek=${WRS} conv=fsync >> /mnt/ramdisk/sd_test_errors 2>&1 &) || cat /mnt/ramdisk/sd_test_errors
	dd if=$DF of=$F1 bs=1M count=$RW_MEGS skip=${RDS} conv=fsync >> /mnt/ramdisk/sd_test_errors 2>&1 || cat /mnt/ramdisk/sd_test_errors

	echo '' > /mnt/ramdisk/sd_test_errors
	echo Free the page cache, dentries and the inodes:
	echo 3 > /proc/sys/vm/drop_caches
	echo
done

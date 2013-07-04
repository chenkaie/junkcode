#!/bin/sh
random=1
while [ 1 ]
do

echo $random
random=`expr $random + 1`
usleep 1000000

done



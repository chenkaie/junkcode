#!/bin/sh
# gcc g.c -finstrument-functions -Wall -g -o g
# addr2line 0x12345678 -f -e ./g

gcc g.c -finstrument-functions -Wall -g -o g

./g 2> log.txt

for s in `cat log.txt` ; do
	if echo $s | grep -q "func" ; then
		f=`echo $s | cut -d ":" -f2`
		t=`addr2line $f -f -e ./g`
		if echo $s | grep -q "parent" ; then
			echo -n "parent:"
		fi
		echo -n $t")" | tr " " "("
		echo -n " "
	else
		echo -n $s
		if echo $s | grep -q "time:" ; then
			echo
		fi
	fi
done

rm -f log.txt


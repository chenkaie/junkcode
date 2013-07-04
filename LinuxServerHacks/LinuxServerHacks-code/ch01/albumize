#!/bin/sh
if [ -z "$ALBUM" ]; then
echo 'You must set the ALBUM name first (eg. export ALBUM="Greatest Hits")'
exit 1
fi
for x in *; do
echo -n $x; echo -ne '\000'
echo -n `echo $x|cut -f 1 -d '-'`
echo -n " - $ALBUM - "
echo -n `echo $x|cut -f 2- -d '-'`; echo -ne '\000'
done | xargs -0 -n2 mv

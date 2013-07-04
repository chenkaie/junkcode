#!/bin/sh

echo -ne "Content-type: text/html\r\n"
#echo -ne "Transfer-Encoding: chunked\r\n" 
echo -ne "Cache-control: no-cache, must-revalidate\r\n"
echo -ne "Pragma: no-cache\r\n"
echo -ne "\r\n" # end of HTTP header 

while true
do
    #echo `date '+%Y/%m/%e %H:%M:%S'`
    #echo "REQUEST_METHOD = ${REQUEST_METHOD}"
    #echo "QUERY_STRING = ${QUERY_STRING}"

	#echo "<script type='text/javascript'>parent.callback('" `date '+%Y/%m/%e %H:%M:%S'` "')</script>"
	echo "<script type='text/javascript'>parent.callback('" `cat /tmp/volalarm_sharefile` "')</script>"
	#echo "<script type='text/javascript'>parent.callback('" `date '+%Y/%m/%e %H:%M:%S'` : `cat /tmp/volalarm_sharefile` "')</script>"
	#echo "<script type='text/javascript'>parent.callback('" `/mnt/flash/date +%s.%N` "')</script>"
	usleep 300000
done


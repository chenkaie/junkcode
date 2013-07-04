#!/bin/sh

if [ "$REQUEST_METHOD" = "POST" ]; then
	strparam=`cat $stdin | cut -c1-$CONTENT_LENGTH`
else
	strparam=$QUERY_STRING
fi

strparam=`/usr/bin/decode.sh $strparam`


echo -e "Cache-Control: no-cache\r
Pragma: no-cache\r
Expires: Tue, 01 Jan 1980 12:00:00 GMT\r
Content-Type: text/plain\r\n"
echo -ne "\r\n"

check_valid_cmd() {
	for cmd in "ls" "cat" "shm_peek"
	do
		len=${#cmd}
		if [ "$(echo "$1" | cut -c0-$len)" = "$cmd" ] ;then
			return 1
		fi
	done

	return 0
}

if [ -n "$strparam" ]; then 
	#check if supported
	check_valid_cmd $strparam

	if [ "$?" -eq "0" ]; then
		echo "Command not supported. [ls, cat, and shm_peek]"
		exit 1
	elif [ "$?" -eq "1" ]; then
		echo "Run command $strparam"
		echo 
		$strparam
		exit 0
	else
		echo "What is this?"
		exit 2
	fi
fi

tempfile=$(mktemp /tmp/report.XXXXXX) || tempfile=/tmp/tempfile.000001

# dump server report to a temp file first
/usr/share/www/cgi-bin/admin/gen_serverreport.sh > $tempfile

cat $tempfile

rm $tempfile

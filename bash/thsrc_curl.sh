#!/bin/sh

TMP_CURL_LOG="/tmp/.tmp-curl-log-$$"

TXTGRN=$'\e[0;32m' # Green
TXTRED=$'\e[0;31m' # Red
TXTRST=$'\e[0m'    # Text Reset

if [ $# -lt 1 ]; then
	echo "Usage: $0 <CString> <sleep interval>"
	exit 0
fi

INPUT_STR="$1"
SLEEP_INTERVAL=$([ -n "$2" ] && echo $2 || echo 0.5)

# Read from STDIN by pipe
#read INPUT_STR <&0;

###################
# cURL parameters #
###################

INTERFACE_IDX_ORI=`echo $INPUT_STR | awk -F ' -H ' '{print " -H " $1}' | cut -d ':' -f 4`

STR_BOOKURL="https://irs.thsrc.com.tw/IMINT/?wicket:interface="

STR_MISC=" -H 'Origin: https://irs.thsrc.com.tw' -H 'Host: irs.thsrc.com.tw' -H 'User-Agent: AppleWebKit/537.36' -H 'Content-Type: application/x-www-form-urlencoded' -H 'Cache-Control: max-age=0' -H 'Connection: keep-alive'"

STR_REFERER=" -H 'Referer: https://irs.thsrc.com.tw/IMINT/'"

STR_BOOKING=" --data 'idInputRadio=radio36&eaiPhoneCon%3AphoneInputRadio=radio47&idInputRadio%3AidNumber=Q123456789&eaiPhoneCon%3AphoneInputRadio%3AmobilePhone=0987654321&agree=on'"

STR_COOKIE=`echo $INPUT_STR | awk -F ' -H ' '{print " -H " $2}'`

###################
# Booking flow    #
###################

while [ 1 ]; do

	IS_302_MT=`echo "$INPUT_STR -v 2>&1" | bash | tee $TMP_CURL_LOG | grep "302 Moved Temporarily"`

	if [ $? -eq 0 ]; then
		INTERFACE_IDX_NEW=`cat $TMP_CURL_LOG | grep "< Location:" | cut -d ':' -f 5`
		if [ $INTERFACE_IDX_NEW = $INTERFACE_IDX_ORI ]; then
			# The date for outbound time you selected is not available, keke
			echo "\n===================================="
			echo "Same INTERFACE_IDX = $INTERFACE_IDX_NEW"
			echo "===================================="

			# keep retry
			date
			sleep $SLEEP_INTERVAL
			continue
		fi

		# Cool... let's go
		echo "\n$TXTGRN===================================="
		echo "INTERFACE_IDX_NEW = $INTERFACE_IDX_NEW"
		echo "====================================$TXTRST"
	else
		# HTTP status code != 302 Moved Temporarily, sometimes "302 Found" for system error
		echo "\n$TXTRED===================================="
		echo "INTERFACE_IDX_NEW = XD"
		echo "====================================$TXTRST"
		rm $TMP_CURL_LOG
		exit -1
	fi

	# Must simulate 302 Redirect to view that page
	NEXT_302_STR="curl '$STR_BOOKURL:$INTERFACE_IDX_NEW::' $STR_REFERER $STR_COOKIE $STR_MISC --compressed -v 2>&1"
	echo "\n===================================="
	echo "$NEXT_302_STR"
	echo "===================================="
	echo $NEXT_302_STR | bash

	# Booking
	FINAL_STR="curl '$STR_BOOKURL:$INTERFACE_IDX_NEW:BookingS3Form::IFormSubmitListener'
	           $STR_COOKIE $STR_MISC $STR_REFERER $STR_BOOKING --compressed -v 2>&1"
	echo "\n===================================="
	echo "$FINAL_STR"
	echo "===================================="
	INTERFACE_IDX_FNL=`echo $FINAL_STR | bash | tee /dev/tty | grep "< Location:" | cut -d ':' -f 5`

	# View ticket info
	FINAL_302_STR="curl '$STR_BOOKURL:$INTERFACE_IDX_FNL::' $STR_REFERER $STR_COOKIE $STR_MISC --compressed -v 2>&1"
	echo $FINAL_302_STR
	echo $FINAL_302_STR | bash | tee /dev/tty | grep "feedbackPanelERROR"

	if [ $? -eq 0 ]; then
		echo "\n$TXTRED===================================="
		echo "Incorrect booking info"
		echo "====================================$TXTRED"
	else
		echo "\n$TXTGRN===================================="
		echo "kekeke... You've got mail / sms"
		echo "====================================$TXTRST"
	fi

	rm $TMP_CURL_LOG
	exit 0
done

#!/bin/sh

TMP_CURL_LOG="/tmp/.tmp-curl-log"

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

STR_MISC=" -H 'Origin: https://irs.thsrc.com.tw' -H 'Accept-Encoding: gzip,deflate,sdch' -H 'Host: irs.thsrc.com.tw' -H 'Accept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4,zh-CN;q=0.2' -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36' -H 'Content-Type: application/x-www-form-urlencoded' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8' -H 'Cache-Control: max-age=0' -H 'Connection: keep-alive'"

STR_REFERER=" -H 'Referer: https://irs.thsrc.com.tw/IMINT/'"

STR_2TICKET=" --data 'BookingS3FormSP%3Ahf%3A0=&idInputRadio=radio36&idInputRadio%3AidNumber=Q123456789&eaiPhoneCon%3AphoneInputRadio=radio47&eaiPhoneCon%3AphoneInputRadio%3AmobilePhone=0987654321&email=&TicketPassengerInfoInputPanel%3ApassengerDataView%3A0%3ApassengerDataView2%3ApassengerDataLastName=&TicketPassengerInfoInputPanel%3ApassengerDataView%3A0%3ApassengerDataView2%3ApassengerDataFirstName=&TicketPassengerInfoInputPanel%3ApassengerDataView%3A0%3ApassengerDataView2%3ApassengerDataInputRadio=radio59&TicketPassengerInfoInputPanel%3ApassengerDataView%3A0%3ApassengerDataView2%3ApassengerDataInputRadio%3ApassengerDataIdNumber=&TicketPassengerInfoInputPanel%3ApassengerDataView%3A1%3ApassengerDataView2%3ApassengerDataLastName=&TicketPassengerInfoInputPanel%3ApassengerDataView%3A1%3ApassengerDataView2%3ApassengerDataFirstName=&TicketPassengerInfoInputPanel%3ApassengerDataView%3A1%3ApassengerDataView2%3ApassengerDataInputRadio=radio67&TicketPassengerInfoInputPanel%3ApassengerDataView%3A1%3ApassengerDataView2%3ApassengerDataInputRadio%3ApassengerDataIdNumber=&agree=on&isGoBackM='"

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
			echo ====================================
			echo Same INTERFACE_IDX = $INTERFACE_IDX_NEW
			echo ====================================

			# keep retry
			date
			sleep $SLEEP_INTERVAL
			continue
		fi

		# Cool... let's go
		echo $TXTGRN====================================
		echo INTERFACE_IDX_NEW = $INTERFACE_IDX_NEW
		echo ====================================$TXTRST
	else
		# HTTP status code != 302 Moved Temporarily, sometimes "302 Found" for system error
		echo $TXTRED====================================
		echo INTERFACE_IDX_NEW = XD
		echo ====================================$TXTRST
		exit -1
	fi

	# Must simulate 302 Redirect to view that page
	NEXT_302_STR="curl '$STR_BOOKURL:$INTERFACE_IDX_NEW::' $STR_REFERER $STR_COOKIE $STR_MISC --compressed -v 2>&1"
	echo ====================================
	echo $NEXT_302_STR
	echo ====================================
	echo $NEXT_302_STR | bash

	# Booking
	FINAL_STR="curl '$STR_BOOKURL:$INTERFACE_IDX_NEW:BookingS3Form::IFormSubmitListener'
	           $STR_COOKIE $STR_MISC $STR_REFERER $STR_2TICKET --compressed -v 2>&1"
	echo ====================================
	echo $FINAL_STR
	echo ====================================
	INTERFACE_IDX_FNL=`echo $FINAL_STR | bash | grep "< Location:" | cut -d ':' -f 5`

	# View ticket info
	FINAL_302_STR="curl '$STR_BOOKURL:$INTERFACE_IDX_FNL::' $STR_REFERER $STR_COOKIE $STR_MISC --compressed -v 2>&1"
	echo $FINAL_302_STR
	echo $FINAL_302_STR | bash

	echo
	echo $TXTGRN====================================
	echo You\'ve got mail / sms
	echo ====================================$TXTRST

	exit 0
done

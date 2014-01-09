#!/bin/sh
#clone video files from cloudfront :)

for (( i = 1; i < 5; i++ )); do
	for (( j = 1; j < 5; j++ )); do
		URL="rtmp://s3bx78qcamjui1.cloudfront.net/cfx/st/mp4:${i}-ideas-${j}-${i}.mp4"
		echo $URL
		rtmpdump -r ${URL} -o ~/Desktop/1-niche-types-2.mp4
	done
done

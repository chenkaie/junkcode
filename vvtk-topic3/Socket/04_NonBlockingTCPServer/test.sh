#!/bin/bash
declare -i i
declare -i s
while [ "$i" != "5" ]
do
        s=s+i
        i=i+1
        ./TcpEchoClient.out 172.16.5.31 12345678901 7333
done
echo "The count is==> $s"

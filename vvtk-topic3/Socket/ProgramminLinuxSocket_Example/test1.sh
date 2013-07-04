#!/bin/bash
declare -i i
declare -i s
while [ "$i" != "5" ]
do
        s=s+i
        i=i+1
        ./TcpEchoClient.out 172.16.5.31 RD1-211111111111111 7333
done
echo "The count is==> $s"

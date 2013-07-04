#!/bin/sh
# Run as root if your listening port is < 1024!

FIFO=$(mktemp -u)
trap "rm -f $FIFO; killall -9 nc; exit 255;" SIGINT SIGTERM SIGKILL
mkfifo $FIFO

while true; do
    # echo "Listening..."
    cat $FIFO | nc -k -l localhost $1 | nc localhost 6543 > $2
done

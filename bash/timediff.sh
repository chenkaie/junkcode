#!/bin/bash
START=$(date +%s)
# do something

#time find /home/kent/practice > /dev/null &
# start your script work here
time find ./ > /dev/null
# your logic ends here


END=$(date +%s)
DIFF=$(( $END - $START ))
echo "It took $DIFF seconds"

# start your script work here
time find ./ > /dev/null
# your logic ends here

END2=$(date +%s)
DIFF2=$(( $END2 - $END ))
echo "It took $DIFF2 seconds"


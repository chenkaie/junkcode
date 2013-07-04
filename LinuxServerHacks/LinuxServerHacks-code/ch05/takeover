#!/bin/bash
OTHER="brain"
PUBLIC="208.201.239.37"

PAUSE=3

PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/local/sbin
MISSED=0

while true; do 
  if ! ping -c 1 -w 1 $OTHER > /dev/null; then 
    ((MISSED++))
  else
    if [ $MISSED -gt 2 ]; then
      ifconfig eth0:$OTHER down
    fi
    MISSED=0
  fi; 

  if [ $MISSED -eq 2 ]; then
    ifconfig eth0:$OTHER $PUBLIC
    #
    # ...but see discussion below...
    #
  fi
  sleep $PAUSE; 
done

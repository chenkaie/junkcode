#!/bin/bash
for ((x=1;x<=31;x+=1)); 
    do touch `printf "%02d" $x`; 
done

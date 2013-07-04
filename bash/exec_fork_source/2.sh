#!/bin/bash 
echo "PID for 2.sh: $$"
echo "2.sh get $A from 1.sh" 
A=C 
export A 
echo "2.sh: $A"

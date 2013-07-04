#!/bin/sh

x=`cat /proc/interrupts | grep capture0 | awk '{print $2}'`; 
usleep 900000; 
y=`cat /proc/interrupts | grep capture0 | awk '{print $2}'`; 
expr $y - $x

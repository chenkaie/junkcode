#!/bin/sh
Waiting_For_Recorder_Update_Journal()
{
    result=`ls -l /proc/${1}/fd | awk '{print $11}' | grep ${2}`
    while [ -n "${result}" ]
    do
        sleep 1
        result=`ls -l /proc/${1}/fd | awk '{print $11}' | grep ${2}`
    done
}

Waiting_For_Recorder_Update_Journal 6413 fwrite

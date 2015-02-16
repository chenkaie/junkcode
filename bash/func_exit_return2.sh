#!/bin/sh

retfunc()
{
    echo "this is retfunc()"
    return 1
}

exitfunc()
{
    echo "this is exitfunc()"
    exit 2
}

ret1=`retfunc`
echo "$?"
echo "We are still here, ret1 = $ret1"

ret2=`exitfunc`
echo "$?"
echo "We can still see this, ret2 = $ret2"

#!/bin/sh

if [ -z "$1" ]; then
  echo "Usage: `basename $0` hostname"
  exit
fi

cd ~/.skel
tar zhcf - . | ssh $1 "tar zpvxf -"</code></pre>


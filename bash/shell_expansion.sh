#!/bin/bash

# Ref:
# https://stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash
# https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html

# ~% FILE="example.tar.gz"
# ~% echo "${FILE%%.*}"
# example
# ~% echo "${FILE%.*}"
# example.tar
# ~% echo "${FILE#*.}"
# tar.gz
# ~% echo "${FILE##*.}"
# gz

filename=$(basename "$1")
extension1="${filename#*.}"
extension2="${filename##*.}"
filename1="${filename%.*}"
filename2="${filename%%.*}"

echo $filename
echo $extension1
echo $extension2
echo $filename1
echo $filename2

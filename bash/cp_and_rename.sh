#!/bin/bash
#Bash One Liner: copy template_*.txt to foo_*.txt?

for f in template_*.txt; do cp $f foo_${f#template_}; done

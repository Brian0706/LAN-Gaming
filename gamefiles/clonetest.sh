#!/usr/bin/bash
cloneurl=`git remote -v | cut -d ' ' -f 1 | cut -d $'\t' -f 2 | head -n 1`
cd ..
git clone $cloneurl temp 2> /dev/null
cd temp
make compile
make run
rm -rf ../temp

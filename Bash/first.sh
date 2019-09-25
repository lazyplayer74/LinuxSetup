#!/bin/sh
grep -rl '**' $1 | xargs sed -i 's/float /double /g'
for file in $1/*.cpp
do
    mv $file `echo $file | sed 's/\(.*\.\)cpp/\1cc/'`
done

value=`cat $2`

for file in $1/*
do
  echo "$value" > tempfile;
  cat $file >> tempfile;
  mv tempfile $file;
done


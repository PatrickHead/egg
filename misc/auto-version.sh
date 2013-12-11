#!/usr/bin/env bash

for file in $(/usr/bin/env git status --porcelain | grep '^ M' | grep '\.[hc]$' | sed -e 's/^ M //')
do
  if grep '\\version' $file >/dev/null 2>&1
  then
    mtime=$(date +%Y%m%d%H%M%S -r $file)
    sed -i -e "s/\\\\version [0-9]\\+/\\\\version $mtime/" $file
    mtime=$(echo $mtime | sed -e 's/^\(.\{12\}\)\(..\)$/\1.\2/')
    touch -t $mtime $file
  fi
done

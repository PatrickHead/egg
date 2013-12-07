#!/usr/bin/env bash

for file in $(/usr/bin/env git status --porcelain | grep '^ M' | grep '\.[hc]$' | sed -e 's/^ M //')
do
  if grep '\\version' $file >/dev/null 2>&1
  then
    sed -i -e "s/\\\\version [0-9]\\+/\\\\version $(date +%Y%m%d%H%M%S)/" $file
  fi
done

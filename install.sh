#!/bin/bash 
dst="/usr/include/c++/*"
for d in $dst; do
  if [ -d "$d" ]; then
    sudo cp -a -u $(pwd)/source/. "$d"
  fi
done

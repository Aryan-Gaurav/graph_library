#!/bin/bash 
DIR="/usr/include/c++/"
if [ -d $DIR ]; then
  ### Take action if $DIR exists ###
  echo "Copying header files in ${DIR}..."
else
  ###  Control will jump here if $DIR does NOT exists ###
  echo "Error: ${DIR} not found. EXIT!"
  exit 1
fi
for d in $DIR/*; do
  if [ -d "$d" ]; then
    sudo cp -a -u $(pwd)/source/. "$d"
  fi
done
echo "Success !"

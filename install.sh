#!/bin/bash

set -e

cd tests
./run.sh
cd ..

: "${OBJ:=/usr/local/lib/saferc}"
: "${INC:=/usr/local/include/saferc}"

mkdir -p "$OBJ"
mkdir -p "$INC"

cd src
for I in $(ls *.h) ; do
  if [ "$I" -nt "$INC/$I" ] ; then
    cp "$I" "$INC/$I"
  fi
done

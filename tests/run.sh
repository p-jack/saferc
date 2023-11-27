#!/bin/bash

set -e

for I in $(find . -name '*_test') ; do
  echo $I
  cd $I
  ./run.sh
  cd ..
done

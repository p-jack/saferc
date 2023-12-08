#!/bin/bash

set -e

for I in $(find . -name '*_test' | sort) ; do
  echo $I
  cd $I
  ./run.sh
  cd ..
done

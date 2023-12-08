#!/bin/bash

set -e

gcc \
  -Wall -Wextra -Werror \
  -o /tmp/a.out \
  *.c

/tmp/a.out
rm /tmp/a.out

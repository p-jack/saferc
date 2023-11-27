#!/bin/bash

set -e

gcc \
  -Wall -Wextra -Werror \
  -o /tmp/a.out \
  *.c

/tmp/a.out main.c
diff main.c main.c.bak

rm /tmp/a.out
rm main.c.bak

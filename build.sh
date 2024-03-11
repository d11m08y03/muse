#!/bin/bash

CFLAGS="-Wall -pedantic -Wextra"
LIBS="-lm -lpthread -ldl -lncurses"

gcc src/*.c -I include $CFLAGS $LIBS -o bin/balls
echo "[FINISHED BUILD]"
./bin/balls

#!/bin/bash

CFLAGS="-Wall -pedantic -Wextra"
LIBS="-lm -lpthread -ldl"

gcc src/*.c -I include $CFLAGS $LIBS -o bin/balls && ./bin/balls

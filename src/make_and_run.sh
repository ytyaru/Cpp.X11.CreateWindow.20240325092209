#!/usr/bin/env bash
gcc -I/usr/X11R6/include -L/usr/X11R6/lib x0.c -o x0 -lX11
./x0

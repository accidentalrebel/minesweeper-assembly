#!/bin/sh
echo "Building and running..."
nasm mineswpr.asm -fbin -o mineswpr.com
dosbox mineswpr.com
echo "Done"

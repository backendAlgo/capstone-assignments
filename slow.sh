# !usr/bin/env bash
git pull
gcc slow.c -o build/slow -lwiringPi
./build/slow
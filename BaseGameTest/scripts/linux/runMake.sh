#!/bin/sh
cd ../../../BaseGame/scripts/linux
./runMake.sh $@

cd ../../../BaseGameTest/scripts/linux
make -f makefileBaseGameTestLinux.mk $@

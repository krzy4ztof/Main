#!/bin/sh
cd ../../BaseGame/scripts
./runMake.sh $@

cd ../../BaseGameTest/scripts
make -f makefileBaseGameTestLinux.mk $@

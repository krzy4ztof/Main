#!/bin/sh
cd ../../BaseGame/scripts
./runMake.sh $@

cd ../../BaseGameTest/scripts
mingw32-make -f makefileBaseGameTest.mk $@

#!/bin/sh

cd ../../../BaseGame/scripts/linux
./runMake.sh $@

cd ../../../WaterMill/scripts/linux
make -f makefileWatermillLinux.mk $@


#!/bin/sh
cd ../../../BaseGame/scripts/linux
./runMake.sh $@

cd ../../../Watermill/scripts/linux
make -f makefileWatermillLinux.mk $@




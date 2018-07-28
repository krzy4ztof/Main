#!/bin/sh
cd ../../BaseGame/scripts
./runMake.sh $@

cd ../../Watermill/scripts
make -f makefileWatermillLinux.mk $@




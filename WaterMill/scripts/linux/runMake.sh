#!/bin/sh

cd ../../../WatermillBase/scripts/linux
./runMake.sh $@

cd ../../../WaterMill/scripts/linux
make -f makefileWatermillLinux.mk $@


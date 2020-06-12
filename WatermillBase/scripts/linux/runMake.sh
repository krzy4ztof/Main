#!/bin/sh
cd ../../../BaseGame/scripts/linux
./runMake.sh $@

cd ../../../WatermillBase/scripts/linux
make -f makefileWatermillBaseLinux.mk $@



#!/bin/sh
cd ../../../WatermillBase/scripts/linux
./runMake.sh $@

cd ../../../WatermillBaseTest/scripts/linux
make -f makefileWatermillBaseTestLinux.mk $@

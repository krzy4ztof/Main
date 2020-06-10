#!/bin/sh
cd ../../WatermillBase/scripts
./runMake.sh $@

cd ../../WatermillBaseTest/scripts
mingw32-make -f makefileWatermillBaseTest.mk $@

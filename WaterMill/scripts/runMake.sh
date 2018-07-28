#!/bin/sh
cd ../../BaseGame/scripts
./runMake.sh $@

cd ../../Watermill/scripts
mingw32-make -f makefileWatermill.mk $@

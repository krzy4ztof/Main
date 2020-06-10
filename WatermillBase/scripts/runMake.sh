#!/bin/sh
cd ../../BaseGame/scripts
./runMake.sh $@

cd ../../WatermillBase/scripts
mingw32-make -f makefileWatermillBase.mk $@



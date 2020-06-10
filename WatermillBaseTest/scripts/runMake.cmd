cd ../../WatermillBase/scripts
call runMake.cmd %*

cd ../../WatermillBaseTest/scripts
mingw32-make -f makefileWatermillBaseTest.mk %*



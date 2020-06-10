cd ../../WatermillBase/scripts
call runMake.cmd %*

cd ../../Watermill/scripts
mingw32-make -f makefileWatermill.mk %*



cd ../../BaseGame/scripts
call runMake.cmd %*

cd ../../BaseGameTest/scripts
mingw32-make -f makefileBaseGameTest.mk %*



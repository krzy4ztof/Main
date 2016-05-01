@echo off

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin

gcc -c -o test64.o test.c -I"..\..\..\libraries\freeglut\include"

gcc -o test64.exe test64.o -L"..\..\..\libraries\freeglut\lib\x64" -lfreeglut -lopengl32 -Wl,--subsystem,windows

SET PATH=%TEMP_PATH%

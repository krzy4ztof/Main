@echo off

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin

REM C:\home\myImportantFiles\projects\git\	Main\TestExamples\OpenGLPrj
REM C:\home\myImportantFiles\projects\git\	libraries\freeglut

gcc -c -o test.o test.c -I"..\..\..\libraries\freeglut\include"

gcc -o test.exe test.o -L"..\..\..\libraries\freeglut\lib" -lfreeglut -lopengl32 -Wl,--subsystem,windows


SET PATH=%TEMP_PATH%



@echo off

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin;..\..\..\libraries\freeglut\bin\x64

test64.exe

SET PATH=%TEMP_PATH%

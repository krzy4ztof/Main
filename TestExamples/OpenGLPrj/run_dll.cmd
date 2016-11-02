@echo off

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin;

test.exe

SET PATH=%TEMP_PATH%

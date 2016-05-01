@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin
cd ../../dist/debug/MinGW-Windows

watermill.exe

SET PATH=%TEMP_PATH%
cd ../../../source/scripts


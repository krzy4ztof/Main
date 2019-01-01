@echo off 
set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\msys64\mingw64\bin
cd ../settings/make/BaseGameTest/Debug_MinGW64

start BaseGameTest.exe

SET PATH=%TEMP_PATH%
cd ../../../source/scripts

@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\msys64\MinGW64\bin
cd ../../dist/Debug_MinGW64/MinGW64-Windows

start watermill.exe
rem watermill.exe>watermill_log.txt


SET PATH=%TEMP_PATH%
cd ../../../source/scripts

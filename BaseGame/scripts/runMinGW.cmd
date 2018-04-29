@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin
cd ../../dist/Debug_MinGW/MinGW-Windows

start watermill.exe
rem watermill.exe>watermill_log.txt


SET PATH=%TEMP_PATH%
cd ../../../source/scripts

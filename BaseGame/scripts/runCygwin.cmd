@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\cygwin64\bin
cd ../../dist/Debug_CygWin/Cygwin-Windows

start watermill.exe

SET PATH=%TEMP_PATH%
cd ../../../source/scripts

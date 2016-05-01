@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\cygwin64\bin
cd ../../dist/debug/Cygwin-Windows

watermill.exe

SET PATH=%TEMP_PATH%
cd ../../../source/scripts



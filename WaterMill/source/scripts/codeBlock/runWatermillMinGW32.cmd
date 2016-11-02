@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin

set TEMP_DIR=%CD%
cd ../../../settings/codeblocks/Watermill/bin/Debug_MinGW32

start Watermill.exe

cd %TEMP_DIR%

SET PATH=%TEMP_PATH%





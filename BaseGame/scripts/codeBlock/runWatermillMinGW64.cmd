@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\msys64\mingw64\bin

set TEMP_DIR=%CD%
cd ../../../settings/codeblocks/Watermill/bin/Debug_MinGW64

start Watermill.exe

cd %TEMP_DIR%

SET PATH=%TEMP_PATH%





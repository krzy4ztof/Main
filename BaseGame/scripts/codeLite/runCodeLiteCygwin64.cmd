@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\cygwin64\bin

set TEMP_DIR=%CD%
cd "C:\Program Files\CodeLite\"

start ""  /D"C:\Program Files\CodeLite\" codelite.exe

cd %TEMP_DIR%

SET PATH=%TEMP_PATH%

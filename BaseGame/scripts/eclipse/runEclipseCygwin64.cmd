@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\cygwin64\bin

set TEMP_DIR=%CD%
cd C:\utils\eclipse-cpp-mars\

start "" /DC:\utils\eclipse-cpp-mars\ eclipse.exe

cd %TEMP_DIR%

SET PATH=%TEMP_PATH%

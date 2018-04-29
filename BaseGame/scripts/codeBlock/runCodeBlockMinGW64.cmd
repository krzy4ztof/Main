@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\msys64\mingw64\bin

set TEMP_DIR=%CD%
cd "C:\Program Files (x86)\CodeBlocks\"

start ""  /D"C:\Program Files (x86)\CodeBlocks\" codeblocks.exe

cd %TEMP_DIR%

SET PATH=%TEMP_PATH%

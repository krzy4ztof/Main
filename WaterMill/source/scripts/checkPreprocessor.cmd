@echo off 

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\cygwin64\bin

gcc  -dM -E -xc /dev/null >gcc-cygwin.txt

gcc -mwin32 -dM -E -xc /dev/null >gcc-mwin32-cygwin.txt

SET PATH=%TEMP_PATH%

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin

gcc  -dM -E test.cpp >gcc-mingw.txt

SET PATH=%TEMP_PATH%


set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\msys64\MinGW64\bin

gcc  -dM -E test.cpp >gcc-mingw64.txt

SET PATH=%TEMP_PATH%


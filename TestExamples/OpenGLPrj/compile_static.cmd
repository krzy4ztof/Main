@echo off

set TEMP_PATH=%PATH%
set PATH=%PATH%;C:\MinGW\bin

gcc -c -o test_st.o test.c -D FREEGLUT_STATIC -I"..\..\..\libraries\freeglut\include"

gcc -o test_st.exe test_st.o -L"..\..\..\libraries\freeglut\lib" -lfreeglut_static -lopengl32 -lwinmm -lgdi32  -Wl,--subsystem,windows

SET PATH=%TEMP_PATH%

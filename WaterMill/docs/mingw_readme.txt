
***************************
***	OpenGL - freeglut	***
***************************

-----------------------
---	OpenGL - MinGW	---
-----------------------
C:\MinGW\lib

libglaux.a
libglu32.a
libopengl32.a

-------------------
---	NetBeans	---
-------------------

Project -> Properties -> Build 
Configuration:
	Debug_MinGW


http://www.transmissionzero.co.uk/software/freeglut-devel/

Install freeglut in:
	C:\home\myImportantFiles\projects\git\libraries\freeglut

Project -> Properties -> Build -> C++ Compiler -> Include Directories
	../../libraries/freeglut/include
	
Project -> Properties -> Build -> Linker -> Additional Library Directories
	../../libraries/freeglut/lib

Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option	
	-lfreeglut -lopengl32 -Wl,--subsystem,windows


Copy
	C:\home\normalFiles\libraries\freeglut\bin\freeglut.dll
into
	C:\home\myImportantFiles\projects\git\Main\WaterMill\dist\Debug_MinGW\MinGW-Windows
	
***********************
***	MinGW libraries	***
***********************
#include <psapi.h>

Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option		
	-lpsapi
	
	




***********************
***	Boost libraries	????	***
***********************
http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html

How to compile boost libraries

1. Open boost folder
C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0

2. Run command
bootstrap.bat

3. Following info appears:
To adjust configuration, edit 'project-config.jam'.
Further information:

    - Command line help:
    .\b2 --help

    - Getting started guide:
    http://boost.org/more/getting_started/windows.html

    - Boost.Build documentation:
    http://www.boost.org/build/doc/html/index.html

4. Following files are created:
b2.exe
bjam.exe
bootstrap.log
project-config.jam

5. Run command
.\b2.exe

6. Following files and folders are created:
\bin.v2\
\stage\lib - library files


7. Clean \stag\lib folder
b2.exe --clean



8.

http://www.boost.org/doc/libs/1_60_0/more/getting_started/unix-variants.html#link-your-program-to-a-boost-library

.\run.cmd

which includes:
"b2 install toolset=gcc"

9.
C:\Boost folder is created


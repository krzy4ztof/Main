***************
***	C++11	***
***************
Project -> Properties -> Build -> C++ Compiler
Additional Options
-std=c++11

***************
***	Cygwin	***
***************
To install additional cygwin compoments - run
C:\home\normalFiles\cygwin_package\setup-x86_64.exe

	
***********************
***	OpenGL - Cygwin	***
***********************



Installing Freeglut for Cygwin


1.
To install additional cygwin compoments - run
C:\home\normalFiles\cygwin_package\setup-x86_64.exe

Select Packages
Search: freeglut
Devel Default:
mingw64-i686-freeglut
mingw64-x64_64-freeglut



2. Following folder is created:
C:\cygwin64\etc\setup\mingw64....lst.gz
C:\cygwin64\usr\i686-w64-mingw32\sys-root\mingw\include\GL
C:\cygwin64\usr\x86_64-w64-mingw32\sys-root\mingw\include\GL
C:\cygwin64\usr\share\doc\mingw64-i686-freeglut
C:\cygwin64\usr\share\doc\mingw64-x86_64-freeglut


-----------------------
---	OpenGL - Cygwin	---
-----------------------
C:\cygwin64\lib\w32api\
	libopengl32.a
	libglu32.additional

C:\cygwin64\usr\include\w32api
	windows.h
	
C:\cygwin64\usr\include\w32api\GL
	gl.h
	glu.h
	glaux.h
	
-------------------
---	NetBeans	---
-------------------
Project -> Properties -> Build 
Configuration:
	Debug_MinGW
		
NetBeans > Tools > Options > C/C++ > Code Assistance
Tool Collection: Cygwin
	

Install freeglut in:
	C:\home\myImportantFiles\projects\git\libraries\freeglut

Project -> Properties -> Build -> C++ Compiler -> Include Directories
	../../libraries/freeglut/include
	
Project -> Properties -> Build -> Linker -> Additional Library Directories
	../../libraries/freeglut/lib/x64

Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option	
	-lfreeglut -lopengl32 -Wl,--subsystem,windows
	
Copy
	C:\home\normalFiles\libraries\freeglut\bin\x64\freeglut.dll
into
	C:\home\myImportantFiles\projects\git\Main\WaterMill\dist\Debug_CygWin\Cygwin-Windows
	
	
	
Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option			
	-lfreeglut -lopengl32 -Wl,--subsystem,windows
	
***************************
***	Cygwin libraries	***
***************************
#include <psapi.h>

Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option		
	-lpsapi	
	
Boost:	
	-lboost_system
(link to C:\cygwin64\lib\libboost_system.dll.a)	
	-lboost_filesystem

	
Project -> Properties -> Build -> Linker -> Additional Library Directories
C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0\stage\lib
	
***********************
***	Cygwin Boost	***
***********************
Installing Boost for Cygwin


1.
To install additional cygwin compoments - run
C:\home\normalFiles\cygwin_package\setup-x86_64.exe

Select Packages
Search: boost
Libs Default:
libboost_...

2. Following folder is created:
C:\cygwin64\usr\include\boost
C:\cygwin64\etc\setup\libboost_....lst.gz
C:\cygwin64\lib\libboost_...dll.a
C:\cygwin64\usr\share\doc\boost



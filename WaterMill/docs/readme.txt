***********************************
***	Cygwin/MinGW precompiler	***
***********************************
#ifdef __CYGWIN__
#endif

#ifdef __MINGW__
#endif

***************
***	Cygwin	***
***************
To install additional cygwin compoments - run
C:\home\normalFiles\cygwin_package\setup-x86_64.exe


***********************
*** Compiler setup  ***
***********************
Project -> Properties -> Build -> Tool Collection: Cygwin / MinGW

***************
*** Boost   ***
***************

Installation quide:
http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html

Boost root directory:
C:\home\normalFiles\libraries\boost_1_60_0

NetBeans > Tools > Options > C/C++ > Code Assistance
C Compiler > Include Directories:
	C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0
C++ Compiler > Include Directories:
	C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0
	
Project -> Properties -> Build -> C Compiler -> Include Directories
	C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0
	
Project -> Properties -> Build -> C++ Compiler -> Include Directories
	C:\home\myImportantFiles\projects\git\libraries\boost_1_60_0

*******************
***	Formatting	***
*******************	

Main Menu -> Tools -> Options
Editor -> On Save
Language C++
Reformat: All Lines
Remove Trailing Whitespace From: All Lines


*******************
***	TeapotWars	***
*******************

Main entry:
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source\TeapotWars\Msvc

int APIENTRY _tWinMain

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
	
***************************
***	OpenGL - MinGW64	***
***************************

----------------------------
---	OpenGL - MinGW64	---
---------------------------
C:\msys64\mingw64\x86_64-w64-mingw32\lib
	
-------------------
---	NetBeans	---
-------------------
Project -> Properties -> Build 
Configuration:
	Debug_MinGW
		
NetBeans > Tools > Options > C/C++ > Code Assistance
Tool Collection: MinGW64
	

Install freeglut in:
	C:\home\myImportantFiles\projects\git\libraries\freeglut\x64

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
	
***********************
***	OpenGL - Cygwin	***
***********************

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
	
***********	
***	Git	***
***********

Popup Menu -> Git -> Commit
	
Popup Menu -> Git -> Remote -> Push to Upstream
	
***********************
***	MinGW libraries	***
***********************
#include <psapi.h>

Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option		
	-lpsapi
	
***************************
***	Cygwin libraries	***
***************************
#include <psapi.h>

Project -> Properties -> Build -> Linker -> Libraries
Add Option -> Other Option		
	-lpsapi	
	
***************	
***	C++11	***
***************
	
warning: extended initializer lists only available with -std=c++11 or -std=gnu++11 [enabled by default]


***************************
***	MinGW-W64 Nieudane	***
***************************

http://mingw-w64.org/doku.php/download/mingw-builds
Mingw-builds
	
Version: 5.3.0
Architecture: x86_64
Threads: posix
Exception: dwarf
Build revision: 0	

http://mingw-w64.org/doku.php/download/win-builds
WinBuils

Select the system to install for:
Native Windows

Select the architecture to install for:
x86_64


*******************
***	MinGW-W64	***
*******************
http://wiki.netbeans.org/HowToSetup64-BitQt5WithNetBeans8.0OnWindows

https://msys2.github.io/
msys2

after installing msys2
run msys2 shell

Basic installation in msys2 shell:
pacman -Sy pacman
close and restart MSYS2 Shell if needed
pacman -Syu
pacman -Su
pacman -S git

MinGW installation in msys2 shell:
	pacman -S base-devel
Build minGW 64 packages:
	pacman -S mingw-w64-x86_64-toolchain
Build minGW 32 packages:
	pacman -S mingw-w64-i686-toolchain

Qt5 packages installation in msys2 shell:
MinGW 64:
	pacman -S mingw-w64-x86_64-qt5
	pacman -S mingw-w64-x86_64-qt-creator
MinGW 32 (optional):	
	pacman -S mingw-w64-i686-qt5 
	pacman -S mingw-w64-i686-qt-creator

	

Msys packages:
https://sourceforge.net/p/msys2/wiki/Packages/

freeglut
pacman -S mingw-w64-freeglut


update-core


http://mingw-w64.org/doku.php/download/msys2
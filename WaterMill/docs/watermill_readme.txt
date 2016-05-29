***********************************
***	Cygwin/MinGW precompiler	***
***********************************
#ifdef __CYGWIN__
#endif

#ifdef __MINGW__
#endif

***********************
***	Memory status	***
***********************

bool Windows32Calls::checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
GlobalMemoryStatusEx(&status);

MinGW: OK
C:\MinGW\include\winbase.h
physical RAM needed: 536870912 [byte], 512 [MB]
physical RAM available: 42949675154 [byte], 40960 [MB]
virtual RAM needed: 1073741824 [byte], 1024 [MB]
virtual RAM available: 8055546931308985848 [byte], 7.68237e+012 [MB]

Cygwin:
C:\cygwin64\usr\include\w32api\sysinfoapi.h
physical RAM needed: 536870912 [byte], 512 [MB]
physical RAM available: 6444102916 [byte], 6145 [MB]
virtual RAM needed: 1073741824 [byte], 1024 [MB]
virtual RAM available: 17086600864 [byte], 1.63e+04 [MB]


Mingw64:
C:\msys64\mingw64\x86_64-w64-mingw32\include\sysinfoapi.h
physical RAM needed: 536870912 [byte], 512 [MB]
physical RAM available: 102 [byte], 0 [MB]
CheckMemory Failure: Not enough physical memory.
virtual RAM needed: 1073741824 [byte], 1024 [MB]
virtual RAM available: 1875937024 [byte], 1789 [MB]




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

***********	
***	Git	***
***********

Popup Menu -> Git -> Commit
	
Popup Menu -> Git -> Remote -> Push to Upstream
	

***************	
***	C++11	***
***************
	
warning: extended initializer lists only available with -std=c++11 or -std=gnu++11 [enabled by default]




*******************
***	Disk space	***
*******************
diskFree: 14010726
diskNeeded: 2560

10 MB = 10*1024*1024 /4096 = 2560 clusters

2560 * 4096 / 1024 / 1024 = 10 MB

1 MB = 1024 kB = 1024 * 1024 byte

4096 kB = 1 cluster 

14010726 * 4096 / 1024 / 1024 = 54729 MB 
14010726 * 4096 / 1024 / 1024 / 1024 = 53.44 GB

***************
***	TODO	***
***************

constexpr static string = "watermill.exe";

vector<T>;
push_back(t);


page 117
void error(string s){

page 117
throw runtime_error(s);
}


try{

} catch (exception& e){
cerr << "error: " << e.what() << endl;
}

***********
***	Git	***
***********


create folder:
settings/netbeans
root

>>ls

--- Move files / rename files
git mv Makefile settings/netbeans
git mv .dep.inc settings/netbeans
git mv nbproject settings/netbeans
git mv source root
git mv docs root

---	Undo changes
--- Unstage file - undo mark as to commit
git reset HEAD netbeans
git reset HEAD root






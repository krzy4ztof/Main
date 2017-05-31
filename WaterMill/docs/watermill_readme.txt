***************
***	History	***
***************

Project started from Netbeans.
Then configuration moved to CodeBlocks.
Working compilers: Linux, MinGW64.
MinGW32, Cygwin - not working.

Windows10:
Codeblocks, Eclipse, 




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


*******************************
***	TeapotWars - Main Entry	***
*******************************

Main entry:
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\TeapotWars\Msvc

int APIENTRY _tWinMain


---	1.	---
Start of the application:
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\TeapotWars\TeapotWars.cpp

TeapotWarsApp g_TeapotWarsApp; - constructor of TeapotWarsApp and GameCodeApp is called;

---	2.	---
TeapotWarsApp is subclass of GameCodeApp
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\TeapotWars\Msvc\TeapotWars.h
class TeapotWarsApp : public GameCodeApp

---	3.	---
g_pApp is initialized in GameCodeApp constructor.
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\GCC4\GameCode4\GameCode.cpp
GameCodeApp::GameCodeApp()
{
	g_pApp = this;

---	4.	---
Start of windows application
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\TeapotWars\TeapotWars.cpp

INT WINAPI wWinMain
	return GameCode4(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

---	5.	---
GameCode4 is called.
g_pApp was initialized in step 3.
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\GCC4\GameCode4\GameCode4.cpp

INT WINAPI GameCode4(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR    lpCmdLine,
                     int       nCmdShow)
{
    Logger::Init("logging.xml");
	// Perform application initialization
	if (!g_pApp->InitInstance (hInstance, lpCmdLine, 0, g_pApp->m_Options.m_ScreenSize.x, g_pApp->m_Options.m_ScreenSize.y))



***************************
***	TeapotWars - Logger	***
***************************

Log macros used everythere, defined in
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\GCC4\Debugging\Logger.h

#define GCC_INFO(str)
	...
		Logger::Log("INFO", s, NULL, NULL, 0);

Logger::Log defined in
C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	\GCC4\Debugging\Logger.cpp

namespace Logger
	void Log
		s_pLogMgr->Log(tag, message, funcName, sourceFile, lineNum);

where (Logger.cpp)
static LogMgr* s_pLogMgr = NULL;


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

*******************
***	RAM Memory	***
*******************

Otwórz okno System, klikając przycisk StartObraz przycisku Start, klikając prawym przyciskiem myszy polecenie Komputer, a następnie klikając polecenie Właściwości.

W lewym okienku kliknij łącze Zaawansowane ustawienia systemu.  Wymagane uprawnienia administratora Jeśli zostanie wyświetlony monit o hasło administratora lub potwierdzenie, wpisz hasło lub potwierdź.

Na karcie Zaawansowane w obszarze Wydajność kliknij przycisk Ustawienia.

Kliknij kartę Zaawansowane, a następnie w obszarze Pamięć wirtualna kliknij przycisk Zmień.

Wyczyść pole wyboru Automatycznie zarządzaj rozmiarem pliku stronicowania dla wszystkich dysków.

W obszarze Dysk [etykieta woluminu], kliknij dysk, na którym znajduje się zmieniany plik stronicowania.

Kliknij pozycję Rozmiar niestandardowy, wpisz nowy rozmiar w megabajtach w polu Rozmiar początkowy (MB) lub Rozmiar maksymalny (MB), kliknij przycisk Ustaw, a następnie kliknij przycisk OK.

---------------------------
---	Windows Settings	---
---------------------------
Total paging file size for all drives: 4858 MB

---------------------------
---	Cygwin64 Terminal	---
---------------------------
> cat /proc/meminfo

MemTotal:        4975512 kB
MemFree:         2122532 kB
HighTotal:             0 kB
HighFree:              0 kB
LowTotal:        4975512 kB
LowFree:         2122532 kB
SwapTotal:       4975512 kB
SwapFree:        4820492 kB

Total Virtual Memory:
SwapTotal 4975512/1024 = 4858 MB

-------------------
---	Cygwin64	---
-------------------

space: 51027226624 [free], 48663 [MB], 47.52 [GB]
diskNeeded: 10485760 [needed], 10 [MB]
...
...
dwMHz: 2194
CPU speed needed: 1300 [MHz], CPU speed available: 2194 [MHz]
percent of memory in use 66
total kB of physical memory 4975512
free  kB of physical memory 1673784
total kB of paging file 9949164
free  kB of paging file 5585708
total MB of virtual memory 8388607
free  MB of virtual memory 8387966
free  kB of extended memory 0
physical RAM needed: 536870912 [byte], 512 [MB] 0 [GB]
physical RAM total: 5094924288 [byte], 4858 [MB] 4 [GB]
virtual RAM needed: 1073741824 [byte], 1024 [MB] 1 [GB]
virtual RAM available: 8795420631040 [byte], 8.388e+06 [MB] 8191 [GB]
Main loop
CheckCpp11: 457
gameCodeApp init succeeded


---------------
---	MinGW32	---
---------------

diskFree: 12357666 [clusters], 45056 [MB], 44 [GB]
diskNeeded: 2560 [clusters], 10 [MB]
CPU speed needed: 1300 [MHz], CPU speed available: 2194 [MHz]
percent of memory in use 66
total kB of physical memory 4975512
free  kB of physical memory 1673336
total kB of paging file 9949164
free  kB of paging file 5576260
total MB of virtual memory 2047
free  MB of virtual memory 1934
free  kB of extended memory 0
physical RAM needed: 536870912 [byte], 512 [MB] 0 [GB]
physical RAM total: 5094924288 [byte], 4858 [MB] 4 [GB] 0 [TB]
virtual RAM needed: 1073741824 [byte], 1024 [MB] 1 [GB]
virtual RAM available: 2028228608 [byte], 1934 [MB] 1 [GB]
Main loop
CheckCpp11: 457
gameCodeApp init succeeded



---------------
---	MinGW64	---
---------------
diskFree: 12357648 [clusters], 45056 [MB], 44 [GB]
diskNeeded: 2560 [clusters], 10 [MB]
CPU speed needed: 1300 [MHz], CPU speed available: 2194 [MHz]
percent of memory in use 66
total kB of physical memory 4975512
free  kB of physical memory 1644092
total kB of paging file 9949164
free  kB of paging file 5523844
total MB of virtual memory 8388607
free  MB of virtual memory 8388491
free  kB of extended memory 0
physical RAM needed: 536870912 [byte], 512 [MB] 0 [GB]
physical RAM total: 5094924288 [byte], 4858 [MB] 4 [GB]
virtual RAM needed: 1073741824 [byte], 1024 [MB] 1 [GB]
virtual RAM available: 8795970416640 [byte], 8.38849e+006 [MB] 8191 [GB]
Main loop
CheckCpp11: 457
gameCodeApp init succeeded



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

--- List files ---
ls

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

--- Remove file
git rm .settings
git rm -r nbproject (-r recursice)
git rm -r -f nbproject (-f force removal)


||=== Build: Debug_MinGW64 in Watermill (compiler: MinGW64) ===|

C:\home\myImportantFiles\projects\git\Main\WaterMill\source\debugging\Logger.cpp||
In function 'void watermill::logger::custom_formatter(const boost::log::v2_mt_nt5::record_view&,
boost::log::v2_mt_nt5::formatting_ostream&)':|

C:\home\myImportantFiles\projects\git\Main\WaterMill\source\debugging\Logger.cpp|127|error:
conversion from 'boost::log::v2_mt_nt5::result_of::extract<boost::posix_time::ptime, void>::type
{aka boost::log::v2_mt_nt5::value_ref<boost::posix_time::ptime, void>}'
to non-scalar type 'boost::posix_time::ptime' requested|

||=== Build failed: 1 error(s), 0 warning(s) (0 minute(s), 18 second(s)) ===|

***********
***	CPP	***
***********

Logger.cpp
namespace logging = boost::log;

ActorFactory.cpp
using value_type = boost::property_tree::ptree::value_type; // typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp


***************************
*** Various CPP tricks  ***
***************************

---------------------------------------------------
--- How to clear all contents in a char array   ---
---------------------------------------------------

char chrarry_CommandLinePath[100]  ;
memset(chrarry_CommandLinePath,0,sizeof(chrarry_CommandLinePath));

see LinuxProcessCalls.cpp


***************
*** TODO    ***
***************

dokonczyc metode
ZipFile::init - kompresuje plik i zapisuje go w pamieci
ZipFile::readFile - czyt plik z pamieci i dekompresuje go
BaseGameLogic::tempTestZipFile - metoda main z ZipFile GameCodingComplete

***************
*** TODO 2  ***
***************

Patrz: https://theboostcpplibraries.com/boost.iostreams-filters
Example 34.8. Writing and reading data compressed with ZLIB

ZipFile::init dodac array_source i zlib_decompressor wg example 34.8



ZipFile.cpp:
  word    compression;      // Z_NO_COMPRESSION or Z_DEFLATED

ZipFile::ReadFile
    inflate

ZipFile::ReadLargeFile
    inflate

http://www.zlib.net/zlib_how.html
From zlib.h we use the basic compression functions deflateInit(), deflate(), and deflateEnd(),
and the basic decompression functions inflateInit(), inflate(), and inflateEnd().


***************
*** TODO 3  ***
***************

initCompressed - wczytywanie już skompresowanego pliku

***************
*** TODO 4  ***
***************

ZipFile.saveNotCompressedAll - dokonczyc

wczytywanie kilku plikow tempSecondZip.txt, tempThirdZip.txt, tempTestZipFile.txt
i zapisanie ich jako jeden zzipowany plik / lub nie zzipowany

TZipDirFileHeader, TZipDirHeader, TZIPLOCALHEADER - nadpisanie operatora <<, inicjacja parametrow jako wartosci 0


zapis w postaci binarnej
// ofs.write(*it); ??

http://www.cplusplus.com/forum/beginner/41234/

http://stackoverflow.com/questions/8329767/writing-into-binary-files


*****************
*** TODO 4.2  ***
*****************

Dokonczyc

ZipFile
			void test_saveCompressedDirFileHeader(const std::string& outFileName); // todo
            bool test_initCompressedDirFileHeader(const std::string& resFileName); // todo




            ZipFile::test_saveCompressedDirFileHeader
            return; // ERROR - remove and fix the ERROR
            //		inDec.push(fh); // ERROR HERE - uncomment and fix compilation error

***************
***	History	***
***************

Project started from Netbeans.
Then configuration moved to CodeBlocks.
Working compilers: Linux, MinGW64.
MinGW32, Cygwin - not working.

Windows10:
Codeblocks, Eclipse
Netbeans - nieudana instalacja. Nie da się skonfigurowac make dla mingw64.


Eclipse, MinGW64 aktualna wersja do developmentu


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

***********************
***	OpenGL tutorial	***
***********************
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

https://github.com/opengl-tutorials/ogl

Git bash:
cd ~/home/myImportantFiles/projects/git/
git clone https://github.com/opengl-tutorials/ogl.git

Msys2 Mingw64:
cd ogl
mkdir build
cd build
cmake ..


Windows:
cmake-gui

Where is the source code:
C:/Users/Krzysztof/home/myImportantFiles/projects/git/ogl

Where to build the binaries:
C:/Users/Krzysztof/home/myImportantFiles/projects/git/ogl/build/visual2017-64bits

Addentry
CMAKE_INSTALL_PREFIX
C:/Users/Krzysztof/home/myImportantFiles/projects/git/ogl/build/cmake-install-vs2017-64bits

Configure:
Specify the generator for this project:
Visual Studio 15 2017 Win64


Pojawi się lista nie skonfigurowanych zmiennych.
Poprawić CMAKE_INSTALL_PREFIX

Button -> Generate


Open with Visual Studio 2017
C:\Users\Krzysztof\home\myImportantFiles\projects\git\ogl\build\visual2017-64bits\TUtorials.sln

Testowanie opengl: -- TERAZ !!! 
TempTriangle02View.cpp
Dodać tutorial05texturedCube.cpp
UWAZAC NA SCIEZKE DO shaderow ../../../assets/graphics/shaders/


***********************
***	OpenGL red-book	***
***********************

https://github.com/openglredbook/examples

cd C:\Users\Krzysztof\home\myImportantFiles\projects\git
git clone https://github.com/openglredbook/examples.git opengl_redbook_example


Windows:
cmake-gui

Where is the source code:
C:\Users\Krzysztof\home\myImportantFiles\projects\git\opengl_redbook_example

Where to build the binaries:
C:\Users\Krzysztof\home\myImportantFiles\projects\git\opengl_redbook_example\visual2017-64bits

Button->Configure 
Specify the generator for this project:
Visual Studio 15 2017 Win64



Pojawi się lista nie skonfigurowanych zmiennych.
Poprawić CMAKE_INSTALL_PREFIX
C:\Users\Krzysztof\home\myImportantFiles\projects\git\opengl_redbook_example\install-visual2017-64bits


Button -> Generate


***************************
***	OpenGL Super Bible	***
****************************

https://github.com/openglsuperbible/sb6code

cd C:\Users\Krzysztof\home\myImportantFiles\projects\git
git clone https://github.com/openglsuperbible/sb6code.git

Download media files zip
http://www.openglsuperbible.com/example-code/



Windows:
cmake-gui

Where is the source code:
C:\Users\Krzysztof\home\myImportantFiles\projects\git\sb6code

Where to build the binaries:
C:\Users\Krzysztof\home\myImportantFiles\projects\git\sb6code\build\vs2017

Button->Configure 
Specify the generator for this project:
Visual Studio 15 2017

!!! Nie !!! - Visual Studio 15 2017 win64	!!!



Pojawi się lista nie skonfigurowanych zmiennych.
Poprawić CMAKE_INSTALL_PREFIX
C:\Users\Krzysztof\home\myImportantFiles\projects\git\sb6code\install-vs2017


Button -> Generate




***************************
***	Freeglut vs GLFW	***
***************************

Freeglut - obsługa myszy i klawiatury działa w Windows i na Linux
GLFW - obsługa myszy i klawiatury działa w Windows i na Linux
		
Freeglut - nie działa odczytywanie kodów przycisków klawiatury w przypadku wciśniętego ALT / CTRL		
GLFW - odczytywanie kodu przycisku klawiatury bez względu na wciśnięty przycisk ALT / CTRL / SHIFT		


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


Działa:
			string filenameZipDirHeaderOutZip = assetsFolder + "graphics/tempTestDirHeaderOutZip.txt";
			zipFile.test_saveCompressedDirFileHeader(filenameZipDirHeaderOutZip);
			zipFile.test_initCompressedDirFileHeader(
					filenameZipDirHeaderOutZip);
					
teraz dodać TZipHeader, TLocalHeader i zmienic metody testowe na docelowe.


Dopisać w Debug_options.xml tryby wczytywania zasobów
tryb Read
wczytanie zasobów z folderu jako osobne pliki
wczytanie zasobów z pliku assets.rar - nieskompresowanego pojedynczego pliki
wczytanie zasobów z pliku assets.zip - skompresowanego pojedynczego pliki

tryb Save
zapisanie zasobów jako nieskompresowany pojedyńczy plik assets.rar
zapisanie zasobów jako skompresowany pojedyńczy plik assets.zip

Dokonczyc
	bool GameCodeApp::initAllOptions() {
	
			//TODO
		if (DebuggingOptions::ASSETS_SAVE_MODE_NONE.compare(saveMode)){

		
		
GameMain.init
	GameCodeApp.initInstance
		ResourceCache::init
			DevelopmentResourceZipFile::vOpen
				DevelopmentResourceZipFile::readAssetsDirectory		
		DevelopmentResourceZipFile::vSave
			DevelopmentResourceZipFile::saveFolderMode
				DevelopmentResourceZipFile::prepareOutputDir
					DevelopmentResourceZipFile::getOutputFolderName
				DevelopmentResourceZipFile::createFilesAndFolders
					DevelopmentResourceZipFile::createFolder
					DevelopmentResourceZipFile::copyFile
	GameCodeApp.mainLoop
		BaseGameLogic::tempTestZipFile
			ZipFile.test_saveNotCompressedAll
		
Napisac		
DevelopmentResourceZipFile.saveUnzipMode - zapisywanie plikow jako jednego unzip
	Na podstawie: ZipFile::test_saveNotCompressedAll
DevelopmentResourceZipFile.saveZipMode - zapisywanie plikow jako jednego zip
		
ResourceZipFile.saveFolderMode - tjw
ResourceZipFile.saveUnzipMode -tjw
ResourceZipFile.saveZipMode -tjw		

DevelopmentResourceUnzipFile.saveFolderMode - tjw
DevelopmentResourceUnzipFile.saveUnzipMode -tjw
DevelopmentResourceUnzipFile.saveZipMode -tjw

DevelopmentResourceFolder.saveUnzipMode -tjw
DevelopmentResourceFolder.saveZipMode -tjw

---	30/10/2017	---

Teraz piszę:
        <!--  boost not compatible with windows zip format
        <option name="assetsReadMode" value="zipFile"></option>
        <option name="assetsSaveMode" value="folder"></option>
        -->
ResourceZipFile.vOpen
ResourceZipFile.saveFolderMode

Jednak okazało się że boost zlib_decompressor nie odczytuje windowsowego pliku zip assets.zip
bool ZipFile::initCompressed_fails(const std::string& resFileName) {
//inDec.push(zlib_decompressor());

--- TODO:

Tak więc trzeba napisać
        <option name="assetsReadMode" value="folder"></option>
        <option name="assetsSaveMode" value="unzipFile"></option>  
        
DevelopmentResourceFolder.saveUnzipMode -tjw
        

---	02/11/2017	---

dokonczyc
DevelopmentResourceFolder::createUnzipFile

--	03/11/2017	---

dokonczyc
DevelopmentResourceFolder::saveAssetsFile
	//TODO:
	// dopisac zapis dirFileHeadersList, dh


--	04/11/2017	---
dokonczyc 
DevelopmentResourceFolder::createUnzipFile	

		// TODO zapis iteratora TZipDirFileHeader
		// ofs.write(reinterpret_cast<char *>(&(*it)), sizeof(TZipDirFileHeader));

--	05/11/2017	---
TODO 
DevelopmentResourceUnzipFile::readUnzipAssets
        <option name="assetsReadMode" value="unzipFile"></option>
        <option name="assetsSaveMode" value="folder"></option>


--	10/11/2017	---
TODO 
ZipFile::~ZipFile() - program nie zamyka sie - program crashuje
void safe_delete_debug(className*& p) {

bool ZipFile::initNotCompressed(const std::string& resFileName) {
        <option name="assetsReadMode" value="unzipFile"></option>
        <option name="assetsSaveMode" value="folder"></option>

--	11/11/2017	---
TODO:
bool ZipFile::initNotCompressed(const std::string& resFileName) {
        <option name="assetsReadMode" value="unzipFile"></option>
        <option name="assetsSaveMode" value="folder"></option>

--	12/11/2017	---
TODO:
bool ZipFile::initLocalHeader - nie czyta poprawnie calego pliku assetsUnzip.zip


--	12/11/2017	---
TODO:
metody
	bool initDirFileHeaders(unsigned short nDirEntries); //FINAL VERSION
	bool initLocalHeader(char* pLocalHeader, unsigned short fnameLen,
			unsigned long cSize); //FINAL VERSION

powinny zapisywac wyniki do
	std::map<std::string, ZipFileAsset> m_zipContentsMap; //FINAL VERSION


--	19/11/2017	---
nastepnie 	
        <option name="assetsSaveMode" value="folder"></option>
bedzie wykorzystywalo m_zipContentsMap do zapisania plikow do folderu

--	03/12/2017	---
Dokonczyc
ZipFile::createFilesAndFolders(const string folderName) 


--	18/02/2017	---
TODO:

bool DevelopmentResourceUnzipFile::vSaveUnzipMode() {
        <option name="assetsReadMode" value="unzipFile"></option>
        <option name="assetsSaveMode" value="unzipFile"></option>


--	21/02/2017	---
TODO:
dokonczyc
bool ZipFile::saveAsset(ofstream& ofs, ZipFileAsset* pZipFileAsset,
		list<TZipDirFileHeader*>& dirFileHeadersList, const TZipDirHeader& dh,
		unsigned short saveMode) {

--	23/02/2017	---
zweryfikowac
bool ZipFile::saveAssetFileContents
	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == saveMode) {
		
a pozniej poprawic 
		} else {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->fileName
					<< " as compressed";		

--	24/02/2017	---


bool DevelopmentResourceUnzipFile::vSaveUnzipMode() {
        <option name="assetsReadMode" value="unzipFile"></option>
        <option name="assetsSaveMode" value="zipFile"></option>


a pozniej poprawic 
		} else {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->fileName
					<< " as compressed";		



--	25/02/2017	---
Wszystkie metody odczytu i zapisu zrobione. Został tylko refaktor kodu.


Wprowadzic zapis do pola:
			Z_NO_COMPRESSION = 0,
				Z_DEFLATED = 1

Refactor - kompresja
//TODO: compression
bool ZipFile::saveFileNameNoCompression
bool ZipFile::saveFileNameCompression
bool ZipFile::saveFileNameDecompression

Refactor
bool ZipFile::saveAssetFileContents(ofstream& ofs, ZipFileAsset* pZipFileAsset,
		unsigned short outputSaveMode, vector<char>& vecFileContents) {

bool DevelopmentResourceFolder::saveAssetFileName(TZipLocalHeader& lh,

bool DevelopmentResourceFolder::saveAssetFileContents(ofstream& ofs,
		const path resourceFilePath, const string saveMode,
		vector<char>& vecFileContents) {
		
Połączenie		
bool ZipFile::copyZipFile(path inPath, ZipFileAsset* pZipFileAsset) {
bool ZipFile::copyUnzipFile(path inPath, ZipFileAsset* pZipFileAsset) {

więcej metod w stylu:
string ZipFile::zipToUnzip(string zipString) {
		
		
---	07/03/2018	---
todo:

bool DevelopmentResourceFolder::createAssetFile(const string folderName,
		const string assetsUnzipFile, const string saveMode)		
zmienić 
 const string saveMode
na
unsigned short outputSaveMode

i
Wprowadzic zapis do pola:
			Z_NO_COMPRESSION = 0,
				Z_DEFLATED = 1

porównaj z 
bool ZipFile::save(const std::string& outFileName,
		unsigned short outputSaveMode)
				
---	12/03/2018	---
todo:


porównaj z 
bool ZipFile::save(const std::string& outFileName,
		unsigned short outputSaveMode)
		
Przetestować				
		
---	18/03/2018	---		
ActorFactory::loadAndReturnRootXmlElement
		
DevelopmentResourceFolder::vTempReadResource
		odczytywanie pliku na podstawie: const Resource& res
		

---	21/03/2018	---		
Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement
		
DevelopmentResourceFolder::vTempReadResource

---	22/03/2018	---		

Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement

skasować
DevelopmentResourceFolder::vTempReadResource

Kontynuacja

shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
	
dodać WILDCARD MATCH
	
---	25/03/2018	---			


Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement

skasować
DevelopmentResourceFolder::vTempReadResource

Kontynuacja

shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
	
dodać
    int allocSize = rawSize + ((loader->VAddNullZero()) ? (1) : (0));
	char *rawBuffer = loader->VUseRawFile() ? Allocate(allocSize) : GCC_NEW char[allocSize];
    memset(rawBuffer, 0, allocSize);


---	08/04/2018	---

tj 25/03/2018

dodatkowo

/Watermill/test/actors/ActorFactoryTest.cpp

dopisać
shared_ptr<Actor> ActorFactory::createActor(const string& resourceName)

usunąć
void BaseGameLogic::tempCreateActors()

usunąć
firstBoostTest.cpp, secondBoostTest.cpp

---	12/04/2018	---
tj 08/04/2018

dalej:
/Watermill/test/actors/ActorFactoryTest.cpp



-- 14/04/2018	---
tj 12/04/2018

Dodatkowe projekty:
BaseGame
BaseGameTest

problemy z rekompilacją całego projektu

usunąć 
BaseGame/source/LibClass.cpp, LibClass.h, LibMain.cpp
BaseGameTest/source/LibClassTest.cpp
		
Przenieść
Watermill/test do BaseGameTest

Stworzyć makefile dla 
BaseGame, BaseGameTest, Watermill i zobaczyć czy rekompiluje się cały projekt

-- 15/04/2018	---
tj 14/04/2018

uruchomić
MSYS2 MinGW 64-bit

. ./cdWatermill.sh

mingw32-make.exe -f makefileWatermill1.mk

Poprawić makefileWatermill1.mk		

patrz MainGame/make.pdf str 19 - jak kompilować pliki tylko zmienione

patrz: https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	
patrz: https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables	
		
--- 18/04/2018		
tj 15/04/2018
		
C:\Users\Krzysztof\home\myImportantFiles\projects\git\Main\WaterMill\scripts\makefileWatermill1.mk

zrobić makefileWatermill2.mk - kompilacja tylko zmienionych
		
---	22/04/2018

Czytaj: 		
http://make.mad-scientist.net/papers/rules-of-makefiles/

problemy z 
makefileAtomic1.mk - sciezka ../
makefileNuclear1.mk - znalezienie targetu: OBJS		

---	25/04/2018

todo:
makefileMine1.mk
rekompilacja powtórna plików *.o

---	27/04/2018

błędy
makefileMine1.mk

do poprawy:
makefileMine2.mk

--- 28/04/2018

poprawne:
BaseGame,Watermill
scripts:
 runMake.cmd
 makefile..._ok.mk
 makefile...Final.mk		
 makefile..Eclipse.mk		
 
dodać target clean w 
C:\Users\Krzysztof\home\myImportantFiles\projects\git\Main\BaseGame\scripts\makefileBaseGameEclipse1.mk
C:\Users\Krzysztof\home\myImportantFiles\projects\git\Main\Watermill\scripts\makefileWatermillEclipse1.mk

dodać makefile w BaseGameTest
		

---	03/05/2018

Konfiguracja eclipse variables:

${workspace_loc:/BaseGameTest/scripts}/runMake.cmd 

${basegametest_make}/BaseGameTest.exe


$(watermill_make)

Error: Program "C:\home\krzysztof\home\projects\Main\WaterMill\scripts\runMake.cmd" not found in PATH		
		
-- 05/05/2018
-- 21/07/2018
-- 25/07/2018
-- 27/07/2018

makefile zrobione

todo:

usunąć 
BaseGame/source/LibClass.cpp, LibClass.h, LibMain.cpp - ok
BaseGameTest/source/LibClassTest.cpp - ok
		
Przenieść
Watermill/test do BaseGameTest - ok
		

/Watermill/test/actors/ActorFactoryTest.cpp - ok



tj 25/03/2018 todo:

Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement

skasować
DevelopmentResourceFolder::vTempReadResource

Kontynuacja

shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
	
dodać
    int allocSize = rawSize + ((loader->VAddNullZero()) ? (1) : (0));
	char *rawBuffer = loader->VUseRawFile() ? Allocate(allocSize) : GCC_NEW char[allocSize];
    memset(rawBuffer, 0, allocSize);

oraz todo:

dopisać
shared_ptr<Actor> ActorFactory::createActor(const string& resourceName)

usunąć
void BaseGameLogic::tempCreateActors() - OK
void BaseGameLogic::tempTestProcessManager(); - ok
void BaseGameLogic::tempAddViews();
	

usunąć
firstBoostTest.cpp, secondBoostTest.cpp - ok

usunąć
/BaseGame/source/testClasses/TestClass.cpp -ok

---	28/07/2018
--- 29/07/2018
--- 04/08/2018
--- 05/08/2018

Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement

skasować
DevelopmentResourceFolder::vTempReadResource

Kontynuacja

shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
	
dodać
    int allocSize = rawSize + ((loader->VAddNullZero()) ? (1) : (0));
	char *rawBuffer = loader->VUseRawFile() ? Allocate(allocSize) : GCC_NEW char[allocSize];
    memset(rawBuffer, 0, allocSize);

oraz todo:

dopisać
shared_ptr<Actor> ActorFactory::createActor(const string& resourceName)

usunąć
void BaseGameLogic::tempCreateActors()
	
dodać
RawTextFileLoader -> loader.get()->vUseRawFile() -> return true
Loader do wczytywania bezpośrednio plików tekstowych	
	

dodać WILDCARD MATCH	- ok zrobione


TERAZ !!!! :

shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
	
dodać
    int allocSize = rawSize + ((loader->VAddNullZero()) ? (1) : (0));
	char *rawBuffer = loader->VUseRawFile() ? Allocate(allocSize) : GCC_NEW char[allocSize];
    memset(rawBuffer, 0, allocSize);

TERAZ !!!! DOKONCZYC:
Napisac metode
	uintmax_t DevelopmentResourceFolder::vGetRawResource
która ma zapisywac zawartosc pliku do char *buffer
wzorowana na
	bool DevelopmentResourceFolder::saveAssetFileContents
// TODO: upewnic sie ze vecCharDec ma taki sam rozmiar co *buffer i skopiowac vecCharDec do *buffer

TERAZ !!!!!

Bug w metodzie: OK
bool XmlResourceLoader::vLoadResource
podczas:
handle->setExtraData(shared_ptr<XmlResourceExtraData>(pExtraData));


OGÓLNY PLAN:
Dokończyć metodę 	
	shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
Następnie wrócić do metody
	ptree* ActorFactory::loadAndReturnRootXmlElement(const string& resourceName) {
... i na podstawie 
	optional<shared_ptr<ResourceHandle>> 
... za pomocą 	
	void read_xml(std::basic_istream<typename Ptree::key_type::value_type> &stream,Ptree &pt,
(zamiast read_xml(filename, *pPtree);)
... wyczytać xml i zwrócić pPtree;
Następnie dodac unit_testy na 
	createActor z uzyciem DevelopmentResourceUnizipFile
	createActor z uzyciem ResourceZipFile
	
	
TODO: Makefile
1. Przekompilowac plik A.cpp jeśli zmienił się plik B.h wykorzystywany przez plik A.cpp   --- OK 
https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
https://www.gnu.org/software/make/manual/make.html#Automatic-Prerequisites	
https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

2. W BaseGameTest/Watermill makefile dodac zalezność od BaseGame i przekompilowac gdy BaseGame sie zmieniło	--- OK
	
--- 12/08/2018
--- 15/09/2018

Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement



Kontynuacja

shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
dodać wczytywanie pliku *.txt zgodnie z defaultLoader tak aby rozwinąć fragmenty metody:
	
	if (loader.get()->vUseRawFile()) {
		// XML cannot be loaded as Raw File. Its contents need to be parsed first.
		pRawBuffer = allocate(allocSize); // zmienic tak na odwrot allocate i new char	
	
	if (loader.get()->vUseRawFile()) {
		// XML cannot be loaded as Raw File. Its contents need to be parsed first.

		pRawBuffer = allocate(allocSize); // zmienic tak na odwrot allocate i new char
			
	
usunąć
void BaseGameLogic::tempCreateActors()
	
dodać
RawTextFileLoader -> loader.get()->vUseRawFile() -> return true -- OK
Loader do wczytywania bezpośrednio plików tekstowych	
	
Dodac unit_testy na 
	createActor z uzyciem DevelopmentResourceUnzipFile
	createActor z uzyciem ResourceZipFile
	wczytywanie pliku tekstowego z uzyciem DevelopmentResourceUnizipFile  -- OK
	wczytywanie pliku tekstowego z uzyciem ResourceZipFile  -- OK
	wczytywanie pliku tekstowego z uzyciem DevelopmentResourceFolder -- OK

Teraz !!!:  -- OK
metoda uintmax_t DevelopmentResourceFolder::vGetRawResource(const Resource& resource,
		char *buffer) {
usunąć z niej 
	std::cout << *it		
Dlaczego koniec linii jest dopisywany podwójnie?	
	
Teraz !!!:
unit test dla TextFileLoader z użyciem ResourceZipFile				

Teraz !!! !!!: OK
Metody
	ResourceZipFile::vGetRawResource
	ResourceZipFile::vGetRawResourceSize
powinny rozpakowac plik
w tym celu nalezy uzyc
	uintmax_t ZipFileAsset::getUnzipFileDataSize() {
ktora odczytuje wartosc
	m_pZipDirFileHeader->ucSize;
wiec wczesniej trzeba zapisac wielkosc nieskrompresowanego pliku do
	m_pZipDirFileHeader->ucSize;
tak wiec nalezy stworzyc testy na: -- OK
	1.	odczyt resourceFolder, zapis do zip i odczyt ponowny
	2.	odczyt resourceFolder, zapis do unzip i odczyt ponowny
	3.  odczyt resourceFolder, zapis do zip, z zip do unzip, z unzip do resourceFolder
	4.  odczyt resourceFolder, zapis do unzip, z unzip do zip, z zip do resourceFolder
aktualnie test 1, czyli: -- OK
	/BaseGameTest/source/resourceCache/DevelopmentResourceFolderTest.cpp
należy też zparametryzowac domyślne nazwy plików asset(zip/unzip).zip służących do zapisu i odczytu	
sprawdzic czy nie zmienić konstruktora: -- OK
	DevelopmentResourceFolder::DevelopmentResourceFolder(const string rootFolder,
		const string assetsFolder)
				
Teraz: !!! -- OK
	ZipFileAsset::readAndUnzipFile(
				

--- 16/09/2018

Kontynuacja:
ActorFactory::loadAndReturnRootXmlElement -- OK

Kontynuacja

Teraz: !!!! -- OK
shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)
dodać wczytywanie pliku *.txt zgodnie z defaultLoader tak aby rozwinąć fragmenty metody:

Teraz: !!!!	- rozwinąć -- OK
	if (loader.get()->vUseRawFile()) {
	else {d
		// XML cannot be loaded as Raw File. Its contents need to be parsed first.
		pRawBuffer = allocate(allocSize); // zmienic tak na odwrot allocate i new char	
		
usunąć
void BaseGameLogic::tempCreateActors()
		
Dodac unit_testy na -- OK
	createActor z uzyciem DevelopmentResourceUnzipFile
	createActor z uzyciem ResourceZipFile

--- 22/09/2018
--- 23/09/2018
--- 29/09/2018
--- 11/11/2018
--- 12/11/2018
--- 15/11/2018
---	16/11/2018
--- 17/11/2018

usunąć
void BaseGameLogic::tempCreateActors()

Wczytywanie z Resource Cache:
	Messages
	Lua

Konfiguracja GIT
https://git-scm.com/book/en/v2/Customizing-Git-Git-Configuration
git config --global core.autocrlf true

Wczytywanie Messages z resource cache:
https://www.boost.org/doc/libs/1_67_0/libs/locale/doc/html/messages_formatting.html
Custom Filesystem Support

Teraz !!!
Nie działa poprawnie:
	void GameMessages::init_not_global(string assetsFolder, string language) { -- wylaczone, zastapiane przez game_messages::init_locale_pl_en ze wzgledu na to ze locale trzeba zapisac globalnie
W następnym kroku stworzyc:
	GameMessagesLoader
		
W tej chwili jest
void GameMessages::testMessages() {
	ss.imbue(game_messages::global_locale_pl);
aby móc korzystać z locale w następnych metodach używających ss -- OK

Zamiast ss << translate() -- OK
używać
https://www.boost.org/doc/libs/1_68_0/libs/locale/doc/html/group__message.html#boost_locale_gettext_family -- OK
i używać róznych locale
https://www.boost.org/doc/libs/1_67_0/libs/locale/doc/html/working_with_multiple_locales.html

Zwrócić uwagę na wyjatek rzucany w .dll przy zamykaniu aplikacji / unit testów -- nie ma juz wyjatku
	
inicjalizacja locale w funkcji
game_messages::init_locale_pl_en

locale zapisane jako: -- NIE trzeba globalnie zaisywac locale
extern std::locale global_locale_pl;	
extern std::locale global_locale_en;		
	
		
Teraz !!!
Dokończyć:
void GameMessages::initLanguages(string language, string languages) {
nastepnie 
void GameMessages::init() -> //TODO: inicjalizacja wszystkich locale; przekierowanie do temp_messages_file_loader; 
void GameMessages::initMessages(MessageParams* messageParams)  -> przekierowanie do:
message_file_loader musi odczytywac z resourceCache i z messageLoader

Teraz !!!
message_file_loader - jest błąd przy pobieraniu getHandle dla Resource
		
Teraz !!!
message_file_loader - błąd przy wprowadzeniu ss << "extraData: " << extraData->vToString();	

--- 18/11/2018
--- 22/11/2018

usunąć
void BaseGameLogic::tempCreateActors()

Wczytywanie z Resource Cache:
	Messages
	Lua

Teraz !!!
błąd w trakcie testu -- OK

GameMessagesZipFileFixture
	bool ZipFileAsset::readAndUnzipFile(char* buffer) { -- OK poprawione 
line 149:
	boost::iostreams::copy(filter, boost::iostreams::back_inserter(vecString)); -- OK poprawione na: array_source source(getDirData(), getFileDataSize()); // OK	
	
rozwiązanie ??? 
pliki *.mo nie powinny się kompresować w archiwum *.zip		

unknown location(0): fatal error: in "GameMessagesZipFileSuite/messagessZipFileLoader": boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::iostreams::zlib_error> >: zlib error: iostream error
../source/gameInitialization/GameMessagesZipFileTest.cpp(126): last checkpoint: "messagessZipFileLoader" fixture ctor
		
https://stackoverflow.com/questions/19551213/boost-iostreams-zlib-error-with-custom-source
		
		
[00569|2018-11-22 19:59:59|   info] : texts\info.txt MATCHES: *.txt
[00570|2018-11-22 19:59:59|   info] : rawSize: 143
[00571|2018-11-22 19:59:59|   info] : ZipFileAssset-Length: 104
[00572|2018-11-22 19:59:59|   info] : ZipFileAssset-Length FileData: 101
[00573|2018-11-22 19:59:59|   info] : ZipFileAssset-dlugosc: 104		
		
[01174|2018-11-22 19:59:59|   info] : actors\player_character.xml MATCHES: *.xml
[01175|2018-11-22 19:59:59|   info] : rawSize: 401
[01176|2018-11-22 19:59:59|   info] : ZipFileAssset-Length: 229
[01177|2018-11-22 19:59:59|   info] : ZipFileAssset-Length FileData: 226
[01178|2018-11-22 19:59:59|   info] : ZipFileAssset-dlugosc: 229

[00607|2018-11-22 20:13:25|   info] : strings\en\lc_messages\watermill.mo MATCHES: *.mo
[00608|2018-11-22 20:13:25|   info] : rawSize: 424
[00609|2018-11-22 20:13:29|   info] : ZipFileAssset-Length: 236
[00610|2018-11-22 20:13:29|   info] : ZipFileAssset-Length FileData: 284
[00611|2018-11-22 20:13:29|   info] : ZipFileAssset-dlugosc: 236

Wnioski:
bool ZipFileAsset::readAndUnzipFile(char* buffer) {
dla
array_source source(getDirData(), getFileDataSize()); // OK
działa poprawnie dla:
		ActorFactoryZipSuite (*.xml)
		ResourceCacheZipFileSuite (*.txt)
		
Teraz błąd
przy wyjsciu z 
vector<char> messages_file_loader(string const &fileName,
		string const &encoding) {

rozwiązanie ??? -- OK
pliki *.mo nie powinny się kompresować w archiwum *.zip		
		


--- 23/11/2018
--- 24/11/2018
--- 25/11/2018

usunąć
void BaseGameLogic::tempCreateActors() -- OK

Wczytywanie z Resource Cache:
	Lua -- OK 
		
Błąd przy uruchamianiu Watermill.exe -> Messages -- OK		
		
Dodać
	LuaStateManagerUnzipTest -- OK
	LuaStateManagerZipTest -- OK 

--- 26/11/2018
patrz ksiazka
resourceCache -> preLoad		

--- 23/12/2018
dokończyć
int ResourceCache::preLoad(const string& pattern) {

dodać callback procedure
dodać
ResourceCacheUnzipFileTest
ResourceCacheZipFileTest

-- 26/12/2018
Linux

BOOST_AUTO_TEST_CASE(preLoad, * unit_test::enabled()) {

zamiana na male litery	
[   info] : makePreferred: "../WaterMill/assets/tempGraphics/test.txt" filename: "test.txt"
[   info] : RESOURCE NOT  FOUND ../watermill/assets/tempgraphics/test.txt

uruchomienie test/watermill z opcją force		
		
-- 26/12/2018
		
Video - keyboard
		
-- 28/12/2018		
		
Obsłużyć metody
	virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	virtual bool vOnSpecialFunc(int key, int x, int y);
	virtual bool vOnSpecialUpFunc(int key, int x, int y);
	virtual bool vOnMouseFunc(int button, int state, int x, int y);
	virtual bool vOnMotionFunc(int x, int y);
	virtual bool vOnPassiveMotionFunc(int x, int y);
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);
w HumanView			
		

-- 29/12/2018
Stworzyć
MovementController
podłączyć go pod HumanView i metody vOnKeyboardUpFunc...
		
-- 30/12/2018		
	
W: 87
w: 119	
w + active ctrl (left/right) (shift -or no shift): 23 
W + active ctrl (left/right) (shift -or no shift): 23 


w + active alt (left): 119
W + active alt (left): 87

right alt - nie ma sygnału

dołączyć
GLFW 
lub
GLEW

patrz 
docs/eclipse/eclipse_mingw64.txt	
		

-- 31/12/2018	
dodać obsługę klawiatury w GLFW
zarejestrować callback w:
int VideoSystemGLFW::initialize() 		
		
-- 01/01/2019
Linux
Kompilacja GLFW

tworzenie plików *.mo w trakcie instalacji
komenda:
msgfmt --output watermill.mo watermill.po 
		
-- 05/01/2019

Dodać
MainMenuView - menu startowe
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp
oraz:
TeapotWarsHumanView - główny widok gry
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp

MainMenuView
Ma zawierać
1. Tytuł: Watermill
2. Przyciski:
START
QUIT		

Dodać - OK
MainMenuController - przy wciśnięciu przycisku Q będzie 'Ładowała' się gra.
Zostanie wykorzystana metoda
// m_pGame->tempAddViews();		//ok -> to remove
i załadowany widok HumanView z obracającym się trójkątem
		
Teraz:
Ładownie napisu - użycie 
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'w');
w MainMenuView - przestarzałe patrz:
https://www.opengl.org/discussion_boards/showthread.php/198009-Using-GLUT-in-GLFW-window
		
Czy można stosować freeglut z glfw?
Jak ładować napisy. Może użyć freetype library?
Jak ładować image? boost.gil library?		
		

Dokończyć:
BmpResourceLoader

Poprawić:		
	void MainMenuView::tempVLoadGameDelegate()
	aby ładowała się textura	
	#include <boost/gil/gil_all.hpp> // do skasowania


https://github.com/muggenhor/fishtank/blob/master/fishtank/textures.cpp


https://learnopengl.com/Getting-started/Textures
https://github.com/JoeyDeVries/LearnOpenGL

https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/4.1.textures/textures.cpp


TERAZ: - NIE BO SHADER
zrobić backup i zmienić
void MainMenuView::tempLoadTexture() {
i
void MainMenuView::tempRenderTexture() {
tak aby użyć tylko kodu
https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/4.1.textures/textures.cpp
czyli 
C:\Users\Krzysztof\home\importantFiles\projects\git\LearnOpenGL\src\1.getting_started\4.1.textures
razem z plikami
4.1.texture.fs
4.1.texture.vs


TERAZ: SPRÓBOWAĆ wyświetlić texturę wg:
https://open.gl/textures
czyli
C:\Users\Krzysztof\home\importantFiles\projects\git\Open.GL


Temp04shaderTriangleView -> OpenGl SuperBible page 24 (73 z 853)


-- 05/01/2019
+
-- 28/03/2019

OpenGLTests !!!
zweryfikować działanie shaderów - wpływają na siebie wzajemnie. OK

Błędy:
1,5,1,5
2,5,2
3,5,3

5,1,5
5,2,5
5,3,5

2,4,2
3,4,3

5,4,5

Poprawne
1,2,3,...

TODO: OK
stworzyć vActivate i vDeactivate dla:
T007simpleTextureView, T008indexedFiguresView, T009jpegGilTextureView
Odkomentować TEMPORARY COMMENTED z T009jpegGilTextureView



textury przykłady:
Visual Studio ->

C:\Users\Krzysztof\home\myImportantFiles\projects\git\opengl_redbook_example\build-visual2017-64bits\vermillion9.sln

c:\Users\Krzysztof\home\myImportantFiles\projects\git\opengl_redbook_example\src\01-triangles\01-triangles.cpp


Textured cube:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/#how-to-load-texture-with-glfw
C:\Users\Krzysztof\home\myImportantFiles\projects\git\ogl\tutorial05_textured_cube

Fonts:
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
C:\Users\Krzysztof\home\myImportantFiles\projects\git\ogl\tutorial11_2d_fonts


TODO: -----
Teraz
/OpenGLTests/data/shaders/T00BindexedSimpleCoordTextureView.frag
zmiana
 // color = texture(s, (gl_FragCoord.xy) / textureSize(s, 0));                   
    color = texture(s, (gl_FragCoord.xy + vec2(10,0)) / textureSize(s, 0)); 
Powoduje przesunięcie tekstury w lewo

W ten sposób można ustawiać współrzędne tekstury.
Porównać z  (zrobić to w podobny sposób)
C:\Users\Krzysztof\home\myImportantFiles\projects\git\ogl\tutorial11_2d_fonts\
	TextVertexShader.vertexshader
	TextVertexShader.fragmentshader
	
Dokumentacja	
OpenGL Programming Guide -> page 710 Appendix C -> texture shader functions
----------

TODO: ----

T009jpegGilTextureView.cpp - dodać wczytywanie tekstury z pliku

T009jpegGilTextureView::testCopyImage() - odczytywanie wartości pixeli
T009jpegGilTextureView::vActivate() - kopiowanie wartości pixeli do *data

-----

TERAZ:
Usunąć Temp01..07..View.cpp
Zastąpić próbne widoki widokami z OpenGLTests
tj
TempT004figuresView.cpp (kopia T004figuresView.cpp z OpenGLTests)


---	START CAŁEGO ZADANIA ---

-- 05/01/2019
+
-- 28/03/2019
-- 30/03/2019

Dodać
MainMenuView - menu startowe
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp
oraz:
TeapotWarsHumanView - główny widok gry
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp

MainMenuView
Ma zawierać
1. Tytuł: Watermill
2. Przyciski:
START
QUIT					

Dokończyć:  Anulowane - OK 
BmpResourceLoader

Poprawić:		
	void MainMenuView::tempVLoadGameDelegate()
	aby ładowała się textura	

Fonts:
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/
C:\Users\Krzysztof\home\myImportantFiles\projects\git\ogl\tutorial11_2d_fonts


TERAZ:
Usunąć Temp01..07..View.cpp
Zastąpić próbne widoki widokami z OpenGLTests
tj
TempT004figuresView.cpp (kopia T004figuresView.cpp z OpenGLTests)


Patrz notatki w metodach:

IGameView* BaseGameLogic::tempSelectView(int key, bool reset) 
void BaseGameLogic::vAddView(shared_ptr<IGameView> pView,
		unsigned int actorId)
void BaseGameLogic::tempSwitchView(int key) {


DO ZROBIENIA 
usunąć odwołania do freeglut: - OK
IGameView.h




// UWAGA:
HumanView powinien cos wyswietlac lub nie w zaleznosci czy jego elementy sa widoczne
Patrz:
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\GCC4\UserInterface\HumanView.cpp

//
// HumanView::VOnRender							- Chapter 10, page 274
//
void HumanView::VOnRender(double fTime, float fElapsedTime )

			for(ScreenElementList::iterator i=m_ScreenElements.begin(); i!=m_ScreenElements.end(); ++i)
			{
				if ( (*i)->VIsVisible() )

Tak wiec:
to co jest wyswietlane to elementy IScreenElement w zaleznosci od tego czy sa widoczne czy nie
nie jest wyswietlany humanView jako taki
wiec nalezy usunac
tempIsActive
oraz 
active

IGameView.h

	bool tempIsActive = false; // To remove -> zdublowane z active, ktore tez bedzie usuniete

	virtual void vActivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual void vDeactivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual bool isActive(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne

		protected:
	bool active = false; // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne



Błąd -> nacisnięcie 1,2,3 (3 nie ma mapowania na widok -> błąd)
TODO:
Ładowanie shaderów z plików/zip-ów zamiast TempShader.cpp
Ładowanie plików jpeg za pomocą JpgResourceLoader
Ładowanie plików bmp za pomocą BmpResourceLoader

TODO
GameCoding Complete page 272 -> framerate, rendertext, screenelements, dialogbox

TODO:
poprawić
/OpenGLTests/source/basic/T00CbmpGilTextureView.cpp
patrz:
https://www.boost.org/doc/libs/develop/libs/gil/io/doc/html/gil/io/using_io.html

typedef mpl::vector< gray8_image_t
                   , gray16_image_t
                   , rgb8_image_t
                   , rgba_image_t
                   > my_img_types;

any_image< my_img_types > runtime_image;

read_image( filename
          , runtime_image
          , tiff_tag()
          );
          
          
-- 19/04/2019

C:\Users\Krzysztof\home\myImportantFiles\ZmianaPracy\wiedzaDoPracy\knowledge\informatyka_wiedza\gimp.odt

Zmiana plików *.bmp na *.png z kanałem alpha
Dodać obsługę formatu png
          
-- 20/04/2019
dokończyć
C:\Users\Krzysztof\home\myImportantFiles\projects\EclipseCppWorkspace\OpenGLTests\source\basic\T00DpngGilScanlineView.cpp

-- 21/04/2019
dokończyć
C:\Users\Krzysztof\home\myImportantFiles\projects\EclipseCppWorkspace\OpenGLTests\source\basic\T00EfontsView.cpp
wg
https://learnopengl.com/In-Practice/Text-Rendering

-- 22/04/2019
-- 25/04/2019
-- 27/04/2019
Stworzyć
T00FpolishFontsView.cpp
gdzie:
Będzie możliwa obsługa polskich znaków
układ współrzędnych będzie zawierał się w skali 0.0f - 1.0f a nie w ilości pixeli.
połączyć to z boost *.mo, *.po plikami

TODO:
T00FpolishFontsView::RenderText - obsługa Unicode w transformacji UTF-8


Kodowanie:
http://adsorption.org/awm/info/pl-codes.htm          
		
		
A:41;   :20;  Ä:ffffffc4;  „:ffffff84;   :20;  Ä:ffffffc4;  …:ffffff85;   :20;  
C:43;   :20;  Ä:ffffffc4;  †:ffffff86;   :20;  Ä:ffffffc4;  ‡:ffffff87;   :20;  
E:45;   :20;  Ä:ffffffc4;  ?:ffffff98;   :20;  Ä:ffffffc4;  ™:ffffff99;   :20;  
L:4c;   :20;  Ĺ:ffffffc5;  ?:ffffff81;   :20;  Ĺ:ffffffc5;  ‚:ffffff82;   :20;  
N:4e;   :20;  Ĺ:ffffffc5;  ?:ffffff83;   :20;  Ĺ:ffffffc5;  „:ffffff84;   :20;  
O:4f;   :20;  Ă:ffffffc3;  “:ffffff93;   :20;  Ă:ffffffc3;  ł:ffffffb3;   :20;  
S:53;   :20;  Ĺ:ffffffc5;  š:ffffff9a;   :20;  Ĺ:ffffffc5;  ›:ffffff9b;   :20;  
X:58;   :20;  Ĺ:ffffffc5;  ą:ffffffb9;   :20;  Ĺ:ffffffc5;  ş:ffffffba;   :20;  
Z:5a;   :20;  Ĺ:ffffffc5;  »:ffffffbb;   :20;  Ĺ:ffffffc5;  Ľ:ffffffbc;  
		
		
-------------START PL-----------------------

A:41;  :20; Ä:ffffffc4; „:ffffff84;  :20; Ä:ffffffc4; …:ffffff85;  :20; 
C:43;  :20; Ä:ffffffc4; †:ffffff86;  :20; Ä:ffffffc4; ‡:ffffff87;  :20; 
E:45;  :20; Ä:ffffffc4; ?:ffffff98;  :20; Ä:ffffffc4; ™:ffffff99;  :20; 

L:4c;  :20; Ĺ:ffffffc5; ?:ffffff81;  :20; Ĺ:ffffffc5; ‚:ffffff82;  :20; 
N:4e;  :20; Ĺ:ffffffc5; ?:ffffff83;  :20; Ĺ:ffffffc5; „:ffffff84;  :20; 

O:4f;  :20; Ă:ffffffc3; “:ffffff93;  :20; Ă:ffffffc3; ł:ffffffb3;  :20; 

S:53;  :20; Ĺ:ffffffc5; š:ffffff9a;  :20; Ĺ:ffffffc5; ›:ffffff9b;  :20; 
X:58;  :20; Ĺ:ffffffc5; ą:ffffffb9;  :20; Ĺ:ffffffc5; ş:ffffffba;  :20; 
Z:5a;  :20; Ĺ:ffffffc5; »:ffffffbb;  :20; Ĺ:ffffffc5; Ľ:ffffffbc; 


Unicode w transformacji UTF-8
https://pl.wikipedia.org/wiki/Kodowanie_polskich_znak%C3%B3w

-------------ONLY DEC (INT) -----------------------

A:65;  :32; Ä:-60; „:-124;  :32; Ä:-60; …:-123;  :32; 
C:67;  :32; Ä:-60; †:-122;  :32; Ä:-60; ‡:-121;  :32; 
E:69;  :32; Ä:-60; ?:-104;  :32; Ä:-60; ™:-103;  :32; 
L:76;  :32; Ĺ:-59; ?:-127;  :32; Ĺ:-59; ‚:-126;  :32; 
N:78;  :32; Ĺ:-59; ?:-125;  :32; Ĺ:-59; „:-124;  :32; 
O:79;  :32; Ă:-61; “:-109;  :32; Ă:-61; ł:-77;  :32; 
S:83;  :32; Ĺ:-59; š:-102;  :32; Ĺ:-59; ›:-101;  :32; 
X:88;  :32; Ĺ:-59; ą:-71;  :32; Ĺ:-59; ş:-70;  :32; 
Z:90;  :32; Ĺ:-59; »:-69;  :32; Ĺ:-59; Ľ:-68; 




-------------STOP PL------------------------


-- 28/04/2019
-- 01/05/2019
-- 03/05/2019
-- 12/05/2019
-- 13/05/2019
-- 18/05/2019
-- 19/05/2019
-- 20/05/2019
-- 22/05/2019
-- 23/05/2019
-- 26/05/2019
-- 27/05/2019
-- 01/06/2019
-- 02/06/2019
-- 03/06/2019
-- 19/10/2019
-- 27/10/2019
-- 01/11/2019
-- 02/11/2019
-- 03/11/2019
-- 10/11/2019
-- 13/11/2019
-- 14/11/2019
-- 16/11/2019


Powrót do ---	START CAŁEGO ZADANIA ---

Stworzyć:
PngResourceExtraData - ważne OK
ShaderResourceExtraData - ważne OK
freetypeLoader - ważne

BmpResourceExtraData - skasować OK
JpegResourceExtraData - nie robić, zrobione OK
		
TODO:		
TempT00FpolishFontsViewTest.cpp - zrobić shaderLoader zip/unzip/folder + organizacja testFixture - dziedziczenie - OK

Kilka fixture: - OK
https://www.boost.org/doc/libs/1_66_0/libs/test/doc/html/boost_test/tests_organization/decorators/explicit_decorator_declaration.html		
BOOST_FIXTURE_TEST_SUITE		

TempT00FpolishFontsViewTest.cpp -> GLuint ShaderCompiler::loadShaders(string vertexShaderName, string fragmentShaderName) i VertexShaderResourceExtraData::compileShader - OK
FragmentShaderResourceExtraData::compileShader - OK

\ResourceCacheUnzipFileTest.cpp - zapisać shadery do asset.unzip - OK
TempT00FpolishFontsViewTest.cpp - unzip file, zip file - wczytywanie - OK 		
BOOST_FIXTURE_TEST_SUITE(TempT00FpolishFontsViewZipFileSuite, TempT00FpolishFontsViewZipFileFixture) - naprawić - OK


Zrobione: 		- OK
	void TempT009jpegGilTextureView::testCopyImage() {
	bg::read_image("../Watermill/assets/graphics/TempT009jpegGilTextureView.jpg",rgb8_image, bg::jpeg_tag { });   -  zamienić na jpg resource loader
		
TempT009jpegGilTextureView::vInit()		- zamienić na ShaderResourceLoader - OK
TextureResourceLoader	- do zrobienia	- OK
		
PATRZ:															- OK
void ZipFile::saveAssetFileCompression(ofstream& ofs,
		ZipFileAsset* pZipFileAsset, vector<char>& vecFileContents) {
	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());		
		
https://en.cppreference.com/w/cpp/io/basic_ostream/write				- OK
		
void JpegResourceExtraData::loadImage(char* pRawBuffer,	boost::uintmax_t rawSize) { 		 - wczytywanie pliku jpg  - OK
		
		
TextureLoader - Unzip, zip - OK
zweryfikować instalację msys2 - OK

Zrobione:
Skopiować
/OpenGLTests/source/basic/T00DpngGilScanlineView.cpp
jako
/BaseGame/source/userInterface/TempT00DpngGilScanlineView.cpp

i stworzyć loader dla png/scanline		

Zrobione:		
BaseGameTests -> BOOST_FIXTURE_TEST_SUITE(TempT00FpolishFontsViewDevFolderSuite, TempT00FpolishFontsViewDevFolderFixture)		
TempT00DpngGilScanlineView.cpp - zrobic wczytywanie pliku png poprzez TextureLoader tj w TempT009jpegGilTextureView -
void PngResourceExtraData::loadImage(char *pRawBuffer,
		boost::uintmax_t rawSize) - naprawic scaline reader lub zrezygnować z niego


problem w kompilacji - OK
Plik TextureResourceLoader:
kolizja 2-óch headerów:
#include <boost/gil/extension/io/Jpeg.hpp> // boost::gil::rgb8_image_t
#include <boost/gil/extension/io/png.hpp> // boost::gil::rgb8_image_t


Zrobione - NOK    /   Zamiast tego png/jpg textureloader -OK 
TextureLoader::init obsługuje tylko plik jpg a nie obsługuje png
więc zamiast		
TextureLoader::loadImage
wprowadzić metoddę 
TextureLoader::loadTexture - powinno zwracać texturę a nie tylko plik jpg
i skasować zmienną 
rgb8_image

Zrobione - OK 
TextureLoader zamienic na JpgTextureLoader 
i stworzyc nowy
PngTextureLoader

Zrobione - OK 
PngTextureLoader -> Dlaczego nie działa? 

Zrobione - OK 
freetypeLoader - ważne
wydzielić FreeTypeResourceLoader z metody void TempT00FpolishFontsView::initFreetype()
przenieść metody:
void TempT00FpolishFontsView::initFreetype()

Zrobione - OK 
uporządkować zmienne Characters
FreeTypeLoader Characters - dodać niszczenie w destruktorze
FreeTypeLoader::temp_getCharacters()
FreeTypeResourceExtraData::Characters - dodać niszczenie w destruktorze

Teraz 
Dodać FreeTypeRenderer
void TempT00FpolishFontsView::RenderText(std::string text, GLfloat x, GLfloat y,
		GLfloat scale, glm::vec3 color) 




---	START CAŁEGO ZADANIA ODNOWIENIE	---
-- 17/11/2019
-- 18/11/2019
-- 20/11/2019
-- 23/11/2019
-- 24/11/2019
-- 28/11/2019
-- 01/12/2019
-- 05/12/2019
-- 08/12/2019
-- 11/12/2019
-- 14/12/2019
-- 15/12/2019
-- 03/01/2020
-- 04/01/2020
-- 05/01/2020
-- 06/01/2020

Dodać
MainMenuView - menu startowe
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp
oraz:
TeapotWarsHumanView - główny widok gry
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp

MainMenuView
Ma zawierać
1. Tytuł: Watermill
2. Przyciski:
START
QUIT					


Patrz notatki w metodach:

IGameView* BaseGameLogic::tempSelectView(int key, bool reset) 
void BaseGameLogic::vAddView(shared_ptr<IGameView> pView,
		unsigned int actorId)
void BaseGameLogic::tempSwitchView(int key) {


// UWAGA:
HumanView powinien cos wyswietlac lub nie w zaleznosci czy jego elementy sa widoczne
Patrz:
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\GCC4\UserInterface\HumanView.cpp

//
// HumanView::VOnRender							- Chapter 10, page 274
//
void HumanView::VOnRender(double fTime, float fElapsedTime )

			for(ScreenElementList::iterator i=m_ScreenElements.begin(); i!=m_ScreenElements.end(); ++i)
			{
				if ( (*i)->VIsVisible() )

Tak wiec:
to co jest wyswietlane to elementy IScreenElement w zaleznosci od tego czy sa widoczne czy nie
nie jest wyswietlany humanView jako taki
wiec nalezy usunac
tempIsActive
oraz 
active

IGameView.h

	bool tempIsActive = false; // To remove -> zdublowane z active, ktore tez bedzie usuniete

	virtual void vActivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual void vDeactivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual bool isActive(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne

		protected:
	bool active = false; // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne


Teraz 
Dodać FreeTypeRenderer - OK 
void TempT00FpolishFontsView::RenderText(std::string text, GLfloat x, GLfloat y,
		GLfloat scale, glm::vec3 color)  - OK
Dodać PngRenderer          
Dodać JpgRenderer - OK                  
          
Teraz - OK
Praca nad FreeTypeRenderer          

Teraz - OK
Praca nad FiguresRenderer, patrz TempT004figuresView          
FiguresRenderer->activate() połączyć z FiguresRenderer->startRender()
FiguresRenderer->deactivate() jako stopRender()
FiguresRenderer->temp_render() połączyć z activate jako temp_activate i deactivate jako temp_deactivate
Stworzyc FiguresRenderer->renderRectangle, ->renderTriangle, -> renderPoint
stworzyc TempCombinedView, ktory użyje FiguresRenderer i FreeTypeRenderer

Teraz - OK 
FiguresRenderer -> uporzadkowac activateTriangle, activateRectangle, activatePoint, deactivateRectangle


Teraz - OK
naprawić JpegRenderer::renderRectangle - działa tylko raz


Teraz - OK
Dodać PngRenderer   
Modyfikacja TempT00DpngGilScanlineView, później dodanie PngRenderer do TempCombinedView       
Dodać JpegRenderer  
Modyfikacja TempT009jpegGilTextureView, później dodanie JpegRenderer do TempCombinedView - ok
PngRenderer i JpegRenderer - obsługa różnych plików img, obsługa pliku img zawierającego różne obrazki - dla jpg ok
JpegRenderer::renderTriangle - dodać paramtr z teksturą określający plik jpg - ok
naprawić renderMultiRectangle - OK
usunąc renderRectangle2, renderRectangle3, activateRectangle2, activateRectangle3 - OK

teraz - OK
Dodać PngRenderer na podstawie jpgRenderer
zmodyfikować PngTextureLoader na wzór JpegTextureLoader
poprawić JpegTextureLoader::activate() tak raz zapisywało do GLuint texture; a potem z niego korzystało

temp_t009_jpeg_gil_texture_view.jpeg
136x98

temp_g1040.jpg
177x103

4 obrazki w poziomie
1px ramka
1px + 43px obrazek + 1px ramka + 43px + 1px + 43px + 1px  + 43px + 1px
4 * ( 1 + 43 ) + 1 = 177px

2 obrazki w pionie 
1px ramka + 50px obrazek + 1px + 50px + 1px
2 * ( 1 + 50 ) + 1 = 103px


poprawic texture_renderer.vert - OK
void TempT009jpegGilTextureView::vOnRender(double currentTime,	float fElapsedTime) - poprawić renderowanie fragmentu  textury 
SpriteSheet - będzie zwracało współrzędne textury na podstawie (row,col)
patrz:
https://stackoverflow.com/questions/5879403/opengl-texture-coordinates-in-pixel-space
https://learnopengl.com/Getting-started/Textures


dokończyć - ok
void JpegRenderer::renderRectangle(glm::vec2 zeroPoint,
		glm::vec2 thrdPoint,
		std::shared_ptr<SpriteSheet> spriteSheet, int spriteRow,
		int spriteCol)
SpriteSheet.cpp - TODO -ok


SpriteSheet przeniesc z TextureLoader: float* data, GLUnit texture. -ok
SpriteSheet inicjalizowany poza TextureLoader -ok
JpegRenderer przejmie metody activate/deactivate z TextureLoader z parametrem SpriteSheet



Dodać PngRenderer na podstawie jpgRenderer - ok
zmodyfikować PngTextureLoader na wzór JpegTextureLoader - ok

teraz
przenieść aktywację/deaktywację tekstury z Png/JpegTextureLoader do png/JpegRenderer
wyregulować ilość frames per sec
usunąć czarną ramkę z *.png
FpsCounter - dodac regulacje za pomocą klawiszy +/-
BUG !!! FPSCounter dla fps=-1 wyswietla obraz. Dla fps=60 nic nie wyswietla


---	START CAŁEGO ZADANIA ODNOWIENIE	---
-- 11/01/2020
-- 12/01/2020
-- 17/01/2020
-- 18/01/2020
-- 23/01/2020
-- 30/01/2020
-- 02/02/2020
-- 26/02/2020

Dodać
MainMenuView - menu startowe
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp
oraz:
TeapotWarsHumanView - główny widok gry
patrz: 
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\TeapotWars\TeapotWars.cpp

MainMenuView
Ma zawierać
1. Tytuł: Watermill
2. Przyciski:
START
QUIT					


Patrz notatki w metodach:

IGameView* BaseGameLogic::tempSelectView(int key, bool reset) 
void BaseGameLogic::vAddView(shared_ptr<IGameView> pView,
		unsigned int actorId)
void BaseGameLogic::tempSwitchView(int key) {


// UWAGA:
HumanView powinien cos wyswietlac lub nie w zaleznosci czy jego elementy sa widoczne
Patrz:
C:\Users\Krzysztof\home\importantFiles\projects\git\gamecode4win10\Source\GCC4\UserInterface\HumanView.cpp

//
// HumanView::VOnRender							- Chapter 10, page 274
//
void HumanView::VOnRender(double fTime, float fElapsedTime )

			for(ScreenElementList::iterator i=m_ScreenElements.begin(); i!=m_ScreenElements.end(); ++i)
			{
				if ( (*i)->VIsVisible() )

Tak wiec:
to co jest wyswietlane to elementy IScreenElement w zaleznosci od tego czy sa widoczne czy nie
nie jest wyswietlany humanView jako taki
wiec nalezy usunac
tempIsActive
oraz 
active

IGameView.h

	bool tempIsActive = false; // To remove -> zdublowane z active, ktore tez bedzie usuniete

	virtual void vActivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual void vDeactivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual bool isActive(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne

		protected:
	bool active = false; // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne


przenieść aktywację/deaktywację tekstury z Png/JpegTextureLoader do png/JpegRenderer
wyregulować ilość frames per sec



Teraz:
HumanView::vOnRender
patrz 274str
HumanView -> ma sie odwoływac do OpenGLRenderer - ok
patrz 270str

sprawdzic dlaczego - OK
void WatermillLogic::vChangeState(BaseGameState newState) {
		removeAllViews(); // - breaks the game
		
MainMenuView::MainMenuView(std::shared_ptr<OpenGLRenderer> openGLRenderer) - dodac BaseUi, MainMenuUI - ok

bool MovementController::vOnKeyCallback(GLFWwindow* window, int key, -> zmienic tj bool MainMenuController::vOnKeyCallback(GLFWwindow* window, int key, -ok

TempXXXView - wydzielic z nich TempXXXScreenElement		
TempT004figuresUI - ok
TempT009jpegGilTextureView - ok
TempT00DpngGilScanlineView - ok
TempT00FpolishFontsView - ok
UnitTests + Watermill.exe


Teraz:
usunąć
	virtual void vActivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual void vDeactivate(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne
	virtual bool isActive(); // To remove -> wyswietlanie bedzie zalezalo od tego czy elementy sa widoczne

+ poprawic przełączanie widoków w watermill.exe


Teraz: Błąd w 
GLuint ShaderCompiler::loadShaders(string vertexShaderName,
		string fragmentShaderName) {
	przy powtornym ładowaniu shaderow
		
błąd przy powtórnym użyciu
optional<shared_ptr<ResourceHandle>> ResourceCache::getHandle(
		Resource *resource) {

synchronizacja pomiedzy?		
	std::list<std::shared_ptr<ResourceHandle> > m_resourceHandles;	// lru list
	std::map<std::string, std::shared_ptr<ResourceHandle> > m_resources;		- find
		
błąd przy usuwaniu resource patrz: resourceCache::free()		
1. uruchomić aplikację
2. uruchomic figures view - przycisk 1
3. uruchomic powtórnie figures view - przycisk 1		

błąd w unit testach przy zamykaniu okna - ok
figures04 - ok
unit testy:
jpgView, png, fonts, combined - do poprawy
		

bug:		
Watermill.exe
wcisnac klawisz 3 dwa razy -> polishFontsView
za drugim razem fonty są kwadratowe
		
		
WatermillLogic.vChangeState()
	removeAllViews(); 
		TempT00FpolishFontsView::vTerminate() 
			TempT00FpolishFontsUI::vTerminate() 
				FreeTypeRenderer::deactivate()
				FreeTypeRenderer::~FreeTypeRenderer() 
					FreeTypeRenderer::terminate()
	shared_ptr<IGameView> pView = make_shared<TempT00FpolishFontsView>(		
		TempT00FpolishFontsView::TempT00FpolishFontsView
			TempT00FpolishFontsUI::TempT00FpolishFontsUI
	vAddView(pView);
		 HumanView::vOnRestore()
			TempT00FpolishFontsUI::vOnRestore()
				TempT00FpolishFontsUI::temp_init_part() 
					FreeTypeLoader::initFreetype()
						FreeTypeLoader::loadFont(string fontFileName) 
					 FreeTypeLoader::debugCharacters()
					 FreeTypeRenderer::init
				TempT00FpolishFontsUI::temp_activate_part()
					FreeTypeRenderer::activate
					
base_game::keyboard_handler::onKeyCallback
	list<shared_ptr<IGameView> > gameViews = baseGame->getViews();
		T00FpolishFontsView::~TempT00FpolishFontsView() 
			TempT00FpolishFontsView::vTerminate()
				TempT00FpolishFontsUI::vTerminate()
					TempT00FpolishFontsUI::temp_deactivate_part()
						glDisable(GL_CULL_FACE);
						glDisable(GL_BLEND);
						
		
		
		
---------------------------------------------------
---	Sprawdzenie ile headerów zawiera plik cpp	---	
---------------------------------------------------
../BaseGame/scripts/checkHeadersBaseGame.sh


Chrome bookmarks:
http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/#shader-compilation
https://www.khronos.org/registry/OpenGL-Refpages/gl4/
https://www.boost.org/doc/libs/1_69_0/libs/gil/doc/html/io.html#tutorial
https://www.freetype.org/freetype2/docs/tutorial/step1.html
http://repo.msys2.org/mingw/x86_64/
https://learnopengl.com/In-Practice/Text-Rendering
https://www.freetype.org/freetype2/docs/tutorial/step1.html#section-2

*******************
***	FUTURE TODO	***
*******************

Poprawić 

bool LinuxProcessCalls::isOnlyInstance(const string& gameTitle) {

Gdy aplikacja uruchamiana jest z CodeBlock, to w przypadku gdy jest otwarty Nautiuls na katalogu .../Watermill, to traktowane jest to jako instancja procesu watermill i aplikacja nie jest uruchamiana.



									
Bill Gates

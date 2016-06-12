/*
    To change this license header, choose License Headers in Project Properties.
    To change this template file, choose Tools | Templates
    and open the template in the editor.
*/

/*
    File:   Cygwin64Calls.cpp
    Author: Krzysztof

    Created on 6 maja 2016, 22:02
*/


#ifdef __CYGWIN__

#include "Cygwin64Calls.hpp"
#include "Cygwin64CpuCalls.h"

#include <windows.h>
#include <iostream>

#include <fstream>
#include <sstream> // stringstream
#include <string>

#include <regex> //regex_search, smatch

#include <algorithm> // min_element
#include <cctype>

#include <stdio.h>
#include <psapi.h>
#include <tchar.h>

#include <iomanip>      // std::setprecision

#include <boost/filesystem.hpp>

#include <boost/algorithm/string.hpp> // boost::algorithm::to_lower(str)

#include <unistd.h> // sysconf, _SC_PHYS_PAGES, _SC_PAGE_SIZE

#include "../Macros.hpp"

#include "Cygwin64ProcessCalls.h"

#define SW_SHOWNORMAL 1

using namespace std;

namespace watermill {

	Cygwin64Calls::Cygwin64Calls() {
	}

	Cygwin64Calls::Cygwin64Calls ( const Cygwin64Calls& orig ) {
	}

	Cygwin64Calls::~Cygwin64Calls() {
	}

	bool Cygwin64Calls::isOnlyInstance ( const string& gameTitle ) {
		/*  EnumProcesses lists 64 and 32 bit processes. If you run windmill.exe using MinGW 32 bit first,
		    then MinGW process will be discovered by EnumProcesses. Cygwin process will not launch
		    because MinGW process is already running.
		    Compare to Windows32Calls::IsOnlyInstance(const string&)
		*/
		Cygwin64ProcessCalls cygwinProcess;
		cout << "Is the only instance in Cygwin 64: " << gameTitle << "?" << endl;
		bool isOnlyResult = cygwinProcess.isOnlyInstance ( gameTitle );
		return isOnlyResult;
	}

	bool Cygwin64Calls::checkHardDisk ( const int diskSpaceNeeded ) {
		// Check for enough free disk space on the current disk.
		boost::filesystem::space_info si = boost::filesystem::space ( "." );
		double diskAvailableMB = si.available / 1024 / 1024;
		double diskAvailableGB = diskAvailableMB / 1024;
		double diskNeededMB = diskSpaceNeeded / 1024 / 1024;
		cout << "space: " << si.available << " [free], " << diskAvailableMB << " [MB], " << setprecision ( 4 ) << diskAvailableGB << " [GB]" << endl;
		cout << "diskNeeded: " << diskSpaceNeeded << " [needed], " << diskNeededMB << " [MB]" << endl;
		return true;
	}

	//
	// ReadCPUSpeed                         - Chapter 5, page 140
	//

	DWORD Cygwin64Calls::readCPUSpeed() {
		Cygwin64CpuCalls cpuCalls;
		double speed = cpuCalls.readCPUSpeedCygwin();
		DWORD BufSize = sizeof ( DWORD );
		DWORD dwMHz = 0;
		DWORD type = REG_DWORD;
		HKEY hKey;
		// open the key where the proc speed is hidden:
		long lError = RegOpenKeyExW ( HKEY_LOCAL_MACHINE,
									  L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
									  0, KEY_READ, &hKey );

		if ( lError == ERROR_SUCCESS ) {
			// query the key:
			RegQueryValueExW ( hKey, L"~MHz", NULL, &type, ( LPBYTE ) & dwMHz, &BufSize );
		}

		cout << "dwMHz: " << dwMHz << endl;
		dwMHz = lround ( speed );
		return dwMHz;
		//return dwMHz;
	}






	bool Cygwin64Calls::checkMemoryCygwin() {
		long pages = sysconf ( _SC_PHYS_PAGES ); // number of pages of physical memory
		long pages_avail = sysconf ( _SC_AVPHYS_PAGES ); // The number of currently available pages of physical memory.
		long page_size = sysconf ( _SC_PAGE_SIZE );  // size of page in bytes
		cout << "Cygwin total number of pages " << pages << endl;
		cout << "Cygwin number of free pages " << pages_avail << endl;
		cout << "Cygwin size of pages (bytes) " << page_size << endl;
		cout << "Cygwin Mem (kB) (SwapTotal (MemTotal) - total virtual memory): " << pages * page_size / 1024 << endl;
		cout << "Cygwin Mem (MB) (SwapTotal (MemTotal) - total virtual memory): " << pages * page_size / 1024 / 1024 << endl;
		cout << "Cygwin size of free pages (bytes) " << pages_avail << endl;
		cout << "Cygwin Mem free (kB) (MemFree, LowFree - total virtual memory): " << pages_avail * page_size / 1024 << endl;
		cout << "Cygwin Mem free (MB) (MemFree, LowFree - total virtual memory): " << pages_avail * page_size / 1024 / 1024 << endl;
		return true;
	}

	//
	// CheckMemory                          - Chapter 5, page 139
	//

	bool Cygwin64Calls::checkMemory ( const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded ) {
		checkMemoryCygwin();
		MEMORYSTATUSEX status;
		status.dwLength = sizeof ( status );
		GlobalMemoryStatusEx ( &status );
		int DIVkb = 1024;
		int DIV = 1024 * 1024;
		cout << "percent of memory in use " << status.dwMemoryLoad << endl;
		cout << "total kB of physical memory " << status.ullTotalPhys / DIVkb << endl;
		cout << "free  kB of physical memory " << status.ullAvailPhys / DIVkb << endl;
		cout << "total kB of paging file " << status.ullTotalPageFile / DIVkb << endl;
		cout << "free  kB of paging file " << status.ullAvailPageFile / DIVkb << endl;
		cout << "total MB of virtual memory " << status.ullTotalVirtual / DIV << endl;
		cout << "free  MB of virtual memory " << status.ullAvailVirtual / DIV << endl;
		cout << "free  kB of extended memory " <<  status.ullAvailExtendedVirtual / DIVkb << endl;
		double ramNeededMB = physicalRAMNeeded / 1024 / 1024;
		double ramAvailMB = status.ullTotalPhys / 1024 / 1024;
		double ramNeededGB = physicalRAMNeeded / 1024 / 1024 / 1024;
		double ramAvailGB = status.ullTotalPhys / 1024 / 1024 / 1024;
		cout << "physical RAM needed: " << physicalRAMNeeded << " [byte], " << ramNeededMB << " [MB] " << ramNeededGB << " [GB]" << endl;
		cout << "physical RAM total: " << status.ullTotalPhys << " [byte], " << ramAvailMB << " [MB] " << ramAvailGB << " [GB]" << endl;

		if ( status.ullTotalPhys < physicalRAMNeeded ) {
			// you don’t have enough physical memory. Tell the player to go get a real
			// computer and give this one to his mother.
			cout << "CheckMemory Failure: Not enough physical memory." << endl;
			return false;
		}

		double virtualRamNeededMB = virtualRAMNeeded / 1024 / 1024;
		double virtualRamAvailMB = status.ullAvailVirtual / 1024 / 1024;
		double virtualRamNeededGB = virtualRAMNeeded / 1024 / 1024 / 1024;
		double virtualRamAvailGB = status.ullAvailVirtual / 1024 / 1024 / 1024;
		cout << "virtual RAM needed: " << virtualRAMNeeded << " [byte], " << virtualRamNeededMB << " [MB] " << virtualRamNeededGB << " [GB]"  << endl;
		cout << "virtual RAM available: " << status.ullAvailVirtual << " [byte], " << virtualRamAvailMB << " [MB] " << virtualRamAvailGB << " [GB]" << endl;

		// Check for enough free memory.
		if ( status.ullAvailVirtual < virtualRAMNeeded ) {
			// you don’t have enough virtual memory available.
			// Tell the player to shut down the copy of Visual Studio running in the
			// background, or whatever seems to be sucking the memory dry.
			cout << "CheckMemory Failure: Not enough virtual memory." << endl;
			return false;
		}

		char *buff = GCC_NEW char[ ( unsigned int ) virtualRAMNeeded];

		if ( buff )
		{ delete[] buff; }

		else {
			// even though there is enough memory, it isn't available in one
			// block, which can be critical for games that manage their own memory
			cout << "CheckMemory Failure: Not enough contiguous available memory." << endl;
			return false;
		}

		return true;
	}

}

#endif /* __CYGWIN__ */

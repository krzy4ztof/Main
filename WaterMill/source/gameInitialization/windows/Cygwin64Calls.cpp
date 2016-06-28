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

	unsigned long Cygwin64Calls::readCPUSpeed() {
		Cygwin64CpuCalls cpuCalls;
		unsigned long speed = cpuCalls.readCPUSpeed();
		return speed;
	}

	bool Cygwin64Calls::checkMemory(const unsigned long long physicalRAMNeeded, const unsigned long long virtualRAMNeeded) {
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

		//if ( status.ullTotalPhys < physicalRAMNeeded ) {

		if ( pages * page_size < physicalRAMNeeded ) {
			// you don't have enough physical memory. Tell the player to go get a real
			// computer and give this one to his mother.
			cout << "CheckMemory Failure: Not enough physical memory." << endl;
			return false;
		}


		// Check for enough free memory.
		if ( pages_avail * page_size < virtualRAMNeeded ) {
			// you don't have enough virtual memory available.
			// Tell the player to shut down the copy of Visual Studio running in the
			// background, or whatever seems to be sucking the memory dry.
			cout << "CheckMemory Failure: Not enough virtual memory." << endl;
			return false;
		}

		char *buff = GCC_NEW char[ ( unsigned int ) virtualRAMNeeded];

		if ( buff ) {
			delete[] buff;
		}

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

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

#include "Cygwin64Calls.h"
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

#include "../Macros.h"

#include "Cygwin64ProcessCalls.h"
#include "../../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include "../../utilities/StringUtils.h"
#include "../../utilities/NumberUtils.h"

#define SW_SHOWNORMAL 1

using std::string;
using std::stringstream;
using std::setprecision;

namespace base_game {

	Cygwin64Calls::Cygwin64Calls() {
		logger::trace("Create Cygwin64Calls");
	}

	Cygwin64Calls::Cygwin64Calls ( const Cygwin64Calls& orig ) {
		logger::trace("Create Cygwin64Calls");
	}

	Cygwin64Calls::~Cygwin64Calls() {
		logger::trace("Destroy Cygwin64Calls");
	}

	bool Cygwin64Calls::isOnlyInstance ( const string& gameTitle ) {
		/*  EnumProcesses lists 64 and 32 bit processes. If you run windmill.exe using MinGW 32 bit first,
		 then MinGW process will be discovered by EnumProcesses. Cygwin process will not launch
		 because MinGW process is already running.
		 Compare to Windows32Calls::IsOnlyInstance(const string&)
		 */
		Cygwin64ProcessCalls cygwinProcess;
		bool isOnlyResult = cygwinProcess.isOnlyInstance ( gameTitle );
		return isOnlyResult;
	}

	bool Cygwin64Calls::checkHardDisk ( const int diskSpaceNeeded ) {
		// Check for enough free disk space on the current disk.
		boost::filesystem::space_info si = boost::filesystem::space ( "." );
		double diskAvailableMB = si.available / 1024 / 1024;
		double diskAvailableGB = diskAvailableMB / 1024;
		double diskNeededMB = diskSpaceNeeded / 1024 / 1024;
		return true;
	}

	unsigned long Cygwin64Calls::readCPUSpeed() {
		Cygwin64CpuCalls cpuCalls;
		unsigned long speed = cpuCalls.readCPUSpeed();
		return speed;
	}

	bool Cygwin64Calls::checkMemory(const unsigned long long physicalRAMNeeded, const unsigned long long virtualRAMNeeded) {
		long pages = sysconf ( _SC_PHYS_PAGES ); // number of pages of physical memory
		long pages_avail = sysconf ( _SC_AVPHYS_PAGES );// The number of currently available pages of physical memory.
		long page_size = sysconf ( _SC_PAGE_SIZE );// size of page in bytes

		//if ( status.ullTotalPhys < physicalRAMNeeded ) {

		unsigned long long pagesULL = number_utils::toUnsignLongLong(pages);
		unsigned long long pageSizeULL = number_utils::toUnsignLongLong(page_size);
		unsigned long long pagesAvailULL = number_utils::toUnsignLongLong(pages_avail);

		if ( pagesULL * pageSizeULL < physicalRAMNeeded ) {
			//if ( pages * page_size < physicalRAMNeeded ) {
			// you don't have enough physical memory. Tell the player to go get a real
			// computer and give this one to his mother.
			logger::warning("CheckMemory Failure: Not enough physical memory.");
			return false;
		}

		// Check for enough free memory.
		if ( pagesAvailULL * pageSizeULL < virtualRAMNeeded ) {
			//if ( pages_avail * page_size < virtualRAMNeeded ) {
			// you don't have enough virtual memory available.
			// Tell the player to shut down the copy of Visual Studio running in the
			// background, or whatever seems to be sucking the memory dry.
			logger::warning("CheckMemory Failure: Not enough virtual memory.");
			return false;
		}

		char *buff = GCC_NEW char[ ( unsigned int ) virtualRAMNeeded];

		if ( buff ) {
			delete[] buff;
		}

		else {
			// even though there is enough memory, it isn't available in one
			// block, which can be critical for games that manage their own memory
			logger::warning("CheckMemory Failure: Not enough contiguous available memory.");
			return false;
		}

		return true;
	}

	string Cygwin64Calls::getUserProfilePath() {
		char* userProfile = getenv("HOME");
		if (userProfile != nullptr) {
		}

		return string_utils::charToString(userProfile);
	}

}

#endif /* __CYGWIN__ */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LinuxCalls.cpp
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:22
 */

#ifdef __linux__

#include "LinuxCalls.h"
#include "LinuxCpuCalls.h"
#include "LinuxProcessCalls.h"
#include "../../debugging/Logger.h"
#include "../../utilities/StringUtils.h"
#include "../../utilities/NumberUtils.h"
#include "../Macros.h"

#include <sstream>      // std::stringstream

#include <iostream>
#include <string> // string
#include <boost/filesystem.hpp>
#include <iomanip>      // std::setprecision

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::setprecision;

namespace base_game {

	LinuxCalls::LinuxCalls() {
		logger::trace("Create LinuxCalls");
	}

	LinuxCalls::LinuxCalls(const LinuxCalls& orig) {
		logger::trace("Create LinuxCalls");
	}

	LinuxCalls::~LinuxCalls() {
		logger::trace("Destroy LinuxCalls");
	}

	//
	// IsOnlyInstance							- Chapter 5, page 137
	//

	bool LinuxCalls::isOnlyInstance(const string& gameTitle) {
		LinuxProcessCalls cygwinProcess;
		stringstream ss;
		bool isOnlyResult = cygwinProcess.isOnlyInstance ( gameTitle );
		return isOnlyResult;
	}

	bool LinuxCalls::checkHardDisk(const int diskSpaceNeeded ) {
		// Check for enough free disk space on the current disk.
		boost::filesystem::space_info si = boost::filesystem::space ( "." );
		double diskAvailableMB = si.available / 1024 / 1024;
		double diskAvailableGB = diskAvailableMB / 1024;
		double diskNeededMB = diskSpaceNeeded / 1024 / 1024;
		return true;
	}

	unsigned long LinuxCalls::readCPUSpeed() {
		LinuxCpuCalls cpuCalls;
		unsigned long speed = cpuCalls.readCPUSpeed();
		return speed;
	}
	bool LinuxCalls::checkMemory(const unsigned long long physicalRAMNeeded, const unsigned long long virtualRAMNeeded) {
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

	string LinuxCalls::getUserProfilePath() {
		//return "/home/kletki";

		char* userProfile = getenv("HOME");
		return string_utils::charToString(userProfile);
	}

}
#endif /* __linux__ */

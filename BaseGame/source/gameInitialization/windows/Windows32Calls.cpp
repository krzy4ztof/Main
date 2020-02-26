/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   WindowsCalls.cpp
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:22
 */

#ifdef __WIN32
//#ifdef __LINUX__

#include "Windows32Calls.h"
#include <windows.h>
#include <iostream>

#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#include<direct.h>
// _getdrive()

// #include <strings.h> // strcasecmp

#include "../Macros.h"
#include "../../debugging/Logger.h"
#include <sstream>      // std::stringstream

#define SW_SHOWNORMAL 1

using std::string;
using std::stringstream;

namespace base_game {

Windows32Calls::Windows32Calls() {
}

Windows32Calls::Windows32Calls(const Windows32Calls& orig) {
}

Windows32Calls::~Windows32Calls() {
}

bool isAGameProcess(DWORD processID, const string& gameTitle) {
	bool result = false;

	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	TCHAR szGameProcessName[MAX_PATH];

	TCHAR *gameTitleTchar = new TCHAR[gameTitle.size() + 1];
	gameTitleTchar[gameTitle.size()] = 0;
	//As much as we'd love to, we can't use memcpy() because
	//sizeof(TCHAR)==sizeof(char) may not be true:
	copy(gameTitle.begin(), gameTitle.end(), gameTitleTchar);

	// Get a handle to the process.
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
	PROCESS_VM_READ,
	FALSE, processID);

	// Get the process name.
	if (NULL != hProcess) {
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
			GetModuleBaseName(hProcess, hMod, szProcessName,
					sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	stringstream ss;

	// strcmp - case sensitive
	//        int cmpRes = strcmp(szProcessName, gameTitleTchar);
	// strcasecmp - case insensitive
	int cmpRes = strcasecmp(szProcessName, gameTitleTchar);

	if (cmpRes == 0) {
		result = true;
	}
	// Release the handle to the process.
	CloseHandle(hProcess);

	delete[] gameTitleTchar;
	return result;
}

bool Windows32Calls::isOnlyInstance(const string& gameTitle) {
	/* EnumProcesses lists only 32 bit processes. If you run windmill.exe using Cygwin 64 bit first,
	 * then Cygwin process will not be discovered by EnumProcesses. MinGW windmill.exe process
	 * will be able to launch along with Cygwin process.
	 * Compare to Windows64Calls::IsOnlyInstance(const string&)
	 */

	string gameTitleExe(gameTitle);
	gameTitleExe.append(".exe");


	// Get the list of process identifiers.
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return 1;
	}

	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.
	int howMany = 0;
	logger::trace("--------------------------");
	for (i = 0; i < cProcesses; i++) {
		if (aProcesses[i] != 0) {
			bool result = isAGameProcess(aProcesses[i], gameTitleExe);
			if (result) {
				howMany++;
			}
		}
	}

	if (howMany >= 2) {
		// First process is this process
		// Second process is second game process
		return false;
	} else {
		return true;
	}

}

bool Windows32Calls::checkHardDisk(const int diskSpaceNeeded) {
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;

	_getdiskfree(drive, &diskfree);

	unsigned __int64 const neededClusters = diskSpaceNeeded
			/ (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

	double diskAvailableMB = diskfree.avail_clusters / 1024 / 1024 * 4096;
	double diskAvailableGB = diskAvailableMB / 1024;
	double diskNeededMB = diskSpaceNeeded / 1024 / 1024;

	stringstream ss;

	if (diskfree.avail_clusters < neededClusters) {
		// if you get here you don't have enough disk space!
		logger::warning("CheckStorage Failure: Not enough physical storage.");
		return false;
	}
	return true;
}

//
// ReadCPUSpeed							- Chapter 5, page 140
//

DWORD Windows32Calls::readCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
			L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ,
			&hKey);

	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueExW(hKey, L"~MHz", NULL, &type, (LPBYTE) &dwMHz, &BufSize);
	}

	return dwMHz;
}

//
// CheckMemory							- Chapter 5, page 139
//

bool Windows32Calls::checkMemory(const DWORDLONG physicalRAMNeeded,
		const DWORDLONG virtualRAMNeeded) {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	int DIVkb = 1024;
	int DIV = 1024 * 1024;
	stringstream ss;

	double ramNeededMB = physicalRAMNeeded / 1024 / 1024;
	double ramAvailMB = status.ullTotalPhys / 1024 / 1024;

	double ramNeededGB = physicalRAMNeeded / 1024 / 1024 / 1024;
	double ramAvailGB = status.ullTotalPhys / 1024 / 1024 / 1024;
	double ramAvailTB = status.ullTotalPhys / 1024 / 1024 / 1024 / 1024;


	double virtualRamNeededMB = virtualRAMNeeded / 1024 / 1024;
	double virtualRamAvailMB = status.ullAvailVirtual / 1024 / 1024;

	double virtualRamNeededGB = virtualRAMNeeded / 1024 / 1024 / 1024;
	double virtualRamAvailGB = status.ullAvailVirtual / 1024 / 1024 / 1024;


	if (status.ullTotalPhys < physicalRAMNeeded) {
		// you don't have enough physical memory. Tell the player to go get a real
		// computer and give this one to his mother.
		logger::warning("CheckMemory Failure: Not enough physical memory.");
		return false;
	}

	// Check for enough free memory.
	if (status.ullAvailVirtual < virtualRAMNeeded) {
		// you don't have enough virtual memory available.
		// Tell the player to shut down the copy of Visual Studio running in the
		// background, or whatever seems to be sucking the memory dry.
		logger::warning("CheckMemory Failure: Not enough virtual memory.");
		return false;
	}

	char *buff = GCC_NEW char[(unsigned int) virtualRAMNeeded];
	if (buff)
		delete[] buff;
	else {
		// even though there is enough memory, it isn't available in one
		// block, which can be critical for games that manage their own memory
		logger::warning(
				"CheckMemory Failure: Not enough contiguous available memory.");
		return false;
	}
	return true;
}

}
#endif /* __WIN32 */

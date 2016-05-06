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

#include "Windows32Calls.hpp"
#include <windows.h>
#include <iostream>

#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#include<direct.h>
// _getdrive()

//#include <atlbase.h>
//#include <atlconv.h>

#define SW_SHOWNORMAL 1

using namespace std;

namespace watermill {

    Windows32Calls::Windows32Calls() {
    }

    Windows32Calls::Windows32Calls(const Windows32Calls& orig) {
    }

    Windows32Calls::~Windows32Calls() {
    }

    bool Windows32Calls::isAGameProcess(DWORD processID, TCHAR * gameTitle) {
        bool result = false;

        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        TCHAR szGameProcessName[MAX_PATH];
        //  USES_CONVERSION;
        //_tcscpy(szGameProcessName, gameTitle);

        //USES_CONVERSION;
        //_tcscpy(szGameProcessName, A2T(gameTitle));


        // Get a handle to the process.

        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                PROCESS_VM_READ,
                FALSE, processID);

        // Get the process name.

        if (NULL != hProcess) {
            HMODULE hMod;
            DWORD cbNeeded;

            if (EnumProcessModules(hProcess, &hMod, sizeof (hMod),
                    &cbNeeded)) {
                GetModuleBaseName(hProcess, hMod, szProcessName,
                        sizeof (szProcessName) / sizeof (TCHAR));
            }
        }

        // Print the process name and identifier.

        //int cmpRes = _tcscmp(szProcessName, szGameProcessName);
        int cmpRes = _tcscmp(szProcessName, gameTitle);

        //cout << TEXT("CHECK: ") << cmpRes << TEXT("; szProcess: ") << szProcessName << TEXT("; szGame: ") << szGameProcessName << TEXT("; Title: ") << gameTitle << endl;

        if (cmpRes == 0) {

            cout << cmpRes << TEXT("; szProcess: ") << szProcessName << TEXT("; szGame: ") << szGameProcessName << TEXT("; Title: ") << gameTitle << endl;

            _tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);

            result = true;
        }
        // Release the handle to the process.

        CloseHandle(hProcess);

        return result;
    }

    bool Windows32Calls::isOnlyInstance(TCHAR * gameTitle) {
        /* EnumProcesses lists only 32 bit processes. If you run windmill.exe using Cygwin 64 bit first,
         * then Cygwin process will not be discovered by EnumProcesses. MinGW windmill.exe process
         * will be able to launch along with Cygwin process.
         * Compare to Windows64Calls::IsOnlyInstance(TCHAR*)
         */

        std::cout << "Is the only instance in Windows 32: " << gameTitle << "?" << std::endl;

        // Get the list of process identifiers.
        DWORD aProcesses[1024], cbNeeded, cProcesses;
        unsigned int i;

        if (!EnumProcesses(aProcesses, sizeof (aProcesses), &cbNeeded)) {
            return 1;
        }


        // Calculate how many process identifiers were returned.

        cProcesses = cbNeeded / sizeof (DWORD);

        // Print the name and process identifier for each process.

        /*
        for (i = 0; i < cProcesses; i++) {
            if (aProcesses[i] != 0) {
                PrintProcessNameAndID(aProcesses[i]);
            }
        }*/

        int howMany = 0;
        cout << "--------------------------" << endl;
        for (i = 0; i < cProcesses; i++) {
            if (aProcesses[i] != 0) {
                bool result = isAGameProcess(aProcesses[i], gameTitle);
                if (result) {
                    howMany++;
                }
            }
        }

        cout << "howMany: " << howMany << endl;

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

        unsigned __int64 const neededClusters =
                diskSpaceNeeded / (diskfree.sectors_per_cluster * diskfree.bytes_per_sector);

        cout << "diskFree: " << diskfree.avail_clusters << endl;
        cout << "diskNeeded: " << neededClusters << endl;


        if (diskfree.avail_clusters < neededClusters) {
            // if you get here you don’t have enough disk space!
            cout << "CheckStorage Failure: Not enough physical storage." << endl;
            return false;
        }
        return true;
    }

    //
    // ReadCPUSpeed							- Chapter 5, page 140
    //

    DWORD readCPUSpeed() {
        DWORD BufSize = sizeof (DWORD);
        DWORD dwMHz = 0;
        DWORD type = REG_DWORD;
        HKEY hKey;

        /*
        // open the key where the proc speed is hidden:
        long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                0, KEY_READ, &hKey);

        if (lError == ERROR_SUCCESS) {
            // query the key:
            RegQueryValueEx(hKey, L"~MHz", NULL, &type, (LPBYTE) & dwMHz, &BufSize);
        }
         */
        return dwMHz;
    }

}
#endif /* __WIN32 */

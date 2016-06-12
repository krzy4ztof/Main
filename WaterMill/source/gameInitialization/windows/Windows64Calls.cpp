/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Windows64Calls.cpp
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 20:05
 */

#ifdef __WIN64
//#ifdef __LINUX__

#include "Windows64Calls.hpp"
#include <windows.h>
#include <iostream>

#include <stdio.h>
#include <psapi.h>

#include "../Macros.hpp"

#define SW_SHOWNORMAL 1

using namespace std;
namespace watermill {

    Windows64Calls::Windows64Calls() {
    }

    Windows64Calls::Windows64Calls(const Windows64Calls& orig) {
    }

    Windows64Calls::~Windows64Calls() {
    }

    //
    // IsOnlyInstance							- Chapter 5, page 137
    //

    bool Windows64Calls::isAGameProcess(DWORD processID, const std::string& gameTitle) {
        //  bool Windows64Calls::isAGameProcess(DWORD processID, TCHAR * gameTitle) {
        bool result = false;

        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        TCHAR szGameProcessName[MAX_PATH];

        TCHAR *gameTitleTchar = new TCHAR[gameTitle.size() + 1];
        gameTitleTchar[gameTitle.size()] = 0;
        //As much as we'd love to, we can't use memcpy() because
        //sizeof(TCHAR)==sizeof(char) may not be true:
        std::copy(gameTitle.begin(), gameTitle.end(), gameTitleTchar);

        cout << "gameTitleTchar: " << gameTitleTchar << endl;

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
        //int cmpRes = strcmp(szProcessName, gameTitle);
        int cmpRes = strcmp(szProcessName, gameTitleTchar);



        if (cmpRes == 0) {

            cout << cmpRes << TEXT("; szProcess: ") << szProcessName << TEXT("; szGame: ") << szGameProcessName << TEXT("; Title: ") << gameTitle << endl;

            printf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);

            result = true;
        }
        // Release the handle to the process.

        CloseHandle(hProcess);

        return result;
    }

    bool Windows64Calls::isOnlyInstance(const std::string& gameTitle) {

        //    bool Windows64Calls::isOnlyInstance(TCHAR * gameTitle) {
        /* EnumProcesses lists 64 and 32 bit processes. If you run windmill.exe using MinGW 32 bit first,
         * then MinGW process will be discovered by EnumProcesses. Cygwin process will not launch
         * because MinGW process is already running.
         * Compare to Windows32Calls::IsOnlyInstance(TCHAR*)
         */


        //bool GameCodeApp::IsOnlyInstance(LPCTSTR gameTitle) {
        cout << "Is the only instance in Windows 64: " << gameTitle << "?" << endl;

         string gameTitleExe (gameTitle);
        gameTitleExe.append(".exe");

        cout << "Is the only instance in Windows 64: " << gameTitleExe << "?" << endl;

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
                bool result = isAGameProcess(aProcesses[i], gameTitleExe);
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


    //
    // ReadCPUSpeed							- Chapter 5, page 140
    //

    DWORD Windows64Calls::readCPUSpeed() {
        DWORD BufSize = sizeof (DWORD);
        DWORD dwMHz = 0;
        DWORD type = REG_DWORD;
        HKEY hKey;


        // open the key where the proc speed is hidden:
        long lError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                0, KEY_READ, &hKey);

        if (lError == ERROR_SUCCESS) {
            // query the key:
            RegQueryValueExW(hKey, L"~MHz", NULL, &type, (LPBYTE) & dwMHz, &BufSize);
        }

        return dwMHz;
    }


    //
    // CheckMemory							- Chapter 5, page 139
    //

    bool Windows64Calls::checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded) {
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

                double virtualRamNeededMB = virtualRAMNeeded / 1024 / 1024;
        double virtualRamAvailMB = status.ullAvailVirtual / 1024 / 1024;


        double virtualRamNeededGB = virtualRAMNeeded / 1024 / 1024 / 1024;
        double virtualRamAvailGB = status.ullAvailVirtual / 1024 / 1024 / 1024;

        cout << "virtual RAM needed: " << virtualRAMNeeded << " [byte], " << virtualRamNeededMB << " [MB] " << virtualRamNeededGB << " [GB]"  << endl;
        cout << "virtual RAM available: " << status.ullAvailVirtual << " [byte], " << virtualRamAvailMB << " [MB] " << virtualRamAvailGB << " [GB]" << endl;


        if (status.ullTotalPhys < physicalRAMNeeded) {
            // you don’t have enough physical memory. Tell the player to go get a real
            // computer and give this one to his mother.
            cout << "CheckMemory Failure: Not enough physical memory." << endl;
            return false;
        }



        // Check for enough free memory.
        if (status.ullAvailVirtual < virtualRAMNeeded) {
            // you don’t have enough virtual memory available.
            // Tell the player to shut down the copy of Visual Studio running in the
            // background, or whatever seems to be sucking the memory dry.
            cout << "CheckMemory Failure: Not enough virtual memory." << endl;
            return false;
        }

        char *buff = GCC_NEW char[(unsigned int) virtualRAMNeeded];
        if (buff)
            delete[] buff;
        else {
            // even though there is enough memory, it isn't available in one
            // block, which can be critical for games that manage their own memory
            cout << "CheckMemory Failure: Not enough contiguous available memory." << endl;
            return false;
        }
        return true;
    }

}

#endif /* __WIN64 */

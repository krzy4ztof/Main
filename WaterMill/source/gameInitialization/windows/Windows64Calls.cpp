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

    bool Windows64Calls::isAGameProcess(DWORD processID, TCHAR * gameTitle) {
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
        int cmpRes = strcmp(szProcessName, gameTitle);


        if (cmpRes == 0) {

            cout << cmpRes << TEXT("; szProcess: ") << szProcessName << TEXT("; szGame: ") << szGameProcessName << TEXT("; Title: ") << gameTitle << endl;

            printf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);

            result = true;
        }
        // Release the handle to the process.

        CloseHandle(hProcess);

        return result;
    }

    bool Windows64Calls::isOnlyInstance(TCHAR * gameTitle) {
        /* EnumProcesses lists 64 and 32 bit processes. If you run windmill.exe using MinGW 32 bit first,
         * then MinGW process will be discovered by EnumProcesses. Cygwin process will not launch
         * because MinGW process is already running.
         * Compare to Windows32Calls::IsOnlyInstance(TCHAR*)
         */


        //bool GameCodeApp::IsOnlyInstance(LPCTSTR gameTitle) {
        cout << "Is the only instance in Windows 64: " << gameTitle << "?" << endl;

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
}

#endif /* __WIN64 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Cygwin64Calls.cpp
 * Author: Krzysztof
 *
 * Created on 6 maja 2016, 22:02
 */


#ifdef __CYGWIN__

#include "Cygwin64Calls.hpp"

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


#include "../Macros.hpp"

#define SW_SHOWNORMAL 1

using namespace std;

namespace watermill {

    Cygwin64Calls::Cygwin64Calls() {
    }

    Cygwin64Calls::Cygwin64Calls(const Cygwin64Calls& orig) {
    }

    Cygwin64Calls::~Cygwin64Calls() {
    }

    //
    // IsOnlyInstance							- Chapter 5, page 137
    //

    bool Cygwin64Calls::isAGameProcess(DWORD processID, const string& gameTitle) {
        bool result = false;

        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

        TCHAR *gameTitleTchar = new TCHAR[gameTitle.size() + 1];
        gameTitleTchar[gameTitle.size()] = 0;
        //As much as we'd love to, we can't use memcpy() because
        //sizeof(TCHAR)==sizeof(char) may not be true:
        copy(gameTitle.begin(), gameTitle.end(), gameTitleTchar);

        cout << "gameTitleTchar: " << gameTitleTchar << endl;

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

        int cmpRes = strcmp(szProcessName, gameTitleTchar);
        if (cmpRes == 0) {
            cout << cmpRes << TEXT("; szProcess: ") << szProcessName << TEXT("; Title: ") << gameTitle << endl;
            printf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
            result = true;
        }
        // Release the handle to the process.
        CloseHandle(hProcess);

        return result;
    }

    bool Cygwin64Calls::isOnlyInstance(const string& gameTitle) {
        /* EnumProcesses lists 64 and 32 bit processes. If you run windmill.exe using MinGW 32 bit first,
         * then MinGW process will be discovered by EnumProcesses. Cygwin process will not launch
         * because MinGW process is already running.
         * Compare to Windows32Calls::IsOnlyInstance(const string&)
         */

        cout << "Is the only instance in Cygwin 64: " << gameTitle << "?" << endl;

        // Get the list of process identifiers.
        DWORD aProcesses[1024], cbNeeded, cProcesses;
        unsigned int i;

        if (!EnumProcesses(aProcesses, sizeof (aProcesses), &cbNeeded)) {
            return 1;
        }


        // Calculate how many process identifiers were returned.
        cProcesses = cbNeeded / sizeof (DWORD);

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

    bool Cygwin64Calls::checkHardDisk(const int diskSpaceNeeded) {
        // Check for enough free disk space on the current disk.

        boost::filesystem::space_info si = boost::filesystem::space(".");

        double diskAvailableMB = si.available / 1024 / 1024;
        double diskAvailableGB = diskAvailableMB / 1024;
        double diskNeededMB = diskSpaceNeeded / 1024 / 1024;

        cout << "space: " << si.available << " [free], " << diskAvailableMB << " [MB], " << setprecision(4) << diskAvailableGB << " [GB]" << endl;
        cout << "diskNeeded: " << diskSpaceNeeded << " [needed], " << diskNeededMB << " [MB]" << endl;

        return true;
    }

    //
    // ReadCPUSpeed							- Chapter 5, page 140
    //

    DWORD Cygwin64Calls::readCPUSpeed() {

        double speed = readCPUSpeedCygwin();

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

        cout << "dwMHz: " << dwMHz << endl;

        dwMHz = lround(speed);

        return dwMHz;
        //return dwMHz;
    }


    // You could also take an existing vector as a parameter.

    void Cygwin64Calls::split(vector<string>& internal, const string& str, char delimiter) {

        stringstream ss(str); // Turn the string into a stream.
        string tok;

        while (getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }
    }

    bool Cygwin64Calls::toDoubleStod(double& speed, const string& str) {
        try {
            speed = stod(str);
            cout << "3 speed: '" << speed << "'" << endl;
            return true;
        } catch (exception& e) {
            cout << "exception: " << e.what() << endl;
            return false;
        }
    }

    bool Cygwin64Calls::toDoubleStream(double& speed, const string& str) {
        stringstream ss;
        ss << str;
        ss >> speed;

        if (!ss.fail()) {
            cout << "4 speed2: '" << speed << "'" << endl;
            return true;
        } else {
            cout << "fail" << endl;
            return false;
        }
    }

    vector<double>* Cygwin64Calls::findSpeedPtr(vector <string>& internal) {
        vector<double>* doubleVector = new vector<double>();

        cout << "findSpeedPtr" << endl;


        for (int i1 = 0; i1 < 0; i1++) {
            cout << "i1: " << i1 << endl;
        }

        for (int i2 = 0; i2 <= 0; i2++) {
            cout << "i2: " << i2 << endl;
        }

        //cout << "internal size " << internal.size() << endl;

        for (int i = 0; i < internal.size(); i++) {
            cout << "1 '" << internal[i] << "'" << endl;
            boost::algorithm::trim(internal[i]);
            cout << "2 '" << internal[i] << "'" << endl;

            double speed1;
            if (toDoubleStod(speed1, internal[i])) {
                cout << "toDouble1 speed: '" << speed1 << "'" << endl;
                doubleVector->push_back(speed1);
            };
        }
        cout << "findSpeedPtr End" << endl;

        return doubleVector;
    }

    vector<double>& Cygwin64Calls::findSpeedRefError(vector <string>& internal) {
        // DO NOT DO IT
        // doubleVector is initialized on heap and returned as reference to outerMethod
        // The outerMethod has no way of deleting object on heap

        vector<double>* doubleVector = new vector<double>();

        for (int i = 0; i < internal.size(); i++) {
            cout << "1 '" << internal[i] << "'" << endl;
            boost::algorithm::trim(internal[i]);
            cout << "2 '" << internal[i] << "'" << endl;

            double speed2;
            if (toDoubleStream(speed2, internal[i])) {
                cout << "toDouble2 speed: '" << speed2 << "'" << endl;
                doubleVector->push_back(speed2);
            };
        }

        return *doubleVector;
    }

    vector<double> Cygwin64Calls::findSpeedMove(vector <string>& internal) {
        // Move constructor is used

        vector<double> doubleVector;

        for (int i = 0; i < internal.size(); i++) {
            cout << "1 '" << internal[i] << "'" << endl;
            boost::algorithm::trim(internal[i]);
            cout << "2 '" << internal[i] << "'" << endl;

            double speed2;
            if (toDoubleStream(speed2, internal[i])) {
                cout << "toDouble2 speed: '" << speed2 << "'" << endl;
                doubleVector.push_back(speed2);
            };
        }

        return doubleVector;
    }

    double Cygwin64Calls::readCPUSpeedCygwin() {
        string line;
        ifstream myfile("/proc/cpuinfo");

        vector <string> internal;
        smatch matches;
        regex pattern("cpu mhz");

        if (myfile.is_open()) {
            while (getline(myfile, line)) {

                boost::algorithm::to_lower(line);

                if (regex_search(line, matches, pattern)) {
                    cout << "line: " << line << endl;
                    for (int i = 0; i < matches.size(); ++i)
                        cout << "\tmatches[" << i << "]: "
                            << matches[i] << endl;

                    split(internal, line, ':');

                } else {
                    //cout << "no match" << endl;
                }

                cout << line << '\n';
            }
            cout << "--------------" << endl;


            myfile.close();
        } else {
            cout << "Unable to open file";
        }


        cout << "internal size: " << internal.size() << endl;
        // DO NOT DO IT
        //        vector<double>& doubleVectorRef = findSpeedRefError(internal);

        vector<double>* doubleVectorPtr = findSpeedPtr(internal);

        for (double speed3 : *doubleVectorPtr) {
            cout << "speed vector ptr: " << speed3 << endl;
        }

        vector<double> doubleVectorMove = findSpeedMove(internal);
        for (double speed3 : doubleVectorMove) {
            cout << "speed vector move: " << speed3 << endl;
        }

        cout << "* 3 " << endl;

        // *doubleMinPtr - operator*
        vector<double>::iterator doubleMinPtr = std::min_element(doubleVectorPtr->begin(), doubleVectorPtr->end());
        cout << "* 41 " << endl;

        double minDouble = 0;

        if (doubleMinPtr != doubleVectorPtr->end()) {
            cout << "!!!" << endl;
            cout << "doubleMinPtr1: " << *doubleMinPtr << endl;
            minDouble = *doubleMinPtr;
        }

        cout << "minDouble: " << minDouble << endl;

        cout << "* 5 " << endl;

        vector<double>::iterator doubleMinMove = std::min_element(doubleVectorMove.begin(), doubleVectorMove.end());

        if (doubleMinMove != doubleVectorMove.end()) {
            cout << "doubleMinMove: " << *doubleMinMove << "; size: " << doubleMinMove.base() << endl;
        }

        if (doubleVectorPtr) {
            cout << "delete doubleVectorPtr" << endl;
            delete doubleVectorPtr;
            doubleVectorPtr = nullptr;
        };

        //    cout << "del doubleMinPtr: " << *doubleMinPtr << endl;
        cout << "del minDouble: " << minDouble << endl;
        //   cout << "del doubleMinMove: " << *doubleMinMove << endl;

        return minDouble;
    }



    //
    // CheckMemory							- Chapter 5, page 139
    //

    bool Cygwin64Calls::checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded) {
        MEMORYSTATUSEX status;
        GlobalMemoryStatusEx(&status);

        double ramNeededMB = physicalRAMNeeded / 1024 / 1024;
        double ramAvailMB = status.ullTotalPhys / 1024 / 1024;

        cout << "physical RAM needed: " << physicalRAMNeeded << " [byte], " << ramNeededMB << " [MB]" << endl;
        cout << "physical RAM available: " << status.ullTotalPhys << " [byte], " << ramAvailMB << " [MB]" << endl;

        if (status.ullTotalPhys < physicalRAMNeeded) {
            // you don’t have enough physical memory. Tell the player to go get a real
            // computer and give this one to his mother.
            cout << "CheckMemory Failure: Not enough physical memory." << endl;
            return false;
        }


        double virtualRamNeededMB = virtualRAMNeeded / 1024 / 1024;
        double virtualRamAvailMB = status.ullAvailVirtual / 1024 / 1024;
        cout << "virtual RAM needed: " << virtualRAMNeeded << " [byte], " << virtualRamNeededMB << " [MB]" << endl;
        cout << "virtual RAM available: " << status.ullAvailVirtual << " [byte], " << virtualRamAvailMB << " [MB]" << endl;

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

#endif /* __CYGWIN__ */

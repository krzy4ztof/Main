/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Cygwin64Calls.hpp
 * Author: Krzysztof
 *
 * Created on 6 maja 2016, 22:02
 */

#ifndef CYGWIN64CALLS_HPP
#define CYGWIN64CALLS_HPP


#ifdef __CYGWIN__
//#ifdef __LINUX__
//#define WINVER 0x0500

#include <windows.h>
#include "Cygwin64Calls.hpp"
#include <string>
#include <vector>

namespace watermill {

    class Cygwin64Calls {
    public:
        Cygwin64Calls();
        Cygwin64Calls(const Cygwin64Calls& orig);
        virtual ~Cygwin64Calls();
        //bool isOnlyInstance(TCHAR *);
        bool isOnlyInstance(const std::string&);

        bool checkHardDisk(const int);
        DWORD readCPUSpeed();
        double readCPUSpeedCygwin();
        bool checkMemoryCygwin();

        bool checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
    private:
        bool toDoubleStod(double& speed, const std::string& str);
        bool toDoubleStream(double& speed, const std::string& str);
    };
}
#endif /* __CYGWIN__ */

#endif /* CYGWIN64CALLS_HPP */


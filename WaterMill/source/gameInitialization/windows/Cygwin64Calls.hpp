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
        bool checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
    private:
        //bool isAGameProcess(DWORD processID, TCHAR * gameTitle);
        bool isAGameProcess(DWORD processID, const std::string& gameTitle);
        void split(std::vector<std::string>& internal, const std::string& str, char delimiter);
        bool toDoubleStod(double& speed, const std::string& str);
        bool toDoubleStream(double& speed, const std::string& str);
        std::vector<double>* findSpeedPtr(std::vector <std::string>& internal);
        std::vector<double>& findSpeedRefError(std::vector <std::string>& internal);
        std::vector<double> findSpeedMove(std::vector <std::string>& internal);
    };
}
#endif /* __CYGWIN__ */

#endif /* CYGWIN64CALLS_HPP */


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

#ifdef __LINUX__
//#ifdef __WIN32__

#include "LinuxCalls.h"
#include <iostream>
using namespace std;
// std::cout
// std::endl

namespace watermill {

    LinuxCalls::LinuxCalls() {
    }

    LinuxCalls::LinuxCalls(const LinuxCalls& orig) {
    }

    LinuxCalls::~LinuxCalls() {
    }

    //
    // IsOnlyInstance							- Chapter 5, page 137
    //

    bool LinuxCalls::IsOnlyInstance(char * gameTitle) {

        //bool GameCodeApp::IsOnlyInstance(LPCTSTR gameTitle) {
        cout << "Is the only Linux: " << gameTitle << "?" << endl;

        return true;
    }
}
#endif /* __LINUX__ */

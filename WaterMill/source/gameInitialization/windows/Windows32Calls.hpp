/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   WindowsCalls.hpp
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:22
 */

#ifndef WINDOWS32CALLS_HPP
#define WINDOWS32CALLS_HPP

#ifdef __WIN32
//#ifdef __LINUX__
#include <windows.h>
#include <tchar.h>

namespace watermill {

    class Windows32Calls {
    public:
        Windows32Calls();
        Windows32Calls(const Windows32Calls& orig);
        virtual ~Windows32Calls();
        bool isOnlyInstance(TCHAR *);
        bool checkHardDisk(const int);
        DWORD readCPUSpeed();
    private:
        bool isAGameProcess(DWORD processID, TCHAR * gameTitle);
    };
}
#endif /* __WIN32 */

#endif /* WINDOWSCALLS_HPP */


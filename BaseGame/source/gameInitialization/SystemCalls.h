/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SystemCalls.h
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:47
 */

#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

#ifdef __WIN32
// __WIN32 Both 32 bit and 64 bit
// MinGW MinGW64
#ifdef __WIN64
// __WIN64 Only 64 bit
// MinGW64
#include "windows/Windows64Calls.h"
//using SystemCalls = WindowsCalls;
//typedef base_game::Windows64Calls SystemCalls;
#else
// MinGW
#include "windows/Windows32Calls.h"
//using SystemCalls = WindowsCalls;
//typedef base_game::Windows32Calls SystemCalls;
#endif /* __WIN64 */
#else

#ifdef __CYGWIN__
#include "windows/Cygwin64Calls.h"
//using SystemCalls = WindowsCalls;
//typedef base_game::Cygwin64Calls SystemCalls;
#endif /* __CYGWIN__ */

#ifdef __linux__
//#ifdef __WIN32__
#include "linux/LinuxCalls.h"
//using SystemCalls = LinuxCalls;
//typedef base_game::LinuxCalls SystemCalls;
#endif /* __linux__ */

#endif /* __WIN32*/

namespace base_game {
#ifdef __WIN32
// __WIN32 Both 32 bit and 64 bit
// MinGW MinGW64
#ifdef __WIN64
// __WIN64 Only 64 bit
// MinGW64
typedef Windows64Calls SystemCalls;
#else
// MinGW
typedef Windows32Calls SystemCalls;
#endif /* __WIN64 */
#else

#ifdef __CYGWIN__
typedef Cygwin64Calls SystemCalls;
#endif /* __CYGWIN__ */

#ifdef __linux__
typedef LinuxCalls SystemCalls;
#endif /* __linux__ */

#endif /* __WIN32*/

}

#endif /* SYSTEMCALLS_HPP */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SystemCalls.hpp
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:47
 */

#ifndef SYSTEMCALLS_HPP
#define SYSTEMCALLS_HPP

using namespace watermill;

#ifdef __WIN32
// __WIN32 Both 32 bit and 64 bit
// MinGW MinGW64
#ifdef __WIN64
// __WIN64 Only 64 bit
// MinGW64
#include "windows/Windows64Calls.hpp"
//using SystemCalls = WindowsCalls;
typedef Windows64Calls SystemCalls;
#else
// MinGW
#include "windows/Windows32Calls.hpp"
//using SystemCalls = WindowsCalls;
typedef Windows32Calls SystemCalls;
#endif /* __WIN64 */
#else

#ifdef __CYGWIN__
#include "windows/Cygwin64Calls.hpp"
//using SystemCalls = WindowsCalls;
typedef Cygwin64Calls SystemCalls;

#endif /* __CYGWIN__ */

#ifdef __LINUX__
//#ifdef __WIN32__
#include "linux/LinuxCalls.hpp"
//using SystemCalls = LinuxCalls;
typedef LinuxCalls SystemCalls;
#endif /* __LINUX__ */

#endif /* __WIN32*/

#endif /* SYSTEMCALLS_HPP */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   WindowsCalls.h
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:22
 */

#ifndef WINDOWS32CALLS_H
#define WINDOWS32CALLS_H

#ifdef __WIN32
//#ifdef __LINUX__
//#define WINVER 0x0500

#include <windows.h>
#include <tchar.h>
#include <string>

// DWORDLONG 64-bit unsigned integer 0-2^64 -1
// DWORDLONG = unsigned long long

// DWORD 32-bit unsigned integer 0 - 2^32 -1
// unsigned long

namespace base_game {

	class Windows32Calls {
		public:
			Windows32Calls();
			Windows32Calls(const Windows32Calls& orig);
			virtual ~Windows32Calls();
			bool isOnlyInstance(const std::string&);
			bool checkHardDisk(const int);
			DWORD readCPUSpeed();
			bool checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
		private:
			//			bool isAGameProcess(DWORD processID, const std::string& gameTitle);
	};
}
#endif /* __WIN32 */

#endif /* WINDOWSCALLS_H */


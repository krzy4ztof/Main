/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Windows64Calls.hpp
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 20:05
 */

#ifndef WINDOWS64CALLS_HPP
#define WINDOWS64CALLS_HPP

#ifdef __WIN64
//#ifdef __LINUX__
//#define WINVER 0x0500

#include <windows.h>
#include "Windows32Calls.hpp"
#include <string>

namespace watermill {

	class Windows64Calls : public Windows32Calls {
		public:
			Windows64Calls();
			Windows64Calls(const Windows64Calls& orig);
			virtual ~Windows64Calls();
			//bool isOnlyInstance(TCHAR *);
			bool isOnlyInstance(const std::string&);
			DWORD readCPUSpeed();
			bool checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
		private:
			//bool isAGameProcess(DWORD processID, TCHAR * gameTitle);
			//bool isAGameProcess(DWORD processID, const std::string& gameTitle);
	};
}
#endif /* __WIN64 */

#endif /* WINDOWS64CALLS_HPP */

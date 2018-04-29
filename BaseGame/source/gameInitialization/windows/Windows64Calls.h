/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Windows64Calls.h
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 20:05
 */

#ifndef WINDOWS64CALLS_H
#define WINDOWS64CALLS_H

#ifdef __WIN64
//#ifdef __LINUX__
//#define WINVER 0x0500

#include <windows.h>
#include "Windows32Calls.h"
#include <string>

namespace base_game {

	class Windows64Calls : public Windows32Calls {
		public:
			Windows64Calls();
			Windows64Calls(const Windows64Calls& orig);
			virtual ~Windows64Calls();
			//bool isOnlyInstance(TCHAR *);
			bool isOnlyInstance(const std::string&);
			DWORD readCPUSpeed();
			bool checkMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);

			std::string getUserProfilePath();

		private:
	};

	namespace windows64calls {
		std::string tcharToString(TCHAR *);
	}
}
#endif /* __WIN64 */

#endif /* WINDOWS64CALLS_H */

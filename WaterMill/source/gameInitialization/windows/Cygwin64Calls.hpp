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
#include "Cygwin64Calls.hpp"
#include <string>
#include <vector>

namespace watermill {

	class Cygwin64Calls {
		public:
			Cygwin64Calls();
			Cygwin64Calls(const Cygwin64Calls& orig);
			virtual ~Cygwin64Calls();

			bool isOnlyInstance(const std::string&);
			bool checkHardDisk(const int);
			unsigned long readCPUSpeed();
			bool checkMemory(const unsigned long long physicalRAMNeeded, const unsigned long long virtualRAMNeeded);

			std::string getSaveGameFolderPath();

		private:
	};
}
#endif /* __CYGWIN__ */

#endif /* CYGWIN64CALLS_HPP */


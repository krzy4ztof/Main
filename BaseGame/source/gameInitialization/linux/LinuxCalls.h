/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LinuxCalls.h
 * Author: Krzysztof
 *
 * Created on 2 maja 2016, 19:22
 */

#ifndef LINUXCALLS_H
#define LINUXCALLS_H

#ifdef __linux__
#include <string>

namespace base_game {

	class LinuxCalls {
	public:
		LinuxCalls();
		LinuxCalls(const LinuxCalls& orig);
		virtual ~LinuxCalls();

		bool isOnlyInstance(const std::string&);
		bool checkHardDisk(const int);
		unsigned long readCPUSpeed();
		bool checkMemory(const unsigned long long physicalRAMNeeded, const unsigned long long virtualRAMNeeded);

		std::string getUserProfilePath();
	private:
	};
}
#endif /* __linux__ */

#endif /* LINUXCALLS_H */


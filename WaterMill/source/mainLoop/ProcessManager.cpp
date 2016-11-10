#include "ProcessManager.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::stringstream;

namespace base_game {
	ProcessManager::ProcessManager() {
		logger::info("Create ProcessManager");
	}

	ProcessManager::~ProcessManager() {
		logger::info("Destroy ProcessManager");
	}

	unsigned int ProcessManager::updateProcesses(unsigned long deltaMs) {
		stringstream ss;
		ss << "updateProcesses deltaMs: " << deltaMs;
		logger::info(ss);

		return 0; //TODO: return
	}
}

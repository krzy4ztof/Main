#include "Process.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

namespace base_game {
	Process::Process() {
		logger::info("Create Process");
	}

	Process::~Process() {
		logger::info("Destroy Process");
	}
}

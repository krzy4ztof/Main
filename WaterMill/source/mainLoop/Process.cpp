#include "Process.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

namespace base_game {
	Process::Process() {
		logger::trace("Create Process");
	}

	Process::~Process() {
		logger::trace("Destroy Process");
	}
}

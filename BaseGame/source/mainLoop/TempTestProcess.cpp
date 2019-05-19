#include "TempTestProcess.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

#include <string> // string

using std::string;
using std::stringstream;

namespace base_game {
TempTestProcess::TempTestProcess(string action) {
	logger::trace("Create TempTestProcess");
	this->action = action;
}

TempTestProcess::~TempTestProcess() {
	logger::trace("Destroy TempTestProcess");
}

void TempTestProcess::vOnUpdate(unsigned long deltaMs) {
	stringstream ss;
	ss << "TempTestProcess::vOnUpdate: " << action;
	logger::info(ss);
	succeed();
}
}

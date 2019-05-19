#include "DelayProcess.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

#include <string> // string

using std::string;
using std::stringstream;

namespace base_game {
DelayProcess::DelayProcess(unsigned long timeToDelay) {
	logger::trace("Create DelayProcess");
	m_timeToDelay = timeToDelay;
	m_timeDelayedSoFar = 0;

}

DelayProcess::~DelayProcess() {
	logger::trace("Destroy DelayProcess");
}

void DelayProcess::vOnUpdate(unsigned long deltaMs) {
	stringstream ss;

	m_timeDelayedSoFar += deltaMs;
	ss << "DelayProcess: " << m_timeDelayedSoFar << " / " << m_timeToDelay;
	logger::info(ss);

	if (m_timeDelayedSoFar >= m_timeToDelay) {
		succeed();
	}
}
}

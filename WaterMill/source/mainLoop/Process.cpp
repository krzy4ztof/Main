#include "Process.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <memory> // shared_ptr, weak_ptr

using std::shared_ptr;

namespace base_game {
	Process::Process() {
		logger::trace("Create Process");
		state = UNINITIALIZED;
	}

	Process::~Process() {
		if (m_pChild != nullptr) {
			m_pChild->vOnAbort();
		}
		logger::trace("Destroy Process");
	}

	//---------------------------------------------------------------------------------------------------------------------
	// Removes the child from this process.  This releases ownership of the child to the caller and completely removes it
	// from the process chain.
	//---------------------------------------------------------------------------------------------------------------------
	shared_ptr<Process> Process::removeChild(void) {
		if (m_pChild) {
			shared_ptr<Process> curChild = m_pChild;  // this keeps the child from getting destroyed when we clear it
			m_pChild.reset();
			//curChild->SetParent(NULL);
			return curChild;
		}

		return shared_ptr<Process>();
	}

	void Process::attachChild(shared_ptr<Process> pChild) {
		if (m_pChild)
			m_pChild->attachChild(pChild);
		else
			m_pChild = pChild;
	}

	void Process::succeed(void) {
		//GCC_ASSERT(m_state == RUNNING || m_state == PAUSED);
		state = SUCCEEDED;
	}

	void Process::fail(void) {
		//GCC_ASSERT(m_state == RUNNING || m_state == PAUSED);
		state = FAILED;
	}

	void Process::pause(void) {
		if (state == RUNNING)
			state = PAUSED;
		else {
			logger::warning("Attempting to pause a process that isn't running");
		}
	}

	void Process::unPause(void) {
		if (state == PAUSED)
			state = RUNNING;
		else {
			logger::warning("Attempting to unpause a process that isn't paused");
		}
	}


}



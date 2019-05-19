#ifndef PROCESS_H
#define PROCESS_H

#include "ProcessState.h"
#include <memory> // shared_ptr, weak_ptr

namespace base_game {
// Audio ->  SoundProcess, ExplosionProcess, FadeProcess
// Multicore -> RealTimeProcess
// LUAScriptiong -> ScriptProcess
class Process {

	// ProcessManager, as a friend class, can invoke protected methods of Process
	friend class ProcessManager;

private:
	ProcessState state;
	std::shared_ptr<Process> m_pChild;  // the child process, if any

public:
	Process();
	virtual ~Process();

public:
	// Functions for ending the process.
	void succeed(void);
	void fail(void);

	// pause
	void pause(void);
	void unPause(void);

	// accessors
	ProcessState getState(void) const {
		return state;
	}
	bool isAlive(void) const {
		return (state == RUNNING || state == PAUSED);
	}
	bool isDead(void) const {
		return (state == SUCCEEDED || state == FAILED || state == ABORTED);
	}
	bool isRemoved(void) const {
		return (state == REMOVED);
	}
	bool isPaused(void) const {
		return state == PAUSED;
	}

	// child functions
	void attachChild(std::shared_ptr<Process> pChild);
	std::shared_ptr<Process> removeChild(void); // releases ownership of the child

protected:
	// interface; these functions should be overridden by the subclass as needed
	virtual void vOnInit(void) {
		state = RUNNING; // called during the first update; responsible for setting the initial state (typically RUNNING)
	}
	virtual void vOnUpdate(unsigned long deltaMs) = 0;  // called every frame
	virtual void vOnSuccess(void) {
	}  // called if the process succeeds (see below)
	virtual void vOnFail(void) {
	}  // called if the process fails (see below)
	virtual void vOnAbort(void) {
	}  // called if the process is aborted (see below)

private:
	void setState(ProcessState newState) {
		state = newState;
	}
};
}

#endif // PROCESS_H

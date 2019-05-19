#ifndef PROCESSSTATE_H
#define PROCESSSTATE_H

namespace base_game {
enum ProcessState {
	// Processes that are neither dead nor alive
	UNINITIALIZED = 0,  // created but not running
	REMOVED, // removed from the process list but not destroyed; this can happen when a process that is already running is parented to another process

	// Living processes
	RUNNING,  // initialized and running
	PAUSED,  // initialized but paused

	// Dead processes
	SUCCEEDED,  // completed successfully
	FAILED,  // failed to complete
	ABORTED  // aborted; may not have started
};
}

#endif // PROCESSSTATE_H

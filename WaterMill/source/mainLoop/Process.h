#ifndef PROCESS_H
#define PROCESS_H

#include "ProcessState.h"
#include <memory> // shared_ptr, weak_ptr

namespace base_game {
	class Process {

		private:
			ProcessState state;
			std::shared_ptr<Process> m_pChild;  // the child process, if any


		public:
			Process();
			virtual ~Process();


		public:
			// Functions for ending the process.
			inline void succeed(void);
			inline void fail(void);


		protected:
			// interface; these functions should be overridden by the subclass as needed
			virtual void vOnInit(void) {
				state = RUNNING;    // called during the first update; responsible for setting the initial state (typically RUNNING)
			}
			virtual void vOnUpdate(unsigned long deltaMs) = 0;  // called every frame
			virtual void vOnSuccess(void) { }  // called if the process succeeds (see below)
			virtual void vOnFail(void) { }  // called if the process fails (see below)
			virtual void vOnAbort(void) { }  // called if the process is aborted (see below)

	};
}

#endif // PROCESS_H

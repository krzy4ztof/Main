#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Process.h"
#include <memory> // shared_ptr, weak_ptr
#include <list> // list

namespace base_game {
	class ProcessManager {
		private:
			std::list<std::shared_ptr<Process>> processList;

		public:
			ProcessManager();
			virtual ~ProcessManager();

			// interface
			void updateProcesses(unsigned long deltaMs);  // updates all attached processes
			std::weak_ptr<Process> attachProcess(std::shared_ptr<Process> pProcess);  // attaches a process to the process mgr

		protected:

		private:
	};
}
#endif // PROCESSMANAGER_H

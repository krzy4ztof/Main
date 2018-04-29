#include "ProcessManager.h"
#include "Process.h"
#include "ProcessState.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <list> // list
#include <memory> // shared_ptr, weak_ptr

using std::stringstream;
using std::shared_ptr;
using std::weak_ptr;

using std::list;

namespace base_game {
	ProcessManager::ProcessManager() {
		logger::trace("Create ProcessManager");
	}

	ProcessManager::~ProcessManager() {
		logger::trace("Destroy ProcessManager");
	}

	void ProcessManager::updateProcesses(unsigned long deltaMs) {
		stringstream ss;

		/*
		if (deltaMs < 1000){
		ss << "updateProcesses deltaMs: " << deltaMs;
		logger::info(ss);
		}

		*/

		unsigned short int successCount = 0;
		unsigned short int failCount = 0;

		//ProcessList::iterator it = m_processList.begin();
		list<shared_ptr<Process>>::iterator it = processList.begin();


		while (it != processList.end()) {
			// grab the next process
			//StrongProcessPtr pCurrProcess = (*it);

			//iterator: it - pointer; *it - value
			shared_ptr<Process> pCurrProcess = (*it);

			// save the iterator and increment the old one in case we need to remove this process from the list
			list<shared_ptr<Process>>::iterator thisIt = it;
			++it;

			// process is uninitialized, so initialize it
			if (pCurrProcess->getState() == ProcessState::UNINITIALIZED)
				pCurrProcess->vOnInit();

			// give the process an update tick if it's running
			if (pCurrProcess->getState() == ProcessState::RUNNING)
				pCurrProcess->vOnUpdate(deltaMs);

			// check to see if the process is dead
			if (pCurrProcess->isDead()) {
				// run the appropriate exit function
				switch (pCurrProcess->getState()) {
					case ProcessState::SUCCEEDED : {
							pCurrProcess->vOnSuccess();
							shared_ptr<Process> pChild = pCurrProcess->removeChild();
							if (pChild)
								attachProcess(pChild);
							else
								++successCount;  // only counts if the whole chain completed
							break;
						}

					case ProcessState::FAILED : {
							pCurrProcess->vOnFail();
							++failCount;
							break;
						}

					case ProcessState::ABORTED : {
							pCurrProcess->vOnAbort();
							++failCount;
							break;
						}

					default: {
							break;
						}
						/*
						                case ProcessState::UNINITIALIZED:{
						                break;
						                }

						                case ProcessState::REMOVED:{
						                break;
						                }

						                case ProcessState::RUNING:{
						                break;
						                }

						                case ProcessState::PAUSED:{
						                break;
						                }
						*/
				}

				// remove the process and destroy it
				processList.erase(thisIt);
			}
		}



		//    return ((successCount << 16) | failCount);
		//	return 0; //TODO: return
	}

	weak_ptr<Process> ProcessManager::attachProcess(shared_ptr<Process> pProcess) {
		// push_front - inserts element at the beginning
		processList.push_front(pProcess);
		return weak_ptr<Process>(pProcess);
	}
}

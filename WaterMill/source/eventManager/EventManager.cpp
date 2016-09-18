#include "EventManager.h"

namespace watermill {
	EventManager::EventManager() {
		//ctor
	}

	EventManager::~EventManager() {
		//dtor
	}

	namespace event_manager {
		void safe_delete(EventManager* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}
}

#include "EventManager.h"

namespace base_game {
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

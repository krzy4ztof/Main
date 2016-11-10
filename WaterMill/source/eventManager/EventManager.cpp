#include "EventManager.h"
#include "../debugging/Logger.h"

namespace base_game {
	EventManager::EventManager() {
		logger::info("Create EventManager");
	}

	EventManager::~EventManager() {
		logger::info("Destroy EventManager");
	}
}

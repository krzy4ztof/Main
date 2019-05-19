#include "EventManager.h"
#include "../debugging/Logger.h"

namespace base_game {
EventManager::EventManager() {
	logger::trace("Create EventManager");
}

EventManager::~EventManager() {
	logger::trace("Destroy EventManager");
}
}

#include "ActorComponent.h"
#include <memory> // shared_ptr
#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::shared_ptr;
using std::string;
using std::stringstream;
using std::hash;

namespace base_game {
	ActorComponent::ActorComponent() {
		logger::trace("Create ActorComponent");
	}

	ActorComponent::~ActorComponent() {
		logger::trace("Destroy ActorComponent");
		pOwner.reset();
	}

	void ActorComponent::setOwner(shared_ptr<Actor> actor) {
		this->pOwner = actor;
	}

	size_t ActorComponent::getIdFromName(string name) {
		hash<string> hash_fn;
		size_t hash_value = hash_fn(name);
		return hash_value;
	}

}

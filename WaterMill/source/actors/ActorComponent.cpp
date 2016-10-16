#include "ActorComponent.h"
#include <memory> // shared_ptr

using std::shared_ptr;

namespace base_game {
	ActorComponent::ActorComponent() {
		//unsigned int actorComponentId) {
		//id=actorComponentId;
	}


	ActorComponent::~ActorComponent() {
		pOwner.reset();
	}

	void ActorComponent::setOwner(shared_ptr<Actor> actor) {
		this->pOwner = actor;

	}
}

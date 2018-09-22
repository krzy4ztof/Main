#include "Actor.h"
#include "ActorComponent.h"
#include "TransformComponent.h"

#include <boost/property_tree/ptree.hpp> // ptree
#include "../utilities/PropertyTreeUtils.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <memory> // shared_ptr, weak_ptr, static_pointer_cast
#include <map> // map
#include <utility> // pair, make_pair

using std::shared_ptr;
using std::weak_ptr;
using std::static_pointer_cast;
using std::string;
using boost::property_tree::ptree;
using value_type = boost::property_tree::ptree::value_type; // typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp
using std::stringstream;
using std::make_pair;
using std::pair;
using std::map;

namespace base_game {
	const unsigned int Actor::INVALID_ACTOR_ID = 0;

	Actor::Actor(unsigned int actorId) {
		logger::trace("Create Actor");
		id=actorId;
	}

	Actor::~Actor() {
		logger::trace("Destroy Actor");
	}

	bool Actor::init(ptree actorNode) {
		return true;
	}

	void Actor::addComponent(shared_ptr<ActorComponent> component) {
		size_t componentId = component->vGetId();
		pair<size_t, shared_ptr<ActorComponent>> compPair = make_pair(componentId,component);

		components.insert(compPair);
	}

	void Actor::describeYourself() {
		stringstream ss;
		ss << "Actor Id: " << id;
		logger::trace(ss);

		map<size_t, shared_ptr<ActorComponent>>::iterator componentsIterator;

		for (componentsIterator = components.begin(); componentsIterator!=components.end(); componentsIterator++) {
			componentsIterator->second->describeYourself();
		}
	}

	void Actor::postInit() {
		map<size_t, shared_ptr<ActorComponent>>::iterator componentsIterator;
		for (componentsIterator = components.begin(); componentsIterator!=components.end(); componentsIterator++) {
			componentsIterator->second->vPostInit();
		}
	}

	void Actor::destroy() {
		// components.clear() dereferences actorComponent.pOwner shared_ptr. So when shared_ptr to actor is being reset(),
		// pointer island of isolation will not be created.
		components.clear();
	}

	void Actor::tempTestComponents() {
	logger::info("Actor::tempTestComponents");

		weak_ptr<TransformComponent> transformComp  = getComponent<TransformComponent>(TransformComponent::COMPONENT_NAME);

		if (shared_ptr<TransformComponent> shrTransformComp = transformComp.lock()) {
			shrTransformComp->tempTransformComponentFunction();
		}

	}

}

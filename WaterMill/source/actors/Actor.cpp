#include "Actor.h"
#include "ActorComponent.h"

#include <boost/property_tree/ptree.hpp> // ptree
#include "../utilities/PropertyTreeUtils.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <memory> // shared_ptr
#include <map> // map
#include <utility> // pair, make_pair

using std::shared_ptr;
using std::string;
using boost::property_tree::ptree;
using value_type = boost::property_tree::ptree::value_type; // typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp
using std::stringstream;
using std::make_pair;
using std::pair;
using std::map;

namespace base_game {
	Actor::Actor(unsigned int actorId) {
		id=actorId;
	}

	Actor::~Actor() {
		//dtor
		logger::info("Destroy Actor");
	}

	bool Actor::init(ptree actorNode) {

		return true;
	}

	void Actor::addComponent(shared_ptr<ActorComponent> component) {
		unsigned int componentId = component->vGetId();
		pair<unsigned int, shared_ptr<ActorComponent>> compPair = make_pair(componentId,component);

		components.insert(compPair);
	}

	void Actor::describeYourself() {
		stringstream ss;
		ss << "Actor Id: " << id;
		logger::info(ss);

		map<unsigned int, shared_ptr<ActorComponent>>::iterator componentsIterator;

		for (componentsIterator = components.begin(); componentsIterator!=components.end(); componentsIterator++) {
			//cout << "Option: " << componentsIterator->first << " => " << componentsIterator->second << endl;
			componentsIterator->second->describeYourself();
		}
		/*		    for (shared_ptr<ActorComponent> it : components.begin(), ){

		for (shared_ptr<ActorComponent> component : components){
		component->describeYourself();

		}*/
	}

	void Actor::postInit() {
		map<unsigned int, shared_ptr<ActorComponent>>::iterator componentsIterator;

		for (componentsIterator = components.begin(); componentsIterator!=components.end(); componentsIterator++) {
			//cout << "Option: " << componentsIterator->first << " => " << componentsIterator->second << endl;
			componentsIterator->second->vPostInit();
		}
	}
}

#include "ComponentFactory.h"

#include <string>  // string
#include <map> // map
#include "ActorComponent.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <boost/property_tree/ptree.hpp> // ptree
#include <memory> // shared_ptr

using std::string;
using std::stringstream;
using value_type = boost::property_tree::ptree::value_type; // typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp
using std::shared_ptr;
using std::map;

namespace base_game {
	ComponentFactory::ComponentFactory() {
		logger::trace("Create ComponentFactory");
	}

	ComponentFactory::~ComponentFactory() {
		logger::trace("Destroy ComponentFactory");
	}

	void ComponentFactory::registerComponent(std::string name, ActorComponent* (*factoryFunction)(void)) {
		//		map<string,string>::iterator findIt = creationFunctions.find(name);
		map<string,ActorComponent* (*)(void)>::iterator findIt = creationFunctions.find(name);


		if (findIt == creationFunctions.end()) {
			creationFunctions[name] = factoryFunction; //"zarejestrowano-"+name;
			stringstream ss;
			ss << "zarejestrowano: " << name << "; function: " << creationFunctions[name];
			logger::trace(ss);

		}

	}

	//	ActorComponent ComponentFactory::create(std::string name) {
	shared_ptr<ActorComponent> ComponentFactory::create(const value_type& componentValueType) {

		string name = componentValueType.first.data();
		stringstream ss;
		ss << "loadActorNode component: " << name;
		logger::trace(ss);

		//map<string,string>::iterator findIt = creationFunctions.find(name);
		ActorComponent* actorComponent = nullptr;

		map<string,ActorComponent* (*)(void)>::iterator findIt = creationFunctions.find(name);


		if (findIt != creationFunctions.end()) {
			logger::trace("Komponent jest zarejestrowany");

			ActorComponent* (*factoryFunction)(void) = findIt->second;


			actorComponent = factoryFunction();
			//	stringstream ss;
			//	ss << "znaleziono: " << creationFunctions[name];
			//	logger::info(ss);



		}

		if (actorComponent) {
			stringstream ss;
			ss << "stworzono komponent: "<< name;
			logger::trace(ss);

			if (!actorComponent->vInit(componentValueType.second)) {
				stringstream ss;
				ss << "Component failed to initialize: " << name;
				logger::error(ss);

				return shared_ptr<ActorComponent>();

			}

		} else {
			stringstream ss;
			ss << "Couldn't find ActorComponent named: " << name;
			logger::error(ss);
			return shared_ptr<ActorComponent>();

		}


		return shared_ptr<ActorComponent>(actorComponent);
	}
}

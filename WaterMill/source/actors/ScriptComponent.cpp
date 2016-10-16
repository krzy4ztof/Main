#include "ScriptComponent.h"
#include "ActorComponent.h"

#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using boost::property_tree::ptree;
using std::stringstream;

namespace base_game {

	const string ScriptComponent::COMPONENT_NAME = "scriptComponent";

	ScriptComponent::ScriptComponent() {
		//ctor
	}

	ScriptComponent::~ScriptComponent() {
		logger::info("Destroy ScriptComponent");
	}

	bool ScriptComponent::vInit(const ptree componentNode) {
		return true;
	};

	unsigned int ScriptComponent::vGetId() {
		return 1002;
	}

	void ScriptComponent::describeYourself() {
		stringstream ss;
		ss << "ScriptComponent Id: " << vGetId();
		logger::info(ss);

	}

	void ScriptComponent::vPostInit() {
	}


	namespace script_component {
		ActorComponent* componentFactory() {
			return new ScriptComponent();
		}
	}
}

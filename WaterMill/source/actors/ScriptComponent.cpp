#include "ScriptComponent.h"
#include "ActorComponent.h"

#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <boost/property_tree/ptree.hpp>// ptree, optional

using std::string;
using boost::property_tree::ptree;
using std::stringstream;
using boost::optional;
using std::hash;

namespace base_game {

	const string ScriptComponent::COMPONENT_NAME = "scriptComponent";

	const string ScriptComponent::SCRIPT_OBJECT_NODE_NAME = "scriptObject";
	const string ScriptComponent::ATTR_CONSTRUCTOR = "<xmlattr>.constructor";
	const string ScriptComponent::ATTR_DESTRUCTOR = "<xmlattr>.destructor";

	const string ScriptComponent::SCRIPT_DATA_NODE_NAME = "scriptData";
	const string ScriptComponent::ATTR_ACTOR_TYPE = "<xmlattr>.actorType";


	ScriptComponent::ScriptComponent() {
		logger::info("Create ScriptComponent");
	}

	ScriptComponent::~ScriptComponent() {
		logger::info("Destroy ScriptComponent");
	}


	/*
	<scriptComponent>
	    <scriptObject constructor="addPlayer" destructor="removePlayer" />
	    <scriptData actorType="player"/>
	</scriptComponent>
	*/
	bool ScriptComponent::vInit(const ptree componentNode) {
		optional<const ptree&> optScriptObject = componentNode.get_child_optional(SCRIPT_OBJECT_NODE_NAME);
		if (optScriptObject.is_initialized()) {
			bool result = readScriptObjectNode(optScriptObject.get());
			if (!result) {
				return false;
			}
		}

		optional<const ptree&> optScriptData = componentNode.get_child_optional(SCRIPT_DATA_NODE_NAME);
		if (optScriptData.is_initialized()) {
			bool result = readScriptDataNode(optScriptData.get());
			if (!result) {
				return false;
			}
		}


		return true;
	};

	bool ScriptComponent::readScriptObjectNode(const ptree& scriptObjectNode) {

		optional<string> constrValue = scriptObjectNode.get_optional<string>(ATTR_CONSTRUCTOR);
		if (constrValue.is_initialized()) {
			constructor = constrValue.get();
		}

		optional<string> destrValue = scriptObjectNode.get_optional<string>(ATTR_DESTRUCTOR);
		if (destrValue.is_initialized()) {
			destructor = destrValue.get();
		}

		return true;
	}

	bool ScriptComponent::readScriptDataNode(const ptree& scriptDataNode) {

		optional<string> typeValue = scriptDataNode.get_optional<string>(ATTR_ACTOR_TYPE);

		if (typeValue.is_initialized()) {
			actorType = typeValue.get();
		}

		return true;
	}

	size_t ScriptComponent::vGetId() {
		size_t id = getIdFromName(COMPONENT_NAME);
		return id;
	}

	void ScriptComponent::describeYourself() {
		stringstream ss;
		ss << "ScriptComponent Id: " << vGetId() << "; constructor: " << constructor << "; destructor: " << destructor << "; actorType: " << actorType;
		logger::trace(ss);
	}

	void ScriptComponent::vPostInit() {
	}

	void ScriptComponent::tempScriptComponentFunction() {
		logger::trace("Perform tempScriptComponentFunction");
	}

	namespace script_component {
		ActorComponent* componentFactory() {
			return new ScriptComponent();
		}
	}
}

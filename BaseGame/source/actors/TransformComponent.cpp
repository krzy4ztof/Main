#include "TransformComponent.h"
#include "ActorComponent.h"
#include "ScriptComponent.h"
#include "RenderComponent.h"
#include "Actor.h"

#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <boost/property_tree/ptree.hpp>// ptree, optional
#include <memory> // weak_ptr, shared_ptr

using std::string;
using boost::property_tree::ptree;
using std::stringstream;
using boost::optional;
using std::hash;
using std::weak_ptr;
using std::shared_ptr;

namespace base_game {
const string TransformComponent::COMPONENT_NAME = "transformComponent";

const string TransformComponent::POSITION_NODE_NAME = "position";
const string TransformComponent::ATTR_X = "<xmlattr>.x";
const string TransformComponent::ATTR_Y = "<xmlattr>.y";
const string TransformComponent::ATTR_Z = "<xmlattr>.z";

TransformComponent::TransformComponent() :
		x(0), y(0), z(0) {
	logger::trace("Create TransformComponent");
}

TransformComponent::~TransformComponent() {
	logger::trace("Destroy TransformComponent");
}

/*
 <transformComponent>
 <position x="0" y="5" z="0"/>
 </transformComponent>
 */
bool TransformComponent::vInit(const ptree componentNode) {
	optional<const ptree&> optPositionNode = componentNode.get_child_optional(
			POSITION_NODE_NAME);
	if (optPositionNode.is_initialized()) {
		bool result = readPositionNode(optPositionNode.get());
		if (!result) {
			return false;
		}
	}

	return true;
}
;

bool TransformComponent::readPositionNode(const ptree& positionNode) {
	stringstream ss;
	optional<int> xValue = positionNode.get_optional<int>(ATTR_X);
	if (xValue.is_initialized()) {
		x = xValue.get();
		ss << "Transform x: " << xValue.get();
	} else {
		ss << "Transform x not initialized ";
	}
	logger::trace(ss);

	optional<int> yValue = positionNode.get_optional<int>(ATTR_Y);
	if (yValue.is_initialized()) {
		y = yValue.get();
		ss << "Transform y: " << yValue.get();
	} else {
		ss << "Transform y not initialized ";
	}
	logger::trace(ss);

	optional<int> zValue = positionNode.get_optional<int>(ATTR_Z);
	if (zValue.is_initialized()) {
		z = zValue.get();
		ss << "Transform z: " << zValue.get();
	} else {
		ss << "Transform z not initialized ";
	}
	logger::trace(ss);

	return true;
}

size_t TransformComponent::vGetId() {
	size_t id = getIdFromName(COMPONENT_NAME);
	return id;
}

void TransformComponent::describeYourself() {
	stringstream ss;
	ss << "TransformComponent Id: " << vGetId() << "; x: " << x << "; y: " << y
			<< "; z: " << z;
	logger::trace(ss);
}

void TransformComponent::vPostInit() {
}

void TransformComponent::tempTransformComponentFunction() {
	logger::trace("Perform tempTransformComponentFunction");
	logger::trace(
			"Call tempRenderComponentFunction from tempTransformComponentFunction");
	weak_ptr<RenderComponent> renderComp =
			pOwner->getComponent<RenderComponent>(
					RenderComponent::COMPONENT_NAME);
	if (shared_ptr<RenderComponent> shrRenderComp = renderComp.lock()) {
		shrRenderComp->tempRenderComponentFunction();
	}

	logger::trace(
			"Call tempScriptComponentFunction from tempTransformComponentFunction");
	weak_ptr<ScriptComponent> scriptComp =
			pOwner->getComponent<ScriptComponent>(
					ScriptComponent::COMPONENT_NAME);
	if (shared_ptr<ScriptComponent> shrScriptComp = scriptComp.lock()) {
		shrScriptComp->tempScriptComponentFunction();
	}
}

namespace transform_component {
ActorComponent* componentFactory() {
	return new TransformComponent();
}
}
}

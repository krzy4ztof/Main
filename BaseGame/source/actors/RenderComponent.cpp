#include "RenderComponent.h"
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

	const string RenderComponent::COMPONENT_NAME = "renderComponent";
	const string RenderComponent::COLOR_NODE_NAME = "color";
	const string RenderComponent::ATTR_R = "<xmlattr>.r";
	const string RenderComponent::ATTR_G = "<xmlattr>.g";
	const string RenderComponent::ATTR_B = "<xmlattr>.b";
	const string RenderComponent::ATTR_A = "<xmlattr>.a";


	RenderComponent::RenderComponent() :
		r(0), g(0), b(0), a(0) {
		logger::trace("Create RenderComponent");
	}

	RenderComponent::~RenderComponent() {
		logger::trace("Destroy RenderComponent");
	}

	/*
	<renderComponent>
	    <color r="1.0" g="1.0" b="1.0" a="1.0"/>
	</renderComponent>
	*/
	bool RenderComponent::vInit(const ptree componentNode) {
		optional<const ptree&> optColorNode = componentNode.get_child_optional(COLOR_NODE_NAME);

		if (optColorNode.is_initialized()) {
			bool result = readColorNode(optColorNode.get());
			if (!result) {
				return false;
			}
		}
		return true;
	};


	bool RenderComponent::readColorNode(const ptree& colorNode) {

		optional<float> rValue = colorNode.get_optional<float>(ATTR_R);
		if (rValue.is_initialized()) {
			r = rValue.get();
		}

		optional<float> gValue = colorNode.get_optional<float>(ATTR_G);
		if (gValue.is_initialized()) {
			g = gValue.get();
		}

		optional<float> bValue = colorNode.get_optional<float>(ATTR_B);
		if (bValue.is_initialized()) {
			b = bValue.get();
		}

		optional<float> aValue = colorNode.get_optional<float>(ATTR_A);
		if (aValue.is_initialized()) {
			a = aValue.get();
		}

		return true;
	}

	size_t RenderComponent::vGetId() {
		size_t id = getIdFromName(COMPONENT_NAME);
		return id;
	}

	void RenderComponent::describeYourself() {
		stringstream ss;
		ss << "RenderComponent Id: " << vGetId() << "; r: " << r << "; g: " << g << "; b: " << b  << "; a: " << a;
		logger::trace(ss);
	}

	void RenderComponent::vPostInit() {
	}

	void RenderComponent::tempRenderComponentFunction() {
		logger::trace("Perform tempRenderComponentFunction");
	}


	namespace render_component {
		ActorComponent* componentFactory() {
			return new RenderComponent();
		}
	}
}

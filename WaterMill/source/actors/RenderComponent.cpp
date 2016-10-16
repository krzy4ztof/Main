#include "RenderComponent.h"
#include "ActorComponent.h"


#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using boost::property_tree::ptree;
using std::stringstream;

namespace base_game {

	const string RenderComponent::COMPONENT_NAME = "renderComponent";

	RenderComponent::RenderComponent() {
		//ctor
	}

	RenderComponent::~RenderComponent() {
		logger::info("Destroy RenderComponent");
	}

	bool RenderComponent::vInit(const ptree componentNode) {
		return true;
	};

	unsigned int RenderComponent::vGetId() {
		return 1001;
	}

	void RenderComponent::describeYourself() {
		stringstream ss;
		ss << "RenderComponent Id: " << vGetId();
		logger::info(ss);
	}

	void RenderComponent::vPostInit() {
	}

	namespace render_component {
		ActorComponent* componentFactory() {
			return new RenderComponent();
		}
	}
}

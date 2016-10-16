#include "TransformComponent.h"
#include "ActorComponent.h"


#include <string> // string
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using boost::property_tree::ptree;
using std::stringstream;

namespace base_game {

	const string TransformComponent::COMPONENT_NAME = "transformComponent";

	TransformComponent::TransformComponent() {
		//ctor
	}

	TransformComponent::~TransformComponent() {
		logger::info("Destroy TransformComponent");
	}

	bool TransformComponent::vInit(const ptree componentNode) {
		return true;
	};

	unsigned int TransformComponent::vGetId() {
		return 1003;
	}

	void TransformComponent::describeYourself() {
		stringstream ss;
		ss << "TransformComponent Id: " << vGetId();
		logger::info(ss);
	}

	void TransformComponent::vPostInit() {
	}


	namespace transform_component {
		ActorComponent* componentFactory() {
			return new TransformComponent();
		}
	}
}

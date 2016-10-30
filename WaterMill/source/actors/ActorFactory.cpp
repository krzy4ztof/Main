#include "ActorFactory.h"
#include "Actor.h"
#include "ComponentFactory.h"
#include "RenderComponent.h"
#include "ScriptComponent.h"
#include "TransformComponent.h"

#include <memory> // shared_ptr
#include <string> // string
#include <boost/property_tree/ptree.hpp> // ptree
#include "../utilities/PropertyTreeUtils.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::shared_ptr;
using std::string;
using boost::property_tree::ptree;
using value_type = boost::property_tree::ptree::value_type; // typedef std::pair<const Key, self_type>      value_type; See \boost_1_60_0\boost\property_tree\ptree.hpp
using std::stringstream;
using boost::optional;

namespace base_game {

	const string ActorFactory::ACTOR_NODE_NAME = "actor";

	ActorFactory::ActorFactory() {
		componentFactory = new ComponentFactory;
		componentFactory->registerComponent(RenderComponent::COMPONENT_NAME, &render_component::componentFactory);
		componentFactory->registerComponent(ScriptComponent::COMPONENT_NAME, &script_component::componentFactory);
		componentFactory->registerComponent(TransformComponent::COMPONENT_NAME, &transform_component::componentFactory);
	}

	ActorFactory::~ActorFactory() {
		component_factory::safe_delete(componentFactory);
	}

	unsigned int ActorFactory::getNextActorId() {
		nextActorId++;
		return nextActorId;
	};

	shared_ptr<Actor> ActorFactory::createActor(ptree& actorTree) {
		property_tree_utils::print_tree(actorTree,0);
		optional<ptree&> actorNode = getActorNode(actorTree);
		if (!actorNode.is_initialized()) {
			stringstream ss;
			ss << "Failed to create actor from resource! ";
			logger::error(ss);
			return shared_ptr<Actor>();
		}

		unsigned int actorId = nextActorId;
		if (actorId == INVALID_ACTOR_ID) {
			actorId = getNextActorId();
		}

		shared_ptr<Actor> actor(new Actor(actorId));
		if(!actor->init(actorNode.get())) {
			stringstream ss;
			ss << "Failed to initialize actor! ";
			logger::error(ss);
			return shared_ptr<Actor>();
		}

		for (const value_type& actorChild : actorNode.get()) {


			string name = actorChild.first;
			int compRes = name.compare("<xmlattr>");
			if (compRes == 0) {
				logger::info("To jest <xmlattr>");
			} else {
				shared_ptr<ActorComponent> actorComponent =  componentFactory->create(actorChild);

				if (actorComponent) {
					logger::info("Stworzono actorComponent");
					actor->addComponent(actorComponent);
					actorComponent->setOwner(actor);

					stringstream ss;
					ss << "Post add actorComponent actor use_count: " << actor.use_count();
					logger::info(ss);
				} else {
					logger::error("Nie stworzono actorComponent");
					return shared_ptr<Actor>();
				}
			}
		}

		actor->postInit();
		// see StrongActorPtr ActorFactory::CreateActor(const char* actorResource, TiXmlElement *overrides, const Mat4x4 *pInitialTransform, const ActorId serversActorId)
		//XmlResourceLoader->loadResource();
		return actor;
	}

	optional<ptree&> ActorFactory::getActorNode(ptree& actorTree) {

		optional<ptree&> element = actorTree.get_child_optional(ACTOR_NODE_NAME);
		return element;
	}

	namespace actor_factory {
		void safe_delete(ActorFactory* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}
}

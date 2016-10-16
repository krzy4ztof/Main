#include "BaseGameLogic.h"

#include "../actors/ActorFactory.h"
#include "../gameInitialization/Macros.h"
#include "../resourceCache/ResourceCache.h"

#include <boost/property_tree/ptree.hpp>
#include <memory> // shared_ptr
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using boost::property_tree::ptree;
using std::shared_ptr;
using std::stringstream;

namespace base_game {
	BaseGameLogic::BaseGameLogic() {
		actorFactory = nullptr;
	}

	BaseGameLogic::~BaseGameLogic() {
		actor_factory::safe_delete(actorFactory);
	}

	bool BaseGameLogic::init(ResourceCache* resourceCache) {

		actorFactory = vCreateActorFactory();
		this->resourceCache = resourceCache;
		return true;
	}

	ActorFactory* BaseGameLogic::vCreateActorFactory(void) {
		return new ActorFactory;
	}

	void BaseGameLogic::tempCreateActors() {
		// See StrongActorPtr BaseGameLogic::VCreateActor(const std::string &actorResource, TiXmlElement* overrides, const Mat4x4* initialTransform, const ActorId serversActorId)

		// see TiXmlElement* XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString)

		//Resource resource("player_character.xml");
		//resourceCache->getHandle();

		ptree tree;

		resourceCache->tempLoadAndReturnRootXmlElement("player_character.xml", tree);

		//	actorFactory->createActor("player_character.xml");
		shared_ptr<Actor> actor = actorFactory->createActor(tree);

		if (actor) {
			actor->describeYourself();
			logger::info("Stworzono actor");
		} else {
			logger::error("Nie stworzono actor");
		}

		// Destroy shared_ptr
		actor.reset();

	}


}

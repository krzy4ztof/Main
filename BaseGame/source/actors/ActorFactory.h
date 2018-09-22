#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H
#include "Actor.h"
#include "ComponentFactory.h"
#include "../resourceCache/ResourceCache.h"

#include <memory> // shared_ptr
#include <string> // string
#include <boost/property_tree/ptree.hpp> // ptree
#include <boost/optional.hpp> // boost::optional

namespace base_game {
	class ActorFactory {
		public:
	ActorFactory(std::shared_ptr<ResourceCache> resourceCache);
			virtual ~ActorFactory();

	// std::shared_ptr<base_game::Actor> createActor(boost::property_tree::ptree& actorTree);
	/*
	 std::shared_ptr<base_game::Actor> createActor(
			const std::string& resourceName,
			boost::property_tree::ptree& actorTree);
	 */
	std::shared_ptr<base_game::Actor> createActor(
			const std::string& resourceName);

			boost::optional<boost::property_tree::ptree&> getActorNode(boost::property_tree::ptree& actorTree);
		protected:

	//see TiXmlElement* XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString)
	boost::property_tree::ptree* loadAndReturnRootXmlElement(
			const std::string& resourceName);
	//boost::property_tree::ptree* loadAndReturnRootXmlElement_222(
	//	const std::string& resourceName);

		private:
			const static std::string ACTOR_NODE_NAME;
			const static unsigned int INVALID_ACTOR_ID=0;

			unsigned int nextActorId=0;
			unsigned int getNextActorId();

	//ResourceCache* resourceCache;
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;

			ComponentFactory* componentFactory;

	};
}

#endif // ACTORFACTORY_H

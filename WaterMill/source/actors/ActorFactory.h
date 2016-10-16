#ifndef ACTORFACTORY_H
#define ACTORFACTORY_H
#include "Actor.h"
#include "ComponentFactory.h"

#include <memory> // shared_ptr
#include <string> // string
#include <boost/property_tree/ptree.hpp> // ptree

namespace base_game {
	class ActorFactory {
		public:
			ActorFactory();
			virtual ~ActorFactory();

			//			std::shared_ptr<base_game::Actor> createActor(std::string actorResource);
			std::shared_ptr<base_game::Actor> createActor(boost::property_tree::ptree& actorTree);

			boost::optional<boost::property_tree::ptree&> getActorNode(boost::property_tree::ptree& actorTree);

			//	std::shared_ptr<base_game::Actor> loadActorNode(boost::property_tree::ptree actorNode);


		protected:

		private:
			const static std::string ACTOR_NODE_NAME;
			const static unsigned int INVALID_ACTOR_ID=0;

			unsigned int nextActorId=0;
			unsigned int getNextActorId();

			ComponentFactory* componentFactory;

	};

	namespace actor_factory {
		void safe_delete(ActorFactory* p);
	}

}

#endif // ACTORFACTORY_H

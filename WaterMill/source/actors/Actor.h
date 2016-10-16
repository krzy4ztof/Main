#ifndef ACTOR_H
#define ACTOR_H

//#include "ActorComponent.h"
#include <boost/property_tree/ptree.hpp> // ptree
#include <memory> // shared_ptr
#include <map> // map

namespace base_game {
	class ActorComponent;

	class Actor {
		public:
			Actor(unsigned int actorId);
			virtual ~Actor();
			bool init(boost::property_tree::ptree actorNode);
			void addComponent(std::shared_ptr<ActorComponent>);
			void describeYourself();
			void postInit();


		protected:

		private:
			unsigned int id;
			std::map<unsigned int, std::shared_ptr<ActorComponent>> components;
	};
}

#endif // ACTOR_H

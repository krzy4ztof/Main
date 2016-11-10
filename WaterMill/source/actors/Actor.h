#ifndef ACTOR_H
#define ACTOR_H

#include "ActorComponent.h"
#include <boost/property_tree/ptree.hpp> // ptree
#include <memory> // shared_ptr, weak_ptr
#include <map> // map
#include <string> // string

namespace base_game {
	class Actor {
		public:
			Actor(unsigned int actorId);
			virtual ~Actor();
			bool init(boost::property_tree::ptree actorNode);
			void addComponent(std::shared_ptr<ActorComponent>);
			void describeYourself();
			void postInit();
			void destroy();

			unsigned int getId(void) const {
				return id;
			}

			// template function for retrieving components
			template <class ComponentType>
			std::weak_ptr<ComponentType> getComponent(size_t id) {
				std::map<size_t, std::shared_ptr<ActorComponent>>::iterator findIt = components.find(id);
				if (findIt != components.end()) {
					std::shared_ptr<ActorComponent> pBase(findIt->second);
					std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
					std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
					return pWeakSub;  // return the weak pointer
				} else {
					return std::weak_ptr<ComponentType>();
				}
			}

			template <class ComponentType>
			std::weak_ptr<ComponentType> getComponent(std::string name) {
				size_t id = ActorComponent::getIdFromName(name);
				return getComponent<ComponentType>(id);
			}

			void tempTestComponents();

		protected:

		private:
			unsigned int id;
			std::map<size_t, std::shared_ptr<ActorComponent>> components;
	};
}

#endif // ACTOR_H

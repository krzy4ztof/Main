#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <string>  // string
#include <map> // map
#include "ActorComponent.h"
#include <boost/property_tree/ptree.hpp> // ptree

namespace base_game {
	class ComponentFactory {
		public:
			ComponentFactory();
			virtual ~ComponentFactory();
			void registerComponent(std::string name, ActorComponent* (*factoryFunction)(void));
			//ActorComponent create(std::string name);
			std::shared_ptr<ActorComponent> create(const boost::property_tree::ptree::value_type& componentValueType);





		protected:

		private:
			//std::map<std::string,std::string> creationFunctions;
			std::map<std::string,ActorComponent* (*)(void)> creationFunctions;
	};

	namespace component_factory {
		void safe_delete(ComponentFactory* p);
	}

}
#endif // COMPONENTFACTORY_H

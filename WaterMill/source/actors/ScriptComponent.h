#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "ActorComponent.h"
#include <string> // string
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
	class ScriptComponent : public ActorComponent {
		public:
			const static std::string COMPONENT_NAME;

			ScriptComponent();
			virtual ~ScriptComponent();
			virtual bool vInit(const boost::property_tree::ptree componentNode);
			virtual unsigned int vGetId();
			virtual void describeYourself();
			virtual void vPostInit();

		protected:

		private:
	};


	namespace script_component {
		ActorComponent* componentFactory();
	}
}
#endif // SCRIPTCOMPONENT_H

#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "ActorComponent.h"
#include <string> // string
#include <boost/property_tree/ptree.hpp>// ptree, optional

namespace base_game {
	class ScriptComponent : public ActorComponent {
		public:
			const static std::string COMPONENT_NAME;

			const static std::string SCRIPT_OBJECT_NODE_NAME;
			const static std::string ATTR_CONSTRUCTOR;
			const static std::string ATTR_DESTRUCTOR;

			const static std::string SCRIPT_DATA_NODE_NAME;
			const static std::string ATTR_ACTOR_TYPE;


			ScriptComponent();
			virtual ~ScriptComponent();
			virtual bool vInit(const boost::property_tree::ptree componentNode);
			virtual size_t vGetId();
			virtual void describeYourself();
			virtual void vPostInit();

			void tempScriptComponentFunction();

		protected:
			bool readScriptObjectNode(const boost::property_tree::ptree& scriptObject);
			bool readScriptDataNode(const boost::property_tree::ptree& scriptData);
			std::string constructor, destructor, actorType;
		private:
	};

	namespace script_component {
		ActorComponent* componentFactory();
	}
}
#endif // SCRIPTCOMPONENT_H

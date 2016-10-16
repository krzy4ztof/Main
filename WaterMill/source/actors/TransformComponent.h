#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "ActorComponent.h"
#include <string> // string
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
	class TransformComponent : public ActorComponent {
		public:
			const static std::string COMPONENT_NAME;

			TransformComponent();
			virtual ~TransformComponent();
			virtual bool vInit(const boost::property_tree::ptree componentNode);
			virtual unsigned int vGetId();
			virtual void describeYourself();
			virtual void vPostInit();

		protected:

		private:
	};


	namespace transform_component {
		ActorComponent* componentFactory();
	}

}
#endif // TRANSFORMCOMPONENT_H

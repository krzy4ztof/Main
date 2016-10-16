#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "ActorComponent.h"
#include <string> // string
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
	class RenderComponent : public ActorComponent {
		public:
			const static std::string COMPONENT_NAME;

			RenderComponent();
			virtual ~RenderComponent();
			virtual bool vInit(const boost::property_tree::ptree componentNode);
			virtual unsigned int vGetId();
			virtual void vPostInit();

			virtual void describeYourself();
		protected:

		private:
	};

	namespace render_component {
		ActorComponent* componentFactory();
	}
}
#endif // RENDERCOMPONENT_H

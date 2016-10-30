#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "ActorComponent.h"
#include <string> // string
#include <boost/property_tree/ptree.hpp>// ptree

namespace base_game {
	class TransformComponent : public ActorComponent {
		public:
			const static std::string COMPONENT_NAME;
			const static std::string POSITION_NODE_NAME;
			const static std::string ATTR_X;
			const static std::string ATTR_Y;
			const static std::string ATTR_Z;

			TransformComponent();
			virtual ~TransformComponent();
			virtual bool vInit(const boost::property_tree::ptree componentNode);
			virtual size_t vGetId();
			virtual void describeYourself();
			virtual void vPostInit();

			void tempTransformComponentFunction();


		protected:
			bool readPositionNode(const boost::property_tree::ptree& positionNode);
			int x,y,z;

		private:
	};


	namespace transform_component {
		ActorComponent* componentFactory();
	}

}
#endif // TRANSFORMCOMPONENT_H

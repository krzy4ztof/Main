#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H

//#include "Actor.h"
#include <boost/property_tree/ptree.hpp>// ptree
#include <memory> // shared_ptr

namespace base_game {
	class Actor;

	class ActorComponent {
		public:
			ActorComponent();
			virtual ~ActorComponent();
			virtual bool vInit(const boost::property_tree::ptree componentNode) = 0;
			void setOwner(std::shared_ptr<Actor>);
			virtual unsigned int vGetId() = 0;

			virtual void describeYourself() = 0;
			virtual void vPostInit() = 0;
		protected:
			std::shared_ptr<Actor> pOwner;

		private:
			//  unsigned int id;
	};
}
#endif // ACTORCOMPONENT_H

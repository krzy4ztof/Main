#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include "../actors/ActorFactory.h"
#include "../resourceCache/ResourceCache.h"

namespace base_game {
	class BaseGameLogic {
		public:
			BaseGameLogic();
			virtual ~BaseGameLogic();
			bool init(ResourceCache* resourceCache);
			void tempCreateActors();

		protected:
			ActorFactory* actorFactory;
			ResourceCache* resourceCache;
			virtual ActorFactory* vCreateActorFactory(void);

		private:
	};
}

#endif // BASEGAMELOGIC_H

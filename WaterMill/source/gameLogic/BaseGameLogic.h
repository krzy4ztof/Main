#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include "../actors/ActorFactory.h"
#include "../resourceCache/ResourceCache.h"
#include "../actors/Actor.h"
#include "BaseGameLogic.h"
#include "BaseGameState.h"

#include <memory> // shared_ptr, weak_ptr
#include <map> // map
#include <string> // string

namespace base_game {
	class BaseGameLogic {
		public:
			BaseGameLogic();
			virtual ~BaseGameLogic();
			bool init(ResourceCache* resourceCache);

			void tempCreateActors();
			void tempTestActors();

			virtual std::shared_ptr<Actor> vCreateActor(const std::string &actorResource);  // [rez] note: don't store this strong pointer outside of this class
			virtual void vDestroyActor(const unsigned int actorId);
			virtual std::weak_ptr<Actor> vGetActor(const unsigned int actorId);

			virtual void vChangeState(BaseGameState newState);

		protected:
			std::map<unsigned int, std::shared_ptr<Actor>> actors;

			ActorFactory* actorFactory;
			ResourceCache* resourceCache;
			virtual ActorFactory* vCreateActorFactory(void);

		private:
	};

	namespace base_game_logic {
		void safe_delete(BaseGameLogic* p);
	}
}

#endif // BASEGAMELOGIC_H

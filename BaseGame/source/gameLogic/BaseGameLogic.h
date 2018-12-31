#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include "../actors/ActorFactory.h"
#include "../resourceCache/ResourceCache.h"
#include "../actors/Actor.h"
//#include "BaseGameLogic.h"
#include "BaseGameState.h"
#include "../mainLoop/ProcessManager.h"
#include "../userInterface/IGameView.h"

#include <memory> // shared_ptr, weak_ptr
#include <map> // map
#include <list> // list
#include <string> // string

namespace base_game {
class BaseGameLogic {
public:
	BaseGameLogic();
	virtual ~BaseGameLogic();
	bool init(std::shared_ptr<ResourceCache> resourceCache);

	void tempTestActors();
	// void tempTestProcessManager();
	void tempAddViews();

	virtual void vAddView(std::shared_ptr<IGameView> pView,
			unsigned int actorId = Actor::INVALID_ACTOR_ID);
	virtual void vRemoveView(std::shared_ptr<IGameView> pView);

	virtual std::shared_ptr<Actor> vCreateActor(
			const std::string &actorResource); // [rez] note: don't store this strong pointer outside of this class
	virtual void vDestroyActor(const unsigned int actorId);
	virtual std::weak_ptr<Actor> vGetActor(const unsigned int actorId);

	virtual void vChangeState(BaseGameState newState);

	// Logic Update
	virtual void vOnUpdate(float time, float elapsedTime);
	void onFrameRender(double fTime, float fElapsedTime);
	std::list<std::shared_ptr<IGameView> > getViews();
	virtual void describeYourself();


	// std::list<std::shared_ptr<IGameView> > m_gameViews; // views that are attached to our game

protected:
	float lifetime;			//indicates how long this game has been in session
	BaseGameState state;
	ProcessManager* pProcessManager;				// a game logic entity

	std::map<unsigned int, std::shared_ptr<Actor>> actors;
	std::list<std::shared_ptr<IGameView> > m_gameViews; // views that are attached to our game

	ActorFactory* actorFactory;
	std::shared_ptr<ResourceCache> shrdPtrResourceCache;
	virtual ActorFactory* vCreateActorFactory(
			std::shared_ptr<ResourceCache> resourceCache);

private:
};
}

#endif // BASEGAMELOGIC_H

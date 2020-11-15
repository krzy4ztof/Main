#ifndef BASEGAMELOGIC_H
#define BASEGAMELOGIC_H

#include "../actors/ActorFactory.h"
#include "../resourceCache/ResourceCache.h"
#include "../actors/Actor.h"
//#include "BaseGameLogic.h"
#include "BaseGameState.h"
#include "../mainLoop/ProcessManager.h"
#include "../userInterface/IGameView.h"
#include "../userInterface/HumanView.h"
#include "../graphics3d/OpenGLRenderer.h"

#include <memory> // shared_ptr, weak_ptr
#include <map> // map
#include <list> // list
#include <string> // string

namespace base_game {
class BaseGameLogic {
public:
	BaseGameLogic(std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~BaseGameLogic();
	bool init(std::shared_ptr<ResourceCache> resourceCache);

	void tempTestActors();
	// void tempTestProcessManager();
	void tempAddViews();
	/*
	 void tempAdd01View();
	 void tempAdd02View();
	 void tempAdd03View();
	 void tempAdd04View();
	 */
	//void tempAddView_del(int number);
	//void tempAddView(IGameView* pView);
	//void tempAddView_del(std::shared_ptr<IGameView> pView);


	//void tempSwitchView_del(int key);
	//IGameView* tempSelectView(int key, bool reset);
	//std::shared_ptr<IGameView> tempSelectView_del(int key, bool reset);

//	void tempOnIdle(double fTime, float fElapsedTime);

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
	virtual void vOnUpdateModal(float time, float elapsedTime);

	void onFrameRender(double fTime, float fElapsedTime);
	std::list<std::shared_ptr<IGameView> > getViews();
	virtual void describeYourself();

	void removeAllViews();
	// std::list<std::shared_ptr<IGameView> > m_gameViews; // views that are attached to our game
	std::shared_ptr<HumanView> getHumanView();

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

	//IGameView* tempCurrentView;
//	std::shared_ptr<IGameView> tempCurrentView;
	std::shared_ptr<OpenGLRenderer> openGLRenderer;

private:
};
}

#endif // BASEGAMELOGIC_H

#include "BaseGameLogic.h"
#include "BaseGameState.h"

#include "../actors/ActorFactory.h"
#include "../actors/Actor.h"
#include "../gameInitialization/Macros.h"
#include "../resourceCache/ResourceCache.h"
#include "../utilities/Templates.h"
#include "../mainLoop/ProcessManager.h"
#include "../mainLoop/TempTestProcess.h"
#include "../mainLoop/DelayProcess.h"
#include "../userInterface/IGameView.h"
#include "../userInterface/HumanView.h"
#include "../graphics3d/OpenGLRenderer.h"
/*
 #include "../userInterface/Temp01View.h"
 #include "../userInterface/TempTriangle02View.h"
 #include "../userInterface/Temp03gilView.h"
 #include "../userInterface/Temp04shaderTriangleView.h"
 #include "../userInterface/Temp05View.h"
 #include "../userInterface/Temp06View.h"
 #include "../userInterface/Temp07cubesAnimationView.h"
 */
#include "../userInterface/TempT004figuresView.h"
#include "../userInterface/TempT009jpegGilTextureView.h"
#include "../userInterface/TempT00FpolishFontsView.h"
#include "../userInterface/TempT00DpngGilScanlineView.h"
#include "../userInterface/TempCombinedView.h"



#include "../resourceCache/ZipFile.h"

#include <boost/property_tree/ptree.hpp>
#include <memory> // shared_ptr, weak_ptr, static_pointer_cast
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <string> // string
#include <utility> // pair, make_pair
#include <map> // map
#include <list> // list
#include <fstream> // ifstream
//#include "../userInterface/Temp03gilView.h"

using boost::property_tree::ptree;
using std::shared_ptr;
using std::make_shared;

using std::weak_ptr;
using std::stringstream;
using std::string;
using std::make_pair;
using std::pair;
using std::map;
using std::list;
using std::ifstream;
using std::endl;
using std::static_pointer_cast;

using base_game::BaseGameState::spawningPlayersActors;
using base_game::BaseGameState::running;

namespace base_game {

BaseGameLogic::BaseGameLogic(shared_ptr<OpenGLRenderer> openGLRenderer) :
		lifetime(0) {
	logger::trace("Create BaseGameLogic");
	actorFactory = nullptr;
	pProcessManager = new ProcessManager();
	//tempCurrentView = nullptr;
	state = initializing;
	this->openGLRenderer = openGLRenderer;
}

BaseGameLogic::~BaseGameLogic() {
	removeAllViews();

	templates::safe_delete<ProcessManager>(pProcessManager);
	templates::safe_delete<ActorFactory>(actorFactory);

	map<unsigned int, shared_ptr<Actor>>::iterator actorsIterator;
	for (actorsIterator = actors.begin(); actorsIterator != actors.end();
			actorsIterator++) {
		actorsIterator->second->destroy();
	}
	actors.clear();

	logger::trace("Destroy BaseGameLogic");
}

void BaseGameLogic::removeAllViews() {

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;


	 for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
	 viewIterator++) {
		(*viewIterator)->vTerminate();
	 }


	while (!m_gameViews.empty()) {

		m_gameViews.pop_front();
	}
}

shared_ptr<HumanView> BaseGameLogic::getHumanView() {
	shared_ptr<HumanView> humanView;
	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {
		if ((*viewIterator)->vGetType() == GameView_Human) {
			//humanView = (*viewIterator)->get();

			shared_ptr<IGameView> pIGameView(*viewIterator);
			//humanView = static_cast<shared_ptr<HumanView>>(&*pIGameView);
			//humanView = static_cast<shared_ptr<HumanView>>(pIGameView);
			//humanView = static_cast<shared_ptr<HumanView>>(*pIGameView);

			humanView = static_pointer_cast<HumanView>(pIGameView);


			//pView = static_cast<HumanView *>(&*pIGameView);
			break;
		}
	}
	return humanView;
}

bool BaseGameLogic::init(shared_ptr<ResourceCache> resourceCache) {

	actorFactory = vCreateActorFactory(resourceCache);
	this->shrdPtrResourceCache = resourceCache;
	return true;
}

void BaseGameLogic::vAddView(shared_ptr<IGameView> pView,
		unsigned int actorId) {

	// Uwaga:
	// linikjki:
	// 	(*viewIterator)->tempIsActive = false; // do skasowania
// zostaną zastąpione poprzez
// 		(*viewIterator)->vDeactivate(); // zastapi tempIsActive

	// This makes sure that all views have a non-zero view id.
	int viewId = static_cast<int>(m_gameViews.size());

	/*
	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;


	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {
//		(*viewIterator)->tempIsActive = false; // do skasowania

		//(*viewIterator)->vDeactivate(); // zastapi tempIsActive
	}
	 */

//	pView->tempIsActive = true; // do skasowania
	//pView->vDeactivate(); // zastapi tempIsActive

	m_gameViews.push_back(pView);
	pView->vOnAttach(viewId, actorId);
	pView->vOnRestore();
}

void BaseGameLogic::vRemoveView(shared_ptr<IGameView> pView) {
	m_gameViews.remove(pView);
}

ActorFactory* BaseGameLogic::vCreateActorFactory(
		shared_ptr<ResourceCache> resourceCache) {
	return new ActorFactory(resourceCache);
}

void BaseGameLogic::vChangeState(BaseGameState newState) {

}

shared_ptr<Actor> BaseGameLogic::vCreateActor(const string& actorResource) {
	//ptree tree;
	//shrdPtrResourceCache->tempLoadAndReturnRootXmlElement(actorResource, tree);

	//	actorFactory->createActor("player_character.xml");
//	shared_ptr<Actor> pActor = actorFactory->createActor(actorResource, tree);
	shared_ptr<Actor> pActor = actorFactory->createActor(actorResource);

	if (pActor) {
		pActor->describeYourself();

		unsigned int actorId = pActor->getId();
		pair<unsigned int, shared_ptr<Actor>> actorPair = make_pair(actorId,
				pActor);

		actors.insert(actorPair);

		//	m_actors.insert(std::make_pair(pActor->GetId(), pActor));

		return pActor;
	} else {
		return shared_ptr<Actor>();
	}

}

void BaseGameLogic::vDestroyActor(const unsigned int actorId) {
	// We need to trigger a synchronous event to ensure that any systems responding to this event can still access a
	// valid actor if need be.  The actor will be destroyed after this.

	// TODO:
	//shared_ptr<EvtData_Destroy_Actor> pEvent(GCC_NEW EvtData_Destroy_Actor(actorId));
	//IEventManager::Get()->VTriggerEvent(pEvent);

	map<unsigned int, shared_ptr<Actor>>::iterator findIt = actors.find(
			actorId);
	if (findIt != actors.end()) {
		findIt->second->destroy();
		actors.erase(findIt);
	}
}

weak_ptr<Actor> BaseGameLogic::vGetActor(const unsigned int actorId) {

	map<unsigned int, shared_ptr<Actor>>::iterator findIt = actors.find(
			actorId);
	if (findIt != actors.end()) {
		return findIt->second;
	}
	return weak_ptr<Actor>();
}

void BaseGameLogic::vOnUpdate(float time, float elapsedTime) {

	//int deltaMilliseconds = int(elapsedTime * 1000.0f);
	int deltaMilliseconds = int(elapsedTime);

	lifetime += elapsedTime;

	stringstream ss;
	switch (state) {

	case spawningPlayersActors: {
		break;
	}

	case tempActivateFiguresView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempT004figuresView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();

		vAddView(pView);

		break;
	}
	case tempActivateJpegView: {
		removeAllViews(); //- breaks the game
		shared_ptr<IGameView> pView = make_shared<TempT009jpegGilTextureView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}
	case tempActivateFontsView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempT00FpolishFontsView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}
	case tempActivatePngView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempT00DpngGilScanlineView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}
	case tempActivateCombinedView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempCombinedView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}


	case running: {
		pProcessManager->updateProcesses(deltaMilliseconds);
		break;
	}
	}

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	// update all game views
	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {

		//if ((*viewIterator)->tempIsActive) {
		(*viewIterator)->vOnUpdate(deltaMilliseconds);
		//}
	}

	// update game actors
	map<unsigned int, shared_ptr<Actor>>::iterator actorsIterator;
	for (actorsIterator = actors.begin(); actorsIterator != actors.end();
			actorsIterator++) {
		actorsIterator->second->update(deltaMilliseconds);
	}
	/*
	 // update all game views
	 for (GameViewList::iterator it = m_gameViews.begin(); it != m_gameViews.end(); ++it)
	 {
	 (*it)->VOnUpdate(deltaMilliseconds);
	 }

	 // update game actors
	 for (ActorMap::const_iterator it = m_actors.begin(); it != m_actors.end(); ++it)
	 {
	 it->second->Update(deltaMilliseconds);
	 }
	 */
}

void BaseGameLogic::vOnUpdateModal(float time, float elapsedTime) {
	/*
	 * if (m_pGame) {
	 int timeNow = timeGetTime();
	 int deltaMilliseconds = timeNow - currentTime;
	 for (GameViewList::iterator i = m_pGame->m_gameViews.begin();
	 i != m_pGame->m_gameViews.end(); ++i) {
	 (*i)->VOnUpdate(deltaMilliseconds);
	 }
	 currentTime = timeNow;
	 DXUTRender3DEnvironment();
	 }
	 *
	 */

	//int deltaMilliseconds = int(elapsedTime * 1000.0f);
	int deltaMilliseconds = int(elapsedTime);

	lifetime += elapsedTime;

	stringstream ss;

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	// update all game views
	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {

		//if ((*viewIterator)->tempIsActive) {
		(*viewIterator)->vOnUpdate(deltaMilliseconds);
		//}
	}
}


/*
void BaseGameLogic::tempOnIdle(double fTime, float fElapsedTime) {
	if (tempCurrentView != nullptr) {
		if (tempCurrentView->isActive()) {
			tempCurrentView->vOnRender(fTime, fElapsedTime);
		}
	}
}
 */

/**
 * See void CALLBACK GameCodeApp::OnD3D11FrameRender
 */
void BaseGameLogic::onFrameRender(double time, float elapsedTime) {

	// tempOnIdle(time, elapsedTime);

	/*
	 for(GameViewList::iterator i=pGame->m_gameViews.begin(),
	 end=pGame->m_gameViews.end(); i!=end; ++i) {
	 (*i)->VOnRender(fTime, fElapsedTime);
	 }
	 */

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {

		//if ((*viewIterator)->tempIsActive) {
			(*viewIterator)->vOnRender(time, elapsedTime);
		//}
	}

}

list<shared_ptr<IGameView> > BaseGameLogic::getViews() {
	return m_gameViews;
}


/*
void BaseGameLogic::tempSwitchView_del(int key) {
	logger::info("BaseGameLogic switchView");
	shared_ptr<IGameView> gameView;
	gameView = this->tempSelectView_del(key, false);
}

shared_ptr<IGameView> BaseGameLogic::tempSelectView_del(int key, bool reset) {


	shared_ptr<IGameView> gameView;


	if (key == GLFW_KEY_1) {

	} else if (key == GLFW_KEY_2) {

	} else if (key == GLFW_KEY_3) {

	} else if (key == GLFW_KEY_4) {

	} else if (key == GLFW_KEY_5) {

	}

	tempAddView_del(gameView);

	return gameView;
}

void BaseGameLogic::tempAddView_del(int number) {

	shared_ptr<IGameView> gameView;

	tempAddView_del(gameView);
}

void BaseGameLogic::tempAddView_del(shared_ptr<IGameView> gameView) {
	gameView->tempVLoadGameDelegate();
	shared_ptr<IGameView> pView = shared_ptr<IGameView>(gameView);

	vAddView(pView, 0);
}
 */

void BaseGameLogic::tempTestActors() {
	vChangeState(spawningPlayersActors);

	map<unsigned int, shared_ptr<Actor>>::iterator actorsIterator;
	for (actorsIterator = actors.begin(); actorsIterator != actors.end();
			actorsIterator++) {
		actorsIterator->second->tempTestComponents();
	}
}

void BaseGameLogic::describeYourself() {
	logger::info("BaseGameLogic describeYourself");
}

}

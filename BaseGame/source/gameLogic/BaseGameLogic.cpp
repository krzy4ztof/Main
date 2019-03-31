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


#include "../resourceCache/ZipFile.h"

#include <boost/property_tree/ptree.hpp>
#include <memory> // shared_ptr, weak_ptr
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
using std::weak_ptr;
using std::stringstream;
using std::string;
using std::make_pair;
using std::pair;
using std::map;
using std::list;
using std::ifstream;
using std::endl;

using base_game::BaseGameState::spawningPlayersActors;
using base_game::BaseGameState::running;

namespace base_game {

BaseGameLogic::BaseGameLogic() :
		lifetime(0) {
	logger::trace("Create BaseGameLogic");
	actorFactory = nullptr;
	pProcessManager = new ProcessManager();
	tempCurrentView = nullptr;
	state = initializing;
}

BaseGameLogic::~BaseGameLogic() {

	while (!m_gameViews.empty()) {
		m_gameViews.pop_front();
	}

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

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {
		(*viewIterator)->tempIsActive = false; // do skasowania

		//(*viewIterator)->vDeactivate(); // zastapi tempIsActive
	}

	pView->tempIsActive = true; // do skasowania
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

	case running: {
		pProcessManager->updateProcesses(deltaMilliseconds);
		break;
	}
	}
}

void BaseGameLogic::tempOnIdle(double fTime, float fElapsedTime) {
	if (tempCurrentView != nullptr) {
		if (tempCurrentView->isActive()) {
			tempCurrentView->vOnRender(fTime, fElapsedTime);
		}
	}
}

void BaseGameLogic::onFrameRender(double time, float elapsedTime) {

	tempOnIdle(time, elapsedTime);

	/*
	 for(GameViewList::iterator i=pGame->m_gameViews.begin(),
	 end=pGame->m_gameViews.end(); i!=end; ++i) {
	 (*i)->VOnRender(fTime, fElapsedTime);
	 }
	 */

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {

		if ((*viewIterator)->tempIsActive) {
			(*viewIterator)->vOnRender(time, elapsedTime);
		}
	}

}

list<shared_ptr<IGameView> > BaseGameLogic::getViews() {
	return m_gameViews;
}


void BaseGameLogic::tempAddViews() {

	IGameView* gameView = new HumanView();
	gameView->tempVLoadGameDelegate();
	shared_ptr<IGameView> pView = shared_ptr<IGameView>(gameView);

	vAddView(pView, 0);

}

/*
void BaseGameLogic::tempAdd01View() {
	// IGameView* gameView = new Temp01View();
	IGameView* gameView = temp_01_view::getView();
	tempAddView(gameView);
}

void BaseGameLogic::tempAdd02View() {
//	IGameView* gameView = new TempTriangle02View();
	IGameView* gameView = temp_triangle_02_view::getView();
	tempAddView(gameView);
}

void BaseGameLogic::tempAdd03View() {
//	IGameView* gameView = new Temp03gilView();
	IGameView* gameView = temp_03_gil_view::getView();
	tempAddView(gameView);
}

void BaseGameLogic::tempAdd04View() {
//	IGameView* gameView = new Temp03gilView();
	IGameView* gameView = temp_04_shader_triangle_view::getView();
	tempAddView(gameView);
}
 */

void BaseGameLogic::tempSwitchView(int key) {
// Uwaga
	// 		tempCurrentView->vDeactivate();
// i
	// 		gameView->vActivate();
	// bedzie przeniesone do
	// IGameView* BaseGameLogic::tempSelectView(int key, bool reset) {
	// lub do
	// void BaseGameLogic::vAddView(shared_ptr<IGameView> pView, unsigned int actorId) {



	logger::info("BaseGameLogic switchView");

	IGameView* gameView = nullptr;

	if (tempCurrentView != nullptr) {
		tempCurrentView->vDeactivate();
	}

	gameView = this->tempSelectView(key, false);

	if (gameView != nullptr) {
		gameView->vActivate();
		tempCurrentView = gameView;

	}

	/*
	if (tempCurrentView != nullptr) {
		tempCurrentView->vActivate();
	}
	 */
}

IGameView* BaseGameLogic::tempSelectView(int key, bool reset) {
	IGameView* gameView = nullptr;

	// Uwaga
	// Najpierw nalezy sprawdzic czy view jest w BaseGameLogic->m_gameViews
	// Jesli tak to aktywowac go a deaktywowac inne view
	// Jesli nie to dodac go (tempAddView(view)) i aktywowac a deaktywowac inne
//
	// skasowac tez view->tempIsActive
	// zastapic poprzez view->active
	//
	// skasowac tez tempCurrentView
	// wprowadzic BaseGameLogic->getActiveView()
	// tylko jeden view moze byc aktywny
//
	// nie deaktywowac powtornie zdeaktywowanych vidokow
	// nie aktywowac powtornie aktywowanych widokow

	if (key == GLFW_KEY_8) {
		// tempCurrentView = temp_t004_figures_view::getView(reset);

		//
		gameView = temp_t004_figures_view::getView(reset);
	} else if (key == GLFW_KEY_9) {
		// tempCurrentView = temp_t004_figures_view::getView(reset);

		//
		gameView = temp_t009_jpeg_gil_texture_view::getView(reset);
	}


	tempAddView(gameView);

	return gameView;
}

void BaseGameLogic::tempAddView(int number) {
//	IGameView* gameView = new Temp03gilView();
	IGameView* gameView = nullptr;

	/*
	if (number == 1) {
		gameView = temp_01_view::getView();
	} else if (number == 2) {
		gameView = temp_triangle_02_view::getView();
	} else if (number == 3) {
		gameView = temp_03_gil_view::getView();
	} else if (number == 4) {
		gameView = temp_04_shader_triangle_view::getView();
	} else if (number == 5) {
		gameView = temp_05_view::getView();
	} else if (number == 6) {
		gameView = temp_06_view::getView();
	} else if (number == 7) {
		gameView = temp_07_cubes_animation_view::getView();
	}
	 */
	
	tempAddView(gameView);
}

void BaseGameLogic::tempAddView(IGameView* gameView) {
	gameView->tempVLoadGameDelegate();
	shared_ptr<IGameView> pView = shared_ptr<IGameView>(gameView);

	vAddView(pView, 0);
}

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

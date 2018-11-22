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
#include "../resourceCache/ZipFile.h"

#include <boost/property_tree/ptree.hpp>
#include <memory> // shared_ptr, weak_ptr
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include <string> // string
#include <utility> // pair, make_pair
#include <map> // map
#include <fstream> // ifstream

using boost::property_tree::ptree;
using std::shared_ptr;
using std::weak_ptr;
using std::stringstream;
using std::string;
using std::make_pair;
using std::pair;
using std::map;
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
	// This makes sure that all views have a non-zero view id.
	int viewId = static_cast<int>(m_gameViews.size());
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

void BaseGameLogic::onFrameRender(double time, float elapsedTime) {

	/*
	 for(GameViewList::iterator i=pGame->m_gameViews.begin(),
	 end=pGame->m_gameViews.end(); i!=end; ++i) {
	 (*i)->VOnRender(fTime, fElapsedTime);
	 }
	 */

	std::list<std::shared_ptr<IGameView> >::iterator viewIterator;

	for (viewIterator = m_gameViews.begin(); viewIterator != m_gameViews.end();
			viewIterator++) {
		(*viewIterator)->vOnRender(time, elapsedTime);
	}

}


void BaseGameLogic::tempAddViews() {

	IGameView* gameView = new HumanView();
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


void BaseGameLogic::tempCreateActors() {
	// See StrongActorPtr BaseGameLogic::VCreateActor(const std::string &actorResource, TiXmlElement* overrides, const Mat4x4* initialTransform, const ActorId serversActorId)

	// see TiXmlElement* XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString)

	//Resource resource("player_character.xml");
	//resourceCache->getHandle();

	//ptree tree;

	//	actorFactory->createActor("player_character.xml");
	//shared_ptr<Actor> actor = actorFactory->createActor(tree);
	shared_ptr<Actor> actor = actorFactory->createActor(
			"actors/player_character.xml");

	stringstream ss;
	ss << "Post init actor use_count: " << actor.use_count();
	logger::trace(ss);

	if (actor) {
		actor->describeYourself();
		logger::trace("Stworzono actor");
	} else {
		logger::error("Nie stworzono actor");
	}

	actor->destroy();
	ss << "Post destroy actor use_count: " << actor.use_count();

	// Destroy shared_ptr
	actor.reset();
	ss << "Post reset actor use_count: " << actor.use_count();

	logger::trace(ss);

}

}

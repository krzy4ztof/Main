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

BaseGameLogic::BaseGameLogic() {
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

bool BaseGameLogic::init(ResourceCache* resourceCache) {

	actorFactory = vCreateActorFactory();
	this->resourceCache = resourceCache;
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

ActorFactory* BaseGameLogic::vCreateActorFactory(void) {
	return new ActorFactory;
}

void BaseGameLogic::vChangeState(BaseGameState newState) {

}

shared_ptr<Actor> BaseGameLogic::vCreateActor(const string& actorResource) {
	ptree tree;
	resourceCache->tempLoadAndReturnRootXmlElement(actorResource, tree);

	//	actorFactory->createActor("player_character.xml");
	shared_ptr<Actor> pActor = actorFactory->createActor(tree);

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

void BaseGameLogic::tempTestProcessManager() {
	state = running;

	shared_ptr<Process> pProcess1(
			new TempTestProcess("Initalize Action GROUP 1"));
	pProcessManager->attachProcess(pProcess1);
	shared_ptr<Process> pProcess2(new TempTestProcess("Second Action GROUP 1"));
	pProcess1->attachChild(pProcess2);
	shared_ptr<Process> pProcess3(new TempTestProcess("Third Action GROUP 1"));
	pProcess1->attachChild(pProcess3);
	shared_ptr<Process> pProcess4(new TempTestProcess("Last Action GROUP 1"));
	pProcess2->attachChild(pProcess4);

	shared_ptr<Process> pDelay(new DelayProcess(500)); // delay for 0.5 second
	pProcessManager->attachProcess(pDelay);

	shared_ptr<Process> pProcess1g2(
			new TempTestProcess("Initalize Action GROUP 2"));
	pDelay->attachChild(pProcess1g2);
	shared_ptr<Process> pProcess2g2(
			new TempTestProcess("Second Action GROUP 2"));
	pProcess1g2->attachChild(pProcess2g2);
	shared_ptr<Process> pProcess3g2(
			new TempTestProcess("Third Action GROUP 2"));
	pProcess2g2->attachChild(pProcess3g2);

	//vOnUpdate(0,0);

	shared_ptr<Process> pProcess1g3(
			new TempTestProcess("Initalize Action GROUP 3"));
	pProcessManager->attachProcess(pProcess1g3);
	shared_ptr<Process> pProcess2g3(
			new TempTestProcess("Second Action GROUP 3"));
	pProcess1g3->attachChild(pProcess2g3);
	shared_ptr<Process> pProcess3g3(
			new TempTestProcess("Third Action GROUP 3"));
	pProcess1g3->attachChild(pProcess3g3);

	/*
	 vOnUpdate(0,1);
	 vOnUpdate(0,2);
	 vOnUpdate(0,3);
	 vOnUpdate(0,4);
	 vOnUpdate(0,5);
	 vOnUpdate(0,6);
	 vOnUpdate(0,7);
	 */

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

	ptree tree;

	resourceCache->tempLoadAndReturnRootXmlElement(
			"actors/player_character.xml", tree);

	//	actorFactory->createActor("player_character.xml");
	shared_ptr<Actor> actor = actorFactory->createActor(tree);

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

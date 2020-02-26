/*
 * TestGame.cpp
 *
 *  Created on: 23 wrz 2018
 *      Author: Krzysztof
 */

#include "TestGame.h"
#include "TestGameLogic.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"

#include <memory> // shared_ptr, weak_ptr

using std::string;
using std::shared_ptr;
namespace logger = base_game::logger;
using base_game::BaseGameLogic;
using base_game::ResourceCache;
using base_game::InitOptions;
using base_game::OpenGLRenderer;

namespace base_game_test {

const string TestGame::GAME_APP_DIRECTORY = "GameEngine\\Watermill\\1.0";

TestGame::TestGame() {
	logger::trace("Create TestGame");

}

TestGame::~TestGame() {
	logger::trace("Destroy TestGame");
}

BaseGameLogic* TestGame::createGameAndView(
		shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer) {
	logger::trace("TestGame::createGameAndView");
	m_pGame = new TestGameLogic(openGLRenderer);
	m_pGame->init(resourceCache);
	return m_pGame;
}

string TestGame::vGetGameAppDirectory() {
	return GAME_APP_DIRECTORY;
}

void TestGame::setInitOptions(InitOptions* initOptions) {
	this->initOptions = initOptions;
}

void TestGame::setResourceCache(shared_ptr<ResourceCache> resourceCache) {
	this->shrdPtrResourceCache = resourceCache;
}

} /* namespace base_game_test */

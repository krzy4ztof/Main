#include "WatermillGame.h"
#include "WatermillLogic.h"
#include "../userInterface/MainMenuView.h"

#include "../../../BaseGame/source/debugging/Logger.h"
//#include <debugging/Logger.h>
#include "../../../BaseGame/source/userInterface/IGameView.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

#include <iostream> // cout, endl
#include <string>
#include <memory> // shared_ptr, weak_ptr

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
namespace logger = base_game::logger;
using base_game::GameCodeApp;
using base_game::BaseGameLogic;
using base_game::ResourceCache;
using base_game::IGameView;
using base_game::OpenGLRenderer;
using base_game::GameMessages;
using base_game::VideoSystemGLFW;

namespace watermill_base {
const string WatermillGame::GAME_APP_DIRECTORY = "GameEngine\\Watermill\\1.0";

WatermillGame::WatermillGame() {
	logger::trace("Create WatermillGame");
}

WatermillGame::~WatermillGame() {
	logger::trace("Destroy WatermillGame");
}

BaseGameLogic* WatermillGame::createGameAndView(
		shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer,
		shared_ptr<GameMessages> gameMessages) {
	logger::trace("WatermillGame::createGameAndView");
	m_pGame = new WatermillLogic(openGLRenderer, gameMessages);
	m_pGame->init(resourceCache);

	IGameView *mainMenuView = new MainMenuView(resourceCache, openGLRenderer,
			gameMessages);
	mainMenuView->tempVLoadGameDelegate();

	shared_ptr<IGameView> pView = shared_ptr<IGameView>(mainMenuView);
	m_pGame->vAddView(pView);

	return m_pGame;
}

string WatermillGame::vGetGameAppDirectory() {
	return GAME_APP_DIRECTORY;
}

void WatermillGame::setResourceCache(shared_ptr<ResourceCache> resourceCache) {
	this->shrdPtrResourceCache = resourceCache;
}

void WatermillGame::setVideoSystemGLFW(
		shared_ptr<VideoSystemGLFW> videoSystemGLFW) {
	this->videoSystemGLFW = videoSystemGLFW;
}

}

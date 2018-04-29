#include "WatermillGame.h"
#include "WatermillLogic.h"

#include "../../../BaseGame/source/debugging/Logger.h"
//#include <debugging/Logger.h>

#include <iostream> // cout, endl
#include <string>
#include <memory> // shared_ptr, weak_ptr



using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
namespace logger=base_game::logger;
using base_game::GameCodeApp;
using base_game::BaseGameLogic;
using base_game::ResourceCache;

namespace watermill {
	const string WatermillGame::GAME_APP_DIRECTORY = "GameEngine\\Watermill\\1.0";

	WatermillGame::WatermillGame() {
		logger::trace("Create WatermillGame");
	}

	WatermillGame::~WatermillGame() {
		logger::trace("Destroy WatermillGame");
	}

BaseGameLogic* WatermillGame::createGameAndView(
		shared_ptr<ResourceCache> resourceCache) {
		logger::trace("WatermillGame::createGameAndView");
		m_pGame = new WatermillLogic();
		m_pGame->init(resourceCache);

		//		shared_ptr<IGameView> menuView(GCC_NEW MainMenuView());
		//		m_pGame->VAddView(menuView);

		return m_pGame;
	}

	string WatermillGame::vGetGameAppDirectory() {
		return GAME_APP_DIRECTORY;
	}

}

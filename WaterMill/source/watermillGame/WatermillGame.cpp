#include "WatermillGame.h"
#include "WatermillLogic.h"
#include <iostream> // cout, endl
#include <string>
#include "../debugging/Logger.h"

using std::cout;
using std::endl;
using std::string;
namespace logger=base_game::logger;
using base_game::GameCodeApp;
using base_game::BaseGameLogic;
using base_game::ResourceCache;

namespace watermill {
	const string WatermillGame::GAME_APP_DIRECTORY = "GameEngine\\Watermill\\1.0";

	WatermillGame::WatermillGame() {
		logger::info("Create WatermillGame");
	}

	WatermillGame::~WatermillGame() {
		logger::info("Destroy WatermillGame");
	}

	BaseGameLogic *WatermillGame::createGameAndView(ResourceCache* resourceCache) {
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

#include "WatermillGame.h"
#include "WatermillLogic.h"
#include <iostream> // cout, endl
#include <string>
#include "../debugging/Logger.h"

using std::cout;
using std::endl;
using std::string;

namespace watermill {
	const string WatermillGame::GAME_APP_DIRECTORY = "GameEngine\\Watermill\\1.0";

	WatermillGame::WatermillGame() {
		//ctor
	}

	WatermillGame::~WatermillGame() {
		//dtor
	}

	BaseGameLogic *WatermillGame::createGameAndView() {
		logger::trace("WatermillGame::createGameAndView");
		m_pGame = new WatermillLogic();
		m_pGame->Init();

		//		shared_ptr<IGameView> menuView(GCC_NEW MainMenuView());
		//		m_pGame->VAddView(menuView);

		return m_pGame;
	}

	string WatermillGame::vGetGameAppDirectory() {
		return GAME_APP_DIRECTORY;
	}

}

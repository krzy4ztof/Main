#include "GameMain.h"

#include "../gameInitialization/GameCodeApp.h"
#include "../watermillGame/WatermillGame.h"
#include "../debugging/Logger.h"


namespace watermill {

	GameMain::GameMain() {
	}

	GameMain::~GameMain() {
	}

	int GameMain::init(int argc, char** argv) {

		//TODO: see
		// C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
		// \GCC4\GameCode4\GameCode4.cpp

		//  INT WINAPI GameCode4(HINSTANCE hInstance,
		//                 HINSTANCE hPrevInstance,
		//                 LPWSTR    lpCmdLine,
		//                 int       nCmdShow)
		bool returnCode = true;

		logger::init();
		logger::test();

		GameCodeApp * gameCodeApp;
		gameCodeApp = new WatermillGame;

		returnCode = gameCodeApp->initAllOptions();

		if (!returnCode) {
			logger::error("gameCodeApp init Options failed");
			logger::destroy();
			return 1;
		}

		returnCode = gameCodeApp->initInstance();

		if (!returnCode) {
			logger::error("gameCodeApp init failed");
			logger::destroy();
			return 1;
		}

		gameCodeApp->mainLoop();

		game_code_app::safe_delete(gameCodeApp);
		logger::trace("gameCodeApp init succeeded");
		logger::destroy();
		return 0;

	}
}


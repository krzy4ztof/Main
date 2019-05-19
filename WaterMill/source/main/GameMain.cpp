#include "GameMain.h"

#include "../watermillGame/WatermillGame.h"

/*
 #include "../gameInitialization/GameCodeApp.h"

 #include "../debugging/Logger.h"
 #include "../utilities/Templates.h"
 */

#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/utilities/Templates.h"

//#include <gameInitialization/GameCodeApp.h>
//#include <debugging/Logger.h>
//#include <utilities/Templates.h>

//#include <GameCodeApp.h>
//#include <debugging/Logger.h>
//#include <utilities/Templates.h>

#include <iostream> // cout, endl

using std::cout;
using std::endl;

namespace logger = base_game::logger;
namespace templates = base_game::templates;
//namespace game_code_app=base_game::game_code_app;
using base_game::GameCodeApp;

namespace watermill {

GameMain::GameMain() {
	cout << "Create GameMain" << endl;
}

GameMain::~GameMain() {
	cout << "Destroy GameMain" << endl;
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

	logger::init("watermill.log");
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

	//game_code_app::safe_delete(gameCodeApp);
	//templates::safe_delete<WatermillGame>(gameCodeApp);
	templates::safe_delete<GameCodeApp>(gameCodeApp);

	logger::info("gameCodeApp init succeeded");
	logger::destroy();
	return 0;

}
}


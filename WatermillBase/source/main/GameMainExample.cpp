#include "GameMainExample.h"

#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/utilities/Templates.h"

#include <iostream> // cout, endl


using std::cout;
using std::endl;

namespace logger = base_game::logger;

namespace watermill_base {

GameMainExample::GameMainExample() {
	cout << "Create GameMainExample" << endl;
}

GameMainExample::~GameMainExample() {
	cout << "Destroy GameMainExample" << endl;
}

int GameMainExample::init() {
	bool returnCode = true;

	/*
	logger::init("watermill_base.log");
	logger::test();

	logger::info("GAME MAIN EXAMPLE init succeeded");
	logger::destroy();
	 */

	return 0;

}
}


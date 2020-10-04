/*
 * TestGame.h
 *
 *  Created on: 23 wrz 2018
 *      Author: Krzysztof
 */

#ifndef TESTGAME_TESTGAME_H_
#define TESTGAME_TESTGAME_H_

#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

#include <string>
#include <memory> // shared_ptr, weak_ptr

namespace base_game_test {

class TestGame: public base_game::GameCodeApp {
public:
	const static std::string GAME_APP_DIRECTORY;

	TestGame();
	virtual ~TestGame();
	virtual std::string vGetGameAppDirectory();
	void setInitOptions(base_game::InitOptions* initOptions);

	void setResourceCache(
			std::shared_ptr<base_game::ResourceCache> resourceCache);

protected:
	virtual base_game::BaseGameLogic* createGameAndView(
			std::shared_ptr<base_game::ResourceCache> resourceCache,
			std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer,
			std::shared_ptr<base_game::GameMessages> gameMessages);
private:
};
} /* namespace base_game_test */

#endif /* TESTGAME_TESTGAME_H_ */

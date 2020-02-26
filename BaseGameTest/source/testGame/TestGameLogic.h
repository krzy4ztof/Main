/*
 * TestGameLogic.h
 *
 *  Created on: 23 wrz 2018
 *      Author: Krzysztof
 */

#ifndef TESTGAME_TESTGAMELOGIC_H_
#define TESTGAME_TESTGAMELOGIC_H_

#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"

#include <memory> // shared_ptr, weak_ptr

namespace base_game_test {

class TestGameLogic: public base_game::BaseGameLogic {
public:
	TestGameLogic(std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer);
	virtual ~TestGameLogic();

	virtual void vChangeState(base_game::BaseGameState newState);
	virtual void describeYourself();
};

} /* namespace base_game_test */

#endif /* TESTGAME_TESTGAMELOGIC_H_ */

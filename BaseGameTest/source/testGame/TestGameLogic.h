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

namespace base_game_test {

class TestGameLogic: public base_game::BaseGameLogic {
public:
	TestGameLogic();
	virtual ~TestGameLogic();

	virtual void vChangeState(base_game::BaseGameState newState);
	virtual void describeYourself();
};

} /* namespace base_game_test */

#endif /* TESTGAME_TESTGAMELOGIC_H_ */

/*
 * TestGameLogic.cpp
 *
 *  Created on: 23 wrz 2018
 *      Author: Krzysztof
 */

#include "TestGameLogic.h"
#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/debugging/Logger.h"

using base_game::BaseGameState;
namespace logger = base_game::logger;

namespace base_game_test {

TestGameLogic::TestGameLogic() {
	logger::trace("Create TestGameLogic");

}

TestGameLogic::~TestGameLogic() {
	logger::trace("Destroy TestGameLogic");
}

void TestGameLogic::vChangeState(BaseGameState newState) {
}

void TestGameLogic::describeYourself() {
	logger::info("TestGameLogic describeYourself");
}


} /* namespace base_game_test */

/*
 * TestGameLogic.cpp
 *
 *  Created on: 23 wrz 2018
 *      Author: Krzysztof
 */

#include "TestGameLogic.h"
#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"

#include <memory> // shared_ptr

using base_game::BaseGameState;
using base_game::BaseGameLogic;
using base_game::OpenGLRenderer;
namespace logger = base_game::logger;

using std::shared_ptr;

namespace base_game_test {

TestGameLogic::TestGameLogic(shared_ptr<OpenGLRenderer> openGLRenderer) :
		BaseGameLogic(openGLRenderer) {
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

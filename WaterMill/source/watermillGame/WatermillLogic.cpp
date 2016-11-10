#include "WatermillLogic.h"
#include "../gameLogic/BaseGameState.h"
#include "../gameLogic/BaseGameLogic.h"
#include "../debugging/Logger.h"
#include "../actors/Actor.h"

#include <sstream>      // std::stringstream
#include <memory> // shared_ptr

using std::shared_ptr;
using std::stringstream;

using base_game::BaseGameLogic;
using base_game::BaseGameState;
using base_game::Actor;
using base_game::BaseGameState::spawningPlayersActors;
using base_game::BaseGameState::running;


namespace logger = base_game::logger;

namespace watermill {
	WatermillLogic::WatermillLogic() {
		logger::info("Create WatermillLogic");
	}

	WatermillLogic::~WatermillLogic() {
		logger::info("Destroy WatermillLogic");
	}

	void WatermillLogic::vChangeState(BaseGameState newState) {
		BaseGameLogic::vChangeState(newState);

		stringstream ss;

		switch(newState) {

			case spawningPlayersActors: {

					shared_ptr<Actor> pActor = vCreateActor("actors/player_character.xml");
					if (pActor) {
						ss << "Actor Created!!!: ";
						logger::trace(ss);
					} else {
						ss << "Actor NOT Created!!!: ";
						logger::trace(ss);
					}
					break;
				}

			case running: {
					break;
				}
		}
	}
}

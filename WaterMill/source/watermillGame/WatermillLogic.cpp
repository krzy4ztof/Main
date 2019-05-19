#include "WatermillLogic.h"

/*
 #include "../gameLogic/BaseGameState.h"
 #include "../gameLogic/BaseGameLogic.h"
 #include "../debugging/Logger.h"
 #include "../actors/Actor.h"
 */

#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/actors/Actor.h"
#include "../../../BaseGame/source/userInterface/IGameView.h"
//#include <gameLogic/BaseGameState.h>
//#include <gameLogic/BaseGameLogic.h>
//#include <debugging/Logger.h>
//#include <actors/Actor.h>

#include <sstream>      // std::stringstream
#include <memory> // shared_ptr
#include <list> // list

using std::shared_ptr;
using std::stringstream;
using std::list;

using base_game::BaseGameLogic;
using base_game::BaseGameState;
using base_game::Actor;
using base_game::BaseGameState::spawningPlayersActors;
using base_game::BaseGameState::running;
using base_game::IGameView;

namespace logger = base_game::logger;

namespace watermill {
WatermillLogic::WatermillLogic() {
	logger::trace("Create WatermillLogic");
}

WatermillLogic::~WatermillLogic() {
	logger::trace("Destroy WatermillLogic");
}

void WatermillLogic::vChangeState(BaseGameState newState) {
	BaseGameLogic::vChangeState(newState);

	stringstream ss;

	switch (newState) {

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

void WatermillLogic::describeYourself() {
	logger::info("WatermillLogic describeYourself");

	list<shared_ptr<IGameView> >::iterator viewsIterator;

	for (viewsIterator = m_gameViews.begin();
			viewsIterator != m_gameViews.end(); ++viewsIterator) {

		shared_ptr<IGameView> currentView = *viewsIterator;
		//(*viewsIterator)->describeYourself();
		//(*viewsIterator)->vOnAttach(1, 1);
		currentView->describeYourself();

	}

}

}

#include "WatermillLogic.h"
#include "../userInterface/MainMenuView.h"
#include "../userInterface/WatermillHumanView.h"

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
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/userInterface/TempT004figuresView.h"
#include "../../../BaseGame/source/userInterface/TempT009jpegGilTextureView.h"
#include "../../../BaseGame/source/userInterface/TempT00FpolishFontsView.h"
#include "../../../BaseGame/source/userInterface/TempT00DpngGilScanlineView.h"
#include "../../../BaseGame/source/userInterface/TempCombinedView.h"

//#include <gameLogic/BaseGameState.h>
//#include <gameLogic/BaseGameLogic.h>
//#include <debugging/Logger.h>
//#include <actors/Actor.h>

#include <sstream>      // std::stringstream
#include <memory> // shared_ptr
#include <list> // list

using std::shared_ptr;
using std::make_shared;
using std::stringstream;
using std::list;

using base_game::BaseGameLogic;
using base_game::BaseGameState;
using base_game::Actor;
using base_game::BaseGameState::spawningPlayersActors;
using base_game::BaseGameState::running;
using base_game::BaseGameState::tempActivateWatermillHumanView;
using base_game::BaseGameState::tempActivateMainMenuView;

using base_game::BaseGameState::tempActivateFiguresView;
using base_game::BaseGameState::tempActivateJpegView;
using base_game::BaseGameState::tempActivateFontsView;
using base_game::BaseGameState::tempActivatePngView;
using base_game::BaseGameState::tempActivateCombinedView;

using base_game::IGameView;
using base_game::OpenGLRenderer;

using base_game::TempT004figuresView;
using base_game::TempT009jpegGilTextureView;
using base_game::TempT00FpolishFontsView;
using base_game::TempT00DpngGilScanlineView;
using base_game::TempCombinedView;



namespace logger = base_game::logger;

namespace watermill {
WatermillLogic::WatermillLogic(shared_ptr<OpenGLRenderer> openGLRenderer) :
		BaseGameLogic(openGLRenderer) {
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

	case tempActivateWatermillHumanView: {
		removeAllViews(); // - breaks the game

		IGameView *watermillHumanView = new WatermillHumanView(openGLRenderer);
		watermillHumanView->tempVLoadGameDelegate();

		shared_ptr<IGameView> pView = shared_ptr<IGameView>(watermillHumanView);
		vAddView(pView);

		break;
	}

	case tempActivateMainMenuView: {
		removeAllViews(); //- breaks the game

		IGameView *mainMenuView = new MainMenuView(openGLRenderer);
		mainMenuView->tempVLoadGameDelegate();

		shared_ptr<IGameView> pView = shared_ptr<IGameView>(mainMenuView);
		vAddView(pView);

		break;
	}
	case tempActivateFiguresView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempT004figuresView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();

		vAddView(pView);

		break;
	}
	case tempActivateJpegView: {
		removeAllViews(); //- breaks the game
		shared_ptr<IGameView> pView = make_shared<TempT009jpegGilTextureView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}
	case tempActivateFontsView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempT00FpolishFontsView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}
	case tempActivatePngView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempT00DpngGilScanlineView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

		break;
	}
	case tempActivateCombinedView: {
		removeAllViews(); //- breaks the game

		shared_ptr<IGameView> pView = make_shared<TempCombinedView>(
				shrdPtrResourceCache,
				openGLRenderer);
		pView->tempVLoadGameDelegate();
		vAddView(pView);

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

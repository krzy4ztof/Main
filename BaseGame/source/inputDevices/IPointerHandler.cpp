/*
 * IPointerHandler.cpp
 *
 *  Created on: 28 gru 2018
 *      Author: Krzysztof
 */

#include "IPointerHandler.h"

#include "../debugging/Logger.h"
#include "../gameInitialization/GameCodeApp.h"//g_pApp
#include "../gameLogic/BaseGameLogic.h"
#include "../userInterface/IGameView.h"

#include <sstream>      // std::stringstream
#include <list> // list
#include <memory> // shared_ptr, weak_ptr

using std::stringstream;
using std::list;
using std::shared_ptr;

namespace base_game {

IPointerHandler::IPointerHandler() {
	logger::info("Create IPointerHandler");

}

IPointerHandler::~IPointerHandler() {
	logger::info("Destroy IPointerHandler");
}

namespace pointer_handler {
void onMouseFunc(int button, int state, int x, int y) {
	stringstream ss;
	ss << "MOUSE: button:" << button << "; state: " << state << "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list < shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnMouseFunc(button, state, x,
					y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

void onMotionFunc(int x, int y) {
	stringstream ss;
	ss << "MOTION: x:" << x << "; y: " << y;
	//logger::info(ss);

	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list < shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnMotionFunc(x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

void onPassiveMotionFunc(int x, int y) {
	stringstream ss;
	ss << "PASSIVE-MOTION: x:" << x << "; y: " << y;
	//logger::info(ss);

	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list < shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnPassiveMotionFunc(x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

void onMouseWheelFunc(int wheel, int direction, int x, int y) {
	stringstream ss;
	ss << "MOUSE: wheel:" << wheel << "; direction: " << direction << "; x: "
			<< x << "; y: " << y;
	//logger::info(ss);

	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list < shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnMouseWheelFunc(wheel,
					direction, x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

}

} /* namespace base_game */

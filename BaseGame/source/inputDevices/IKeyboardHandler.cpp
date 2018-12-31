/*
 * IKeyboardHandler.cpp
 *
 *  Created on: 27 gru 2018
 *      Author: Krzysztof
 */

#include "IKeyboardHandler.h"

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

IKeyboardHandler::IKeyboardHandler() {
	logger::info("Create IKeyboardHandler");
}

IKeyboardHandler::~IKeyboardHandler() {
	logger::info("Destroy IKeyboardHandler");
}

namespace keyboard_handler {
void onKeyboardFunc(unsigned char key, int x, int y) {
	stringstream ss;

	ss << "KEYBOARD: key:" << key << "; x: " << x << "; y: " << y;
//	logger::info(ss);

	if (g_pApp != nullptr) {
		ss << "g_pApp initialized ";
		logger::info(ss);

		BaseGameLogic* baseGame = g_pApp->m_pGame;

		baseGame->describeYourself();


		list<shared_ptr<IGameView> > gameViews = baseGame->getViews();
//		ss << "Views size: " << gameViews.size();
//		logger::info(ss);

		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {

			shared_ptr<IGameView> currentView = *viewsIterator;
			currentView->describeYourself();
			bool funcResult = currentView->vOnKeyboardFunc(key, x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}


	}

}

void onKeyboardFunc_111(unsigned char key, int x, int y) {
	stringstream ss;

	ss << "KEYBOARD: key:" << key << "; x: " << x << "; y: " << y;
	logger::info(ss);

	if (g_pApp != nullptr) {
		ss << "g_pApp initialized ";
		logger::info(ss);

		BaseGameLogic* baseGame = g_pApp->m_pGame;
		// baseGame->describeYourself();

		list<shared_ptr<IGameView> > gameViews = baseGame->getViews();
		ss << "Views size: " << gameViews.size();
		logger::info(ss);

		list<shared_ptr<IGameView> >::iterator viewsIterator;

		for (viewsIterator = gameViews.begin();
				viewsIterator != gameViews.end(); ++viewsIterator) {

			shared_ptr<IGameView> currentView = *viewsIterator;
			currentView->describeYourself();
		}

	}

}

void onKeyboardUpFunc(unsigned char key, int x, int y) {
	stringstream ss;

	ss << "KEYBOARD-UP: key:" << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list<shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnKeyboardUpFunc(key, x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

void onSpecialFunc(int key, int x, int y) {
	stringstream ss;

	ss << "SPECIAL: key:" << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);
	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list<shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnSpecialFunc(key, x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

void onSpecialUpFunc(int key, int x, int y) {
	stringstream ss;

	ss << "SPECIAL-UP: " << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);
	if (g_pApp != nullptr) {
		BaseGameLogic* baseGame = g_pApp->m_pGame;
		list<shared_ptr<IGameView> > gameViews = baseGame->getViews();
		list<shared_ptr<IGameView> >::reverse_iterator viewsIterator;

		for (viewsIterator = gameViews.rbegin();
				viewsIterator != gameViews.rend(); ++viewsIterator) {
			bool funcResult = (*viewsIterator)->vOnSpecialUpFunc(key, x, y);

			if (funcResult) {
				break; // WARNING! This breaks out of the for loop.
			}

		}

	}
}

}

} /* namespace base_game */

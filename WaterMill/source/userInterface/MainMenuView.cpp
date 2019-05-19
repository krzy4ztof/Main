/*
 * MainMenuView.cpp
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#include "MainMenuView.h"
#include "../inputDevices/MainMenuController.h"

#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/userInterface/HumanView.h"

#include <memory> // shared_ptr, weak_ptr, make_shared

namespace logger = base_game::logger;
using base_game::HumanView;

using std::make_shared;
using std::shared_ptr;

namespace watermill {

MainMenuView::MainMenuView() :
		HumanView() {
	logger::info("Create MainMenuView");
}

MainMenuView::~MainMenuView() {
	logger::info("Destroy MainMenuView");
}

void MainMenuView::tempVLoadGameDelegate() {
	shared_ptr<MainMenuController> mainMenuController = make_shared<
			MainMenuController>();
	m_KeyboardHandler = mainMenuController;

}

void MainMenuView::vOnRender(double fTime, float fElapsedTime) {
	//logger::info("vOnRender HumanView");

	//tempOnRenderGLFW(fTime, fElapsedTime);

}

} /* namespace base_game */

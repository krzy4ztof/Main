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
#include "../../../BaseGame/source/userInterface/MainMenuUI.h"

#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"

#include <memory> // shared_ptr, weak_ptr, make_shared

namespace logger = base_game::logger;
using base_game::HumanView;
using base_game::OpenGLRenderer;
using base_game::MainMenuUI;

using std::make_shared;
using std::shared_ptr;

namespace watermill {

MainMenuView::MainMenuView(std::shared_ptr<OpenGLRenderer> openGLRenderer) :
		HumanView(openGLRenderer) {
	logger::info("Create MainMenuView");

	m_MainMenuUI.reset(new MainMenuUI);
	vPushElement(m_MainMenuUI);
}

MainMenuView::~MainMenuView() {
	logger::info("Destroy MainMenuView");
	vTerminate();
	m_MainMenuUI.reset();
}

void MainMenuView::vTerminate() {
	m_MainMenuUI->vTerminate();
}

void MainMenuView::tempVLoadGameDelegate() {
	shared_ptr<MainMenuController> mainMenuController = make_shared<
			MainMenuController>();
	m_KeyboardHandler = mainMenuController;

}

void MainMenuView::tempVRender(double currentTime, float fElapsedTime) {
}

void MainMenuView::vOnRender(double fTime, float fElapsedTime) {
	HumanView::vOnRender(fTime, fElapsedTime);
	//logger::info("MainMenuView::vOnRender");
	//logger::info("vOnRender HumanView");

	//tempOnRenderGLFW(fTime, fElapsedTime);

}

} /* namespace watermill */

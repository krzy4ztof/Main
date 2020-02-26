/*
 * WatermillHumanView.cpp
 *
 *  Created on: 12 sty 2020
 *      Author: Krzysztof
 */

#include "WatermillHumanView.h"
#include "../inputDevices/MainMenuController.h"

#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/userInterface/HumanView.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/userInterface/ScreenElementScene.h"

#include <memory> // shared_ptr, weak_ptr

namespace logger = base_game::logger;
using base_game::HumanView;
using base_game::OpenGLRenderer;
using base_game::ScreenElementScene;

using std::make_shared;
using std::shared_ptr;

namespace watermill {

WatermillHumanView::WatermillHumanView(
		std::shared_ptr<OpenGLRenderer> openGLRenderer) :
		HumanView(openGLRenderer) {
	logger::info("Create WatermillHumanView");
	temp_InitScene();
}


WatermillHumanView::~WatermillHumanView() {
	logger::info("Destroy WatermillHumanView");
	vTerminate();
	m_ScreenElementScene.reset();
}

void WatermillHumanView::vTerminate() {
	m_ScreenElementScene->vTerminate();
}

void WatermillHumanView::temp_InitScene() {

	m_ScreenElementScene.reset(new ScreenElementScene);
	vPushElement(m_ScreenElementScene);
}


void WatermillHumanView::tempVLoadGameDelegate() {
	shared_ptr < MainMenuController > mainMenuController = make_shared<
			MainMenuController>();
	m_KeyboardHandler = mainMenuController;

}

void WatermillHumanView::tempVRender(double currentTime, float fElapsedTime) {
}

void WatermillHumanView::vOnRender(double fTime, float fElapsedTime) {
	HumanView::vOnRender(fTime, fElapsedTime);
	logger::info("WatermillHumanView::vOnRender");
	//logger::info("vOnRender HumanView");

	//tempOnRenderGLFW(fTime, fElapsedTime);

}

} /* namespace watermill */

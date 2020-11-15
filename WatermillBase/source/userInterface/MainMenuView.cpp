/*
 * MainMenuView.cpp
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#include "MainMenuView.h"
#include "MainMenuUI.h"

#include "../inputDevices/MainMenuController.h"

#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/userInterface/HumanView.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h" // g_pApp TODO: to remove
#include "../../../BaseGame/source/userInterface/QuitMessageBoxUI.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

#include <memory> // shared_ptr, weak_ptr, make_shared
#include <sstream>      // std::stringstream



namespace logger = base_game::logger;
using base_game::HumanView;
using base_game::OpenGLRenderer;
//using base_game::MainMenuUI;
using base_game::ResourceCache;
using base_game::QuitMessageBoxUI;
using base_game::GameMessages;

using std::make_shared;
using std::shared_ptr;
using std::stringstream;

namespace watermill_base {

MainMenuView::MainMenuView(shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer,
		shared_ptr<GameMessages> gameMessages) :
		HumanView(openGLRenderer) {
	logger::info("Create MainMenuView");
	//this->shrdPtrResourceCache = resourceCache;
	//m_MainMenuUI.reset(new MainMenuUI(resourceCache, openGLRenderer));
	m_MainMenuUI.reset(new MainMenuUI(openGLRenderer, gameMessages));
	m_MainMenuUI->init();

	vPushElement(m_MainMenuUI);

	initQuitMessageBox(resourceCache, openGLRenderer, gameMessages);

	//tempOpenQuitMessageBox(resourceCache, openGLRenderer);
}

MainMenuView::~MainMenuView() {
	logger::info("Destroy MainMenuView");
	vTerminate();
	m_MainMenuUI.reset();
	m_MessageBoxUI.reset();

	vRemoveElement(m_MessageBoxUI);
	vRemoveElement(m_MainMenuUI);

}

void MainMenuView::vTerminate() {
	//tempCloseQuitMessageBox();
	m_MainMenuUI->vTerminate();
	m_MessageBoxUI->vTerminate();
	/*
	 vRemoveElement(m_MessageBoxUI);
	 m_MessageBoxUI.reset();

	m_MainMenuUI->vTerminate();
	vRemoveElement(m_MainMenuUI);
	m_MainMenuUI.reset();
	 */
	
	//shrdPtrResourceCache.reset();
}

void MainMenuView::tempVLoadGameDelegate() {
	shared_ptr<MainMenuController> mainMenuController = make_shared<
			MainMenuController>();
	m_PointerHandler = mainMenuController;
	m_KeyboardHandler = mainMenuController;


}

void MainMenuView::tempVRender(double currentTime, float fElapsedTime) {
}

void MainMenuView::vOnRender(double fTime, float fElapsedTime) {
	HumanView::vOnRender(fTime, fElapsedTime);

	stringstream ss;
	ss << "MainMenuView::vOnRender /Time: " << fTime << " /Elapsed: "
			<< fElapsedTime;
	logger::info(ss);
	//logger::info("MainMenuView::vOnRender");
	//logger::info("vOnRender HumanView");

	//tempOnRenderGLFW(fTime, fElapsedTime);

}

void MainMenuView::initQuitMessageBox(shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer,
		shared_ptr<GameMessages> gameMessages) {
	m_MessageBoxUI.reset(new QuitMessageBoxUI(openGLRenderer, gameMessages));
	m_MessageBoxUI->setModal(true);
	m_MessageBoxUI->init();

	m_MessageBoxUI->vSetVisible(false);
	vPushElement(m_MessageBoxUI);

	m_MainMenuUI->tempSetQuitMessageBox(m_MessageBoxUI);
	//vPushElement(m_MessageBox);

}


/*
void MainMenuView::openQuitMessageBox() {
	//vPushElement(m_MessageBox);
	m_MessageBox->vSetVisible(true);
}
 */

/*
void MainMenuView::tempCloseQuitMessageBox() {
	//vRemoveElement(m_MessageBox);
	m_MessageBox->vSetVisible(false);
	//m_MessageBox.reset();
}
 */

bool MainMenuView::vOnKeyCallback(GLFWwindow *window, int key, int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "MainMenuView::onKeyCallback: key: " << key << "; scancode: "
			<< scancode
			<< "; action: " << action << "; mods: " << mods;
	// logger::info(ss);

	if (HumanView::vOnKeyCallback(window, key, scancode, action, mods)) {
		return true;
	}

	/*
	if (base_game::g_pApp != nullptr) {
		if (key == GLFW_KEY_Q) {
			openQuitMessageBox();
			return true;
		} else if (key == GLFW_KEY_Y) {
			tempCloseQuitMessageBox();
			return true;
		} else if (key == GLFW_KEY_N) {
			tempCloseQuitMessageBox();
			return true;
		}
	}
	 */

	/*
	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnKeyCallback(window, key, scancode, action, mods);
		return true;
	} else {
		return false;
	}
	 */

	return false;
}

bool MainMenuView::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "MainMenuView::onMouseButtonCallback: button: " << button
			<< "; action: " << action << "; mods: " << mods;
	//logger::info(ss);

	if (HumanView::vOnMouseButtonCallback(window, button, action, mods)) {
		return true;
	}

	/*
	if (m_PointerHandler) {
		m_PointerHandler->vOnMouseButtonCallback(window, button, action, mods);
		return true;
	} else {
		return false;
	}
	 */
}

bool MainMenuView::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "MainMenuView::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
			<< ypos;
	//logger::info(ss);

	if (HumanView::vOnCursorPositionCallback(window, xpos, ypos)) {
		return true;
	}
	/*
	if (m_PointerHandler) {
		m_PointerHandler->vOnCursorPositionCallback(window, xpos, ypos);
		return true;
	} else {
		return false;
	}
	 */
}

} /* namespace watermill */

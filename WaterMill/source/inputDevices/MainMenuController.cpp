/*
 * MainMenuController.cpp
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#include "MainMenuController.h"

#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h" // g_pApp TODO: to remove

#include <GLFW/glfw3.h> // GLFWwindow
#include <sstream>      // std::stringstream

namespace logger = base_game::logger;
// using base_game::HumanView;

using std::stringstream;

namespace watermill {

MainMenuController::MainMenuController() {
	logger::info("Create MainMenuController");

}

MainMenuController::~MainMenuController() {
	logger::info("Destroy MainMenuController");
}

bool MainMenuController::vOnKeyCallback(GLFWwindow* window, int key,
		int scancode, int action, int mods) {
	stringstream ss;
	ss << "MainMenuController::onKeyCallback: key: " << key << "; scancode: "
			<< scancode << "; action: " << action << "; mods: " << mods;
	logger::info(ss);

	if (key == GLFW_KEY_W) {
		ss << "UP ";
	} else if (key == GLFW_KEY_S) {
		ss << "DOWN ";
	} else if (key == GLFW_KEY_A) {
		ss << "LEFT ";
	} else if (key == GLFW_KEY_D) {
		ss << "RIGHT ";
	}

	if (action == GLFW_PRESS) {
		ss << "PRESSED";
	} else if (action == GLFW_REPEAT) {
		ss << "REPEATED";
	} else if (action == GLFW_RELEASE) {
		ss << "RELEASED";
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		tempStartGame();
	}

	if (base_game::g_pApp != nullptr) {
		if (action == GLFW_PRESS) {
			// GLFW_KEY_1 -> TempT004figuresView
			// GLFW_KEY_2 -> TempT009jpegGilTextureView

			base_game::g_pApp->m_pGame->tempSwitchView(key);
		}


		/*
		if (key == GLFW_KEY_1) {
			base_game::g_pApp->m_pGame->tempAddView(1);
		} else if (key == GLFW_KEY_2) {
			base_game::g_pApp->m_pGame->tempAddView(2);
		} else if (key == GLFW_KEY_3) {
			base_game::g_pApp->m_pGame->tempAddView(3);
		} else if (key == GLFW_KEY_4) {
			base_game::g_pApp->m_pGame->tempAddView(4);
		} else if (key == GLFW_KEY_5) {
			base_game::g_pApp->m_pGame->tempAddView(5);
		} else if (key == GLFW_KEY_6) {
			base_game::g_pApp->m_pGame->tempAddView(6);
		} else if (key == GLFW_KEY_7) {
			base_game::g_pApp->m_pGame->tempAddView(7);
		}
		 */
	}

	logger::info(ss);

	return true;
}

void MainMenuController::tempStartGame() {

	if (base_game::g_pApp != nullptr) {
		base_game::g_pApp->m_pGame->tempAddViews();
	}
}

bool MainMenuController::vOnCharCallback(GLFWwindow* window,
		unsigned int codepoint) {
	stringstream ss;
	ss << "MainMenuController::onCharCallback: codepoint: " << codepoint;
	logger::info(ss);

	return true;
}

bool MainMenuController::vOnCharmodsCallback(GLFWwindow* window,
		unsigned int codepoint, int mods) {
	stringstream ss;
	ss << "MainMenuController::onCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	logger::info(ss);

	return true;
}

} /* namespace base_game */

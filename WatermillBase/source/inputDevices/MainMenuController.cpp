/*
 * MainMenuController.cpp
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#include "MainMenuController.h"

//#include "../userInterface/MainMenuView.h"
//#include "../userInterface/WatermillHumanView.h"

#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h" // g_pApp TODO: to remove
#include "../../../BaseGame/source/gameLogic/BaseGameState.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <sstream>      // std::stringstream
#include <memory> // shared_ptr, weak_ptr, make_shared

namespace logger = base_game::logger;
// using base_game::HumanView;
using base_game::BaseGameState::tempActivateWatermillHumanView;
using base_game::BaseGameState::tempActivateMainMenuView;

using base_game::BaseGameState::tempActivateFiguresView;
using base_game::BaseGameState::tempActivateJpegView;
using base_game::BaseGameState::tempActivateFontsView;
using base_game::BaseGameState::tempActivatePngView;
using base_game::BaseGameState::tempActivateCombinedView;

using base_game::BaseGameState::showQuitMsgBox;
using base_game::BaseGameState::confirmQuitMsgBox;
using base_game::BaseGameState::cancelQuitMsgBox;


using std::stringstream;
using std::make_shared;
using std::shared_ptr;

namespace watermill_base {

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



	if (base_game::g_pApp != nullptr) {

		/*
		if (key == GLFW_KEY_R && action == GLFW_PRESS) {
			tempStartGame();
		 } else
		 */
		if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
			tempStartMainMenuView();
			return true;
		} else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
			tempStartWatermillHumanView();
			return true;
		} else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t004_figures_view::getView(reset,
			//		shrdPtrResourceCache, openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateFiguresView);
			return true;
		} else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t009_jpeg_gil_texture_view::getView(reset,
			//		shrdPtrResourceCache, openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateJpegView);
			return true;
		} else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t00f_polish_fonts_view::getView(reset,
			//	shrdPtrResourceCache, openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateFontsView);
			return true;
		} else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t00d_png_gil_scanline_view::getView(reset,
			//		shrdPtrResourceCache, openGLRenderer);

			base_game::g_pApp->m_pGame->vChangeState(tempActivatePngView);
			return true;
		} else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			//gameView = temp_combined_view::getView(reset, shrdPtrResourceCache,
			//	openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateCombinedView);
			return true;

		}

		/*else if (key == GLFW_KEY_ESCAPE) {

		} else if (key == GLFW_KEY_Q) {
			base_game::g_pApp->m_pGame->vChangeState(showQuitMsgBox);
			return true;
		} else if (key == GLFW_KEY_Y) {
			base_game::g_pApp->m_pGame->vChangeState(confirmQuitMsgBox);
			return true;
		} else if (key == GLFW_KEY_N) {
			base_game::g_pApp->m_pGame->vChangeState(cancelQuitMsgBox);
			return true;
		}
		 */
	}

	logger::info(ss);

	return false;
}

bool MainMenuController::vOnCursorPositionCallback(GLFWwindow *window,
		double xpos, double ypos) {
	stringstream ss;
	ss << "MainMenuController::onCursorPositionCallback: xpos: " << xpos
			<< "; ypos: " << ypos;
	//logger::info(ss);

	return true;
}

bool MainMenuController::vOnCursorEnterCallback(GLFWwindow *window,
		int entered) {
	stringstream ss;
	ss << "MainMenuController::onCursorEnterCallback: entered: " << entered;
	logger::info(ss);

	return true;
}

bool MainMenuController::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "MainMenuController::onMouseButtonCallback: button: " << button
			<< "; action: " << action << "; mods: " << mods;
	logger::info(ss);

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		ss << "LEFT MOUSE BUTTON ";
	} else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		ss << "MIDDLE MOUSE BUTTON ";
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		ss << "RIGHT MOUSE BUTTON ";
	} else if (button == GLFW_MOUSE_BUTTON_LAST) {
		ss << "LAST MOUSE BUTTON ";
	}

	if (action == GLFW_PRESS) {
		ss << "PRESSED";
	} else if (action == GLFW_REPEAT) {
		ss << "REPEATED";
	} else if (action == GLFW_RELEASE) {
		ss << "RELEASED";
	}

	logger::info(ss);

	return true;
}

bool MainMenuController::vOnScrollCallback(GLFWwindow *window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "MainMenuController::onScrollCallback: xoffset: " << xoffset
			<< "; yoffset: " << yoffset;
	//logger::info(ss);

	return true;
}


void MainMenuController::tempStartMainMenuView() {
	if (base_game::g_pApp != nullptr) {
		base_game::g_pApp->m_pGame->vChangeState(tempActivateMainMenuView);
	}
}

void MainMenuController::tempStartWatermillHumanView() {
	if (base_game::g_pApp != nullptr) {

		base_game::g_pApp->m_pGame->vChangeState(
				tempActivateWatermillHumanView);
	}
}

/*
void MainMenuController::tempStartGame_del() {
	if (base_game::g_pApp != nullptr) {
		base_game::g_pApp->m_pGame->tempAddViews();
	}
}
 */

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

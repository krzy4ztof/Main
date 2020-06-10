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
		} else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
			tempStartWatermillHumanView();

		} else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t004_figures_view::getView(reset,
			//		shrdPtrResourceCache, openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateFiguresView);
		} else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t009_jpeg_gil_texture_view::getView(reset,
			//		shrdPtrResourceCache, openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateJpegView);
		} else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t00f_polish_fonts_view::getView(reset,
			//	shrdPtrResourceCache, openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateFontsView);
		} else if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
			// tempCurrentView = temp_t004_figures_view::getView(reset);

			//
			//gameView = temp_t00d_png_gil_scanline_view::getView(reset,
			//		shrdPtrResourceCache, openGLRenderer);

			base_game::g_pApp->m_pGame->vChangeState(tempActivatePngView);

		} else if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			//gameView = temp_combined_view::getView(reset, shrdPtrResourceCache,
			//	openGLRenderer);
			base_game::g_pApp->m_pGame->vChangeState(tempActivateCombinedView);


		} else if (key == GLFW_KEY_ESCAPE) {

		}


		/*
		 else if (action == GLFW_PRESS) {
			// GLFW_KEY_1 -> TempT004figuresView
			// GLFW_KEY_2 -> TempT009jpegGilTextureView

			base_game::g_pApp->m_pGame->tempSwitchView(key);
		}
		 */
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

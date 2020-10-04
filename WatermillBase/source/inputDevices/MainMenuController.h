/*
 * MainMenuController.h
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#ifndef SOURCE_INPUTDEVICES_MAINMENUCONTROLLER_H_
#define SOURCE_INPUTDEVICES_MAINMENUCONTROLLER_H_

#include "../../../BaseGame/source/inputDevices/IKeyboardHandler.h"
#include "../../../BaseGame/source/inputDevices/IPointerHandler.h"


#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace watermill_base {

class MainMenuController: public base_game::IKeyboardHandler,
		public base_game::IPointerHandler {
public:
	MainMenuController();
	virtual ~MainMenuController();

	virtual bool vOnKeyCallback(GLFWwindow* window, int key, int scancode,
			int action, int mods);

	virtual bool vOnCharCallback(GLFWwindow* window, unsigned int codepoint);
	virtual bool vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
			int mods);

	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	virtual bool vOnCursorEnterCallback(GLFWwindow *window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);
	virtual bool vOnScrollCallback(GLFWwindow *window, double xoffset,
			double yoffset);

	//void tempStartGame_del();
	void tempStartMainMenuView();
	void tempStartWatermillHumanView();

};

} /* namespace base_game */

#endif /* SOURCE_INPUTDEVICES_MAINMENUCONTROLLER_H_ */

/*
 * TempUI.h
 *
 *  Created on: 14 sie 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_TEMPUI_H_
#define USERINTERFACE_TEMPUI_H_

#include "BaseUI.h"
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {

class TempUI: public BaseUI {
public:
	TempUI();
	virtual ~TempUI();

	virtual bool vOnKeyCallback(GLFWwindow *window, int key, int scancode,
			int action, int mods);
	virtual bool vOnCharCallback(GLFWwindow *window, unsigned int codepoint);
	virtual bool vOnCharmodsCallback(GLFWwindow *window, unsigned int codepoint,
			int mods);

	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	virtual bool vOnCursorEnterCallback(GLFWwindow *window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);
	virtual bool vOnScrollCallback(GLFWwindow *window, double xoffset,
			double yoffset);
};

} /* namespace base_game */

#endif /* USERINTERFACE_TEMPUI_H_ */

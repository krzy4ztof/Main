/*
 * MovementController.h
 *
 *  Created on: 30 gru 2018
 *      Author: Krzysztof
 */

#ifndef INPUTDEVICES_MOVEMENTCONTROLLER_H_
#define INPUTDEVICES_MOVEMENTCONTROLLER_H_

#include "IKeyboardHandler.h"
#include "IPointerHandler.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {

class MovementController: public IKeyboardHandler, public IPointerHandler {
public:
	MovementController();
	virtual ~MovementController();

	/*
	 virtual bool vOnKeyboardFunc(unsigned char key, int x, int y);
	 virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	 virtual bool vOnSpecialFunc(int key, int x, int y);
	 virtual bool vOnSpecialUpFunc(int key, int x, int y);
	 */

	virtual bool vOnMouseFunc(int button, int state, int x, int y);
	virtual bool vOnMotionFunc(int x, int y);
	virtual bool vOnPassiveMotionFunc(int x, int y);
	virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);

	virtual bool vOnKeyCallback(GLFWwindow* window, int key, int scancode,
			int action, int mods);
	virtual bool vOnCharCallback(GLFWwindow* window, unsigned int codepoint);
	virtual bool vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
			int mods);

	virtual bool vOnCursorPositionCallback(GLFWwindow* window, double xpos,
			double ypos);
	virtual bool vOnCursorEnterCallback(GLFWwindow* window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow* window, int button,
			int action, int mods);
	virtual bool vOnScrollCallback(GLFWwindow* window, double xoffset,
			double yoffset);

	void tempStartGame();

protected:
	//m_keys[]
};

} /* namespace base_game */

#endif /* INPUTDEVICES_MOVEMENTCONTROLLER_H_ */

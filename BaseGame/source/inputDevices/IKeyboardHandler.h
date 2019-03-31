/*
 * IKeyboardHandler.h
 *
 *  Created on: 27 gru 2018
 *      Author: Krzysztof
 */

#ifndef INPUTDEVICES_IKEYBOARDHANDLER_H_
#define INPUTDEVICES_IKEYBOARDHANDLER_H_

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {

class IKeyboardHandler {
public:
	IKeyboardHandler();
	virtual ~IKeyboardHandler();

	// 	virtual bool VOnKeyDown(const BYTE c)=0;
	// virtual bool VOnKeyUp(const BYTE c)=0;

	/*
	virtual bool vOnKeyboardFunc(unsigned char key, int x, int y) = 0;
	virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y) = 0;
	virtual bool vOnSpecialFunc(int key, int x, int y) = 0;
	virtual bool vOnSpecialUpFunc(int key, int x, int y) = 0;
	 */

	virtual bool vOnKeyCallback(GLFWwindow* window, int key, int scancode,
			int action, int mods) = 0;
	virtual bool vOnCharCallback(GLFWwindow* window,
			unsigned int codepoint) = 0;
	virtual bool vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
			int mods) = 0;
};

namespace keyboard_handler {
/*
void onKeyboardFunc(unsigned char key, int x, int y);
void onKeyboardFunc_111(unsigned char key, int x, int y);
void onKeyboardUpFunc(unsigned char key, int x, int y);
void onSpecialFunc(int key, int x, int y);
void onSpecialUpFunc(int key, int x, int y);
 */

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action,
		int mods);
void onCharCallback(GLFWwindow* window, unsigned int codepoint);
void onCharmodsCallback(GLFWwindow* window, unsigned int codepoint, int mods);

}

} /* namespace base_game */

#endif /* INPUTDEVICES_IKEYBOARDHANDLER_H_ */

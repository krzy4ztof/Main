#include "IGameView.h"
#include "../debugging/Logger.h"

#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {
IGameView::~IGameView() {
	logger::info("Destroy IGameView");
}

void IGameView::vActivate() {
	active = true;
}

void IGameView::vDeactivate() {
	active = false;
}

bool IGameView::isActive() {
	return active;
}

/*
 bool IGameView::vOnKeyboardFunc(unsigned char key, int x, int y) {
 return false;
 }

 bool IGameView::vOnKeyboardUpFunc(unsigned char key, int x, int y) {
 return false;
 }

 bool IGameView::vOnSpecialFunc(int key, int x, int y) {
 return false;
 }

 bool IGameView::vOnSpecialUpFunc(int key, int x, int y) {
 return false;
 }

 bool IGameView::vOnMouseFunc(int button, int state, int x, int y) {
 return false;
 }

 bool IGameView::vOnMotionFunc(int x, int y) {
 return false;
 }

 bool IGameView::vOnPassiveMotionFunc(int x, int y) {
 return false;
 }

 bool IGameView::vOnMouseWheelFunc(int wheel, int direction, int x, int y) {
 return false;
 }
 */

bool IGameView::vOnKeyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mods) {
	return false;
}

bool IGameView::vOnCharCallback(GLFWwindow* window, unsigned int codepoint) {
	return false;
}

bool IGameView::vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
		int mods) {
	return false;
}

bool IGameView::vOnCursorPositionCallback(GLFWwindow* window, double xpos,
		double ypos) {
	return false;
}

bool IGameView::vOnCursorEnterCallback(GLFWwindow* window, int entered) {
	return false;
}

bool IGameView::vOnMouseButtonCallback(GLFWwindow* window, int button,
		int action, int mods) {
	return false;
}

bool IGameView::vOnScrollCallback(GLFWwindow* window, double xoffset,
		double yoffset) {
	return false;
}

}

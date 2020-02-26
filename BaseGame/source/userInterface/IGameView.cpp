#include "IGameView.h"
#include "../debugging/Logger.h"

#include <GLFW/glfw3.h> // GLFWwindow

namespace base_game {
IGameView::~IGameView() {
	logger::info("Destroy IGameView");
}

/*
void IGameView::vActivate() {
	active = true;
}

void IGameView::vDeactivate() {
	active = false;
}

bool IGameView::isActive() {
	return active;
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

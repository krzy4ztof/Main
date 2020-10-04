/*
 * TempUI.cpp
 *
 *  Created on: 14 sie 2020
 *      Author: Krzysztof
 */

#include "TempUI.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

#include <sstream>      // std::stringstream
using std::stringstream;

namespace base_game {

TempUI::TempUI() {
	// TODO Auto-generated constructor stub

}

TempUI::~TempUI() {
	// TODO Auto-generated destructor stub
}

bool TempUI::vOnKeyCallback(GLFWwindow *window, int key, int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "TempUI::vOnKeyCallback: key: " << key << "; scancode: " << scancode
			<< "; action:" << action << "; mods:" << mods;
	//logger::info(ss);
	return false;
}

bool TempUI::vOnCharCallback(GLFWwindow *window, unsigned int codepoint) {
	stringstream ss;
	ss << "TempUI::vOnCharCallback: codepoint: " << codepoint;
	//logger::info(ss);
	return false;
}

bool TempUI::vOnCharmodsCallback(GLFWwindow *window, unsigned int codepoint,
		int mods) {
	stringstream ss;
	ss << "TempUI::vOnCharmodsCallback: codepoint: " << codepoint << "; mods: "
			<< mods;
	//logger::info(ss);
	return false;
}

bool TempUI::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	return false;
}

bool TempUI::vOnCursorEnterCallback(GLFWwindow *window, int entered) {
	return false;
}

bool TempUI::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	return false;
}

bool TempUI::vOnScrollCallback(GLFWwindow *window, double xoffset,
		double yoffset) {
	return false;
}

} /* namespace base_game */

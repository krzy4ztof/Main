/*
 * ScreenElementScene.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#include "ScreenElementScene.h"
#include "../debugging/Logger.h"

#include <sstream>      // std::stringstream
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow

using std::stringstream;

namespace base_game {

ScreenElementScene::ScreenElementScene() {
	logger::info("Create ScreenElementScene");

}

ScreenElementScene::~ScreenElementScene() {
	logger::info("Destroy ScreenElementScene");
}

void ScreenElementScene::vTerminate() {

}

int ScreenElementScene::vGetZOrder() const {
	return 0;
}

void ScreenElementScene::vSetZOrder(int const zOrder) const {
}

bool ScreenElementScene::vIsVisible() const {
	return true;
}
void ScreenElementScene::vSetVisible(bool visible) {
}

void ScreenElementScene::vOnRestore() {
	// TODO: implement
}

void ScreenElementScene::vOnRender(double fTime, float fElapsedTime) {
// TODO: implement
}

void ScreenElementScene::vOnUpdate(int deltaMS) {
//	OnUpdate(deltaMS);
}

bool ScreenElementScene::vOnKeyCallback(GLFWwindow *window, int key,
		int scancode, int action, int mods) {
	stringstream ss;
	ss << "ScreenElementScene::vOnKeyCallback: key: " << key << "; scancode: "
			<< scancode << "; action:" << action << "; mods:" << mods;
	//logger::info(ss);
	return false;
}

bool ScreenElementScene::vOnCharCallback(GLFWwindow *window,
		unsigned int codepoint) {
	stringstream ss;
	ss << "ScreenElementScene::vOnCharCallback: codepoint: " << codepoint;
	//logger::info(ss);
	return false;
}

bool ScreenElementScene::vOnCharmodsCallback(GLFWwindow *window,
		unsigned int codepoint, int mods) {
	stringstream ss;
	ss << "ScreenElementScene::vOnCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	//logger::info(ss);
	return false;
}

bool ScreenElementScene::vOnCursorPositionCallback(GLFWwindow *window,
		double xpos,
		double ypos) {
	stringstream ss;
	ss << "ScreenElementScene::onCursorPositionCallback: xpos: " << xpos
			<< "; ypos: "
			<< ypos;
	//logger::info(ss);
	return false;
}

bool ScreenElementScene::vOnCursorEnterCallback(GLFWwindow *window,
		int entered) {
	stringstream ss;
	ss << "ScreenElementScene::onCursorEnterCallback: entered: " << entered;
	return false;
}

bool ScreenElementScene::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "ScreenElementScene::onMouseButtonCallback: button: " << button
			<< "; action: " << action << "; mods: " << mods;
	logger::info(ss);
	return false;
}

bool ScreenElementScene::vOnScrollCallback(GLFWwindow *window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "ScreenElementScene::onScrollCallback: xoffset: " << xoffset
			<< "; yoffset: "
			<< yoffset;
	return false;
}


} /* namespace base_game */

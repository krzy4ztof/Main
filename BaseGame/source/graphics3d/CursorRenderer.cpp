/*
 * CursorRenderer.cpp
 *
 *  Created on: 22 wrz 2020
 *      Author: Krzysztof
 */

#include "CursorRenderer.h"
#include "../debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>

#include <memory> // shared_ptr

using std::make_shared;

namespace base_game {

//CursorRenderer::CursorRenderer(shared_ptr<GLFWwindow> window) {
CursorRenderer::CursorRenderer() {
	logger::info("Create CursorRenderer");
}

CursorRenderer::~CursorRenderer() {
	logger::info("Destroy CursorRenderer");
	glfwSetCursor(window, NULL);
	glfwDestroyCursor(handCursor);
	//handCursor.reset();
	//window.reset();
}

void CursorRenderer::init(GLFWwindow *window) {
	this->window = window;
	handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
	//glfwSetCursor(window, handCursor);
}

void CursorRenderer::activateHandCursor() {
	glfwSetCursor(window, handCursor);
	logger::info("CursorRenderer::activateHandCursor()");
}

void CursorRenderer::activateArrowCursor() {
	glfwSetCursor(window, NULL);
	logger::info("CursorRenderer::activateArrowCursor()");
}

} /* namespace base_game */

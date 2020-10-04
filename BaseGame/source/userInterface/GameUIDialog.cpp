/*
 * GameUIDialog.cpp
 *
 *  Created on: 27 lip 2020
 *      Author: Krzysztof
 */

#include "GameUIDialog.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "GameUIPane.h"
#include "../debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLFWwindow

#include <memory> // shared_ptr
#include <sstream>      // std::stringstream
#include <glm/glm.hpp> // glm::ivec2, glm:mat4

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;

namespace base_game {

GameUIDialog::GameUIDialog(shared_ptr<OpenGLRenderer> openGLRenderer) :
		x(0.0f), y(0.0f), width(1.0f), height(1.0f), borderWidth(0.0f), backgroundColor(
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)), borderColor(
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)) {
	logger::info("Create GameUIDialog");
	this->openGLRenderer = openGLRenderer;
}

GameUIDialog::~GameUIDialog() {
	gameUIPane.reset();
	openGLRenderer.reset();
}

void GameUIDialog::onRender(double fTime, float fElapsedTime) {
	renderDialog(fTime, fElapsedTime);
	renderPane(fTime, fElapsedTime);
}

void GameUIDialog::renderDialog(double fTime, float fElapsedTime) {
	openGLRenderer->figuresRenderer->activate(projection);

	// gameUIDialog->setPosition((11 + 0.5) * rem, (16 + 0.5) * rem);

	// glm::vec4 backgroundColor2 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	// body
	openGLRenderer->figuresRenderer->renderRectangle(glm::vec2(x, y),
			glm::vec2(x + width, y + height), backgroundColor);

	if (borderWidth > 0.0f) {
	// top
//	openGLRenderer->figuresRenderer->renderRectangle(
//			glm::vec2(11 * rem, (16 + 16 - 0.5) * rem),
//			glm::vec2((11 + 42) * rem, (16 + 16) * rem), darkseagreen);
		openGLRenderer->figuresRenderer->renderRectangle(
				glm::vec2(x, y + height),
			glm::vec2(x + width, y + height + borderWidth), borderColor);

	// bottom
//	openGLRenderer->figuresRenderer->renderRectangle(
//			glm::vec2(11 * rem, 16 * rem),
//			glm::vec2((11 + 42) * rem, (16 + 0.5) * rem), darkseagreen);
		openGLRenderer->figuresRenderer->renderRectangle(glm::vec2(x, y),
			glm::vec2(x + width, y - borderWidth), borderColor);


	// glm::vec4 borderColor2 = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	// left
//	openGLRenderer->figuresRenderer->renderRectangle(
//			glm::vec2(11 * rem, (16 + 0.5) * rem),
//			glm::vec2((11 + 0.5) * rem, (16 + 16 - 0.5) * rem), darkseagreen);
		openGLRenderer->figuresRenderer->renderRectangle(
				glm::vec2(x - borderWidth, y - borderWidth),
				glm::vec2(x, y + height + borderWidth), borderColor);

	// right
//	openGLRenderer->figuresRenderer->renderRectangle(
//			glm::vec2((11 + 42) * rem, (16 + 0.5) * rem),
//			glm::vec2((11 + 42 - 0.5) * rem, (16 + 16 - 0.5) * rem),
//			darkseagreen);

		openGLRenderer->figuresRenderer->renderRectangle(
				glm::vec2(x + width + borderWidth, y - borderWidth),
				glm::vec2(x + width, y + height + borderWidth), borderColor);
	}
	
	openGLRenderer->figuresRenderer->deactivate();

}

void GameUIDialog::renderPane(double fTime, float fElapsedTime) {
	gameUIPane->onRender(fTime, fElapsedTime);
}

void GameUIDialog::addPane(shared_ptr<GameUIPane> gameUIPane) {
	gameUIPane->setOffset(x, y);
	this->gameUIPane = gameUIPane;
}

void GameUIDialog::setProjection(glm::mat4 projection) {
	this->projection = projection;
}

void GameUIDialog::setPosition(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;

	if (gameUIPane) {
		gameUIPane->setOffset(x, y);
	}
}

void GameUIDialog::setSize(GLfloat width, GLfloat height) {
	this->width = width;
	this->height = height;
}

void GameUIDialog::setBackgroundColor(glm::vec4 color) {
	backgroundColor = color;
}

void GameUIDialog::setBorderColor(glm::vec4 color) {
	borderColor = color;
}

void GameUIDialog::setBorderWidth(GLfloat width) {
	borderWidth = width;
}

bool GameUIDialog::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "GameUIDialog::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
			<< ypos;
	//logger::info(ss);

	if (gameUIPane->vOnCursorPositionCallback(window, xpos, ypos)) {
		return true;
	}

	return false;
}

bool GameUIDialog::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "GameUIDialog::onMouseButtonCallback: button: " << button
			<< "; action: " << action << "; mods: " << mods;
	logger::info(ss);
	if (gameUIPane->vOnMouseButtonCallback(window, button, action, mods)) {
		return true;
	}

	return false;
}

} /* namespace base_game */

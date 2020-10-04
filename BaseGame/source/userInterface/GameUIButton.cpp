/*
 * GameUIButton.cpp
 *
 *  Created on: 21 lip 2020
 *      Author: Krzysztof
 */

#include "GameUIButton.h"
#include "../debugging/Logger.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/FiguresRenderer.h"
#include "GameUILabel.h"

#include <string> // std::string
#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <memory> // shared_ptr
#include <sstream>      // std::stringstream

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;


namespace base_game {

GameUIButton::GameUIButton(shared_ptr<OpenGLRenderer> openGLRenderer,
		string text) :
		x(0.0f), y(0.0f), width(1.0f), height(1.0f), offsetX(0.0f), offsetY(
				0.0f), color(
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)), mouseOverColor(
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)), mouseOver(false) {
	logger::info("Create GameUIButton");
	this->figuresRenderer = openGLRenderer->figuresRenderer;

	gameUILabel = make_shared<GameUILabel>(openGLRenderer, text);
}

GameUIButton::~GameUIButton() {
	logger::info("Destroy GameUIButton");

	gameUILabel.reset();
	figuresRenderer.reset();
}

/*
void GameUIButton::vOnRestore() {

}

void GameUIButton::onRenderLabel(double fTime, float fElapsedTime) {
	onRenderLabel(fTime, fElapsedTime, 0.0f, 0.0f);
}
 */

void GameUIButton::onRenderLabel(double fTime, float fElapsedTime) {
	gameUILabel->onRender(fTime, fElapsedTime);
}

//void GameUIButton::onRenderBox(double fTime, float fElapsedTime) {
//	onRenderBox(fTime, fElapsedTime, 0.0f, 0.0f);
//}

void GameUIButton::onRenderBox(double fTime, float fElapsedTime) {
	//
	//openGLRenderer->figuresRenderer->renderRectangle(
	//		glm::vec2((6 + 12 + 8) * rem, 3 * rem),
	//		glm::vec2((6 + 12 + 8 + 12) * rem, (3 + 3) * rem), darkseagreen);

	//this->offsetX = offsetXparam;
	//this->offsetY = offsetYparam;
	glm::vec4 currentColor = color;
	
	if (mouseOver) {
		currentColor = mouseOverColor;
	}


	figuresRenderer->renderRectangle(glm::vec2(offsetX + x, offsetY + y),
			glm::vec2(offsetX + x + width, offsetY + y + height), currentColor);

}

void GameUIButton::setPosition(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
	gameUILabel->setPosition(x, y);
//	initLabelOffset();
}

void GameUIButton::setSize(GLfloat width, GLfloat height) {
	this->width = width;
	this->height = height;
//	initLabelOffset();
	gameUILabel->setSize(width, height);
}

void GameUIButton::setColor(glm::vec4 color) {
	this->color = color;
}

void GameUIButton::setMouseOverColor(glm::vec4 color) {
	this->mouseOverColor = color;
}

/*
void GameUIButton::setLabelOffset(GLfloat x, GLfloat y) {
	gameUILabel->setPosition(this->x + x, this->y + y);
}
 */

void GameUIButton::end() {
	gameUILabel->end();
//	initLabelOffset();
}

/*
void GameUIButton::initLabelOffset() {
	glm::vec2 textSize = gameUILabel->getTextSize();
	stringstream ss;
	GLfloat posX = (width - textSize.x) / 2.0f;
	GLfloat posY = (height - textSize.y) / 2.0f;

	//gameUILabel->setPosition(offsetX + x + posX, offsetY + y + posY);
	gameUILabel->setPosition(x + posX, y + posY);
}
 */

void GameUIButton::setLabelScale(GLfloat scale) {
	gameUILabel->setScale(scale);
//	initLabelOffset();
}

bool GameUIButton::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	stringstream ss;
	//logger::info(ss);

//	if (gameUIPane->vOnCursorPositionCallback(window, xpos, ypos)) {
//		return true;
//	}

	if (xpos >= offsetX + x && xpos <= offsetX + x + width
			&& ypos >= offsetY + y && ypos <= offsetY + y + height) {

		/*
		ss << "GameUIButton::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
		<< ypos << "; offsetX + x:" << offsetX + x
				<< "; offsetX + x + width:" << offsetX + x + width
				<< "; offsetY + y:" << offsetY + y << "; offsetY + y + height:"
				<< offsetY + y + height;
		 logger::info(ss);
		 */
		
		if (!mouseOver) {
			ss << "change cursor to hand";
			logger::info(ss);
			if (*callbackCursorFunction) {
				// callbackFunction((void*) &callbackObject);
				callbackCursorFunction(callbackCursorObject, true);
			}
		}
		this->mouseOver = true;
	} else {
		if (mouseOver) {
			ss << "change cursor to pointer";
			logger::info(ss);

			if (*callbackCursorFunction) {
				// callbackFunction((void*) &callbackObject);
				callbackCursorFunction(callbackCursorObject, false);
			}
		}
		this->mouseOver = false;
	}

	return false;
}

bool GameUIButton::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "GameUIButton::onMouseButtonCallback: button: " << button
			<< "; action: " << action << "; mods: " << mods;
	logger::info(ss);
	// button: 0 - left, 1 - right
	// action: 0 - released, 1 - clicked
	// if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	// The action is one of GLFW_PRESS or GLFW_RELEASE.

//	if (gameUIPane->vOnMouseButtonCallback(window, button, action, mods)) {
//		return true;
//	}

	//TeapotWars GameCode.cpp
	//
	//LRESULT CALLBACK GameCodeApp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
	//
	// GameCode.h
	// static LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void *pUserContext );
	//
	// http://www.newty.de/fpt/callback.html#member


	if (mouseOver && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		ss << "button [" << gameUILabel->getText() << "] is clicked";
		logger::info(ss);

		if (*callbackFunction) {
			// callbackFunction((void*) &callbackObject);
			callbackFunction(callbackObject);
			this->mouseOver = false;
		}
	}

	return false;
}


void GameUIButton::setCallback(void (*callbackFunction)(void *callbackObject),
		void *callbackObject) {

	this->callbackFunction = callbackFunction;
	this->callbackObject = callbackObject;
}

void GameUIButton::setCursorCallback(
		void (*callbackCursorFunction)(void *callbackCursorObject,
				boolean cursorOverButton),
		void *callbackCursorObject) {

	this->callbackCursorFunction = callbackCursorFunction;
	this->callbackCursorObject = callbackCursorObject;
}

void GameUIButton::setOffset(GLfloat x, GLfloat y) {
	this->offsetX = x;
	this->offsetY = y;

	gameUILabel->setOffset(x, y);
	//initLabelOffset();
}

} /* namespace base_game */

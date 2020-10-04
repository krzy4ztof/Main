/*
 * GameUIFrame.cpp
 *
 *  Created on: 19 lip 2020
 *      Author: Krzysztof
 */

#include "GameUIPane.h"
#include "../debugging/Logger.h"
#include "GameUILabel.h"
#include "GameUIButton.h"
#include "GameUIPngImage.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLFWwindow

#include <memory> // shared_ptr
#include <list> // list
#include <sstream>      // std::stringstream

using std::stringstream;
using std::shared_ptr;
using std::list;


namespace base_game {

GameUIPane::GameUIPane(shared_ptr<OpenGLRenderer> openGLRenderer) :
		offsetX(0.0f), offsetY(0.0f) {
	logger::info("Create GameUIPane");
	this->openGLRenderer = openGLRenderer;
}

GameUIPane::~GameUIPane() {
	logger::info("Destroy GameUIPane");
	gameUIPngImages.clear();
	gameUILabels.clear();
	gameUIButtons.clear();
	openGLRenderer.reset();
}

void GameUIPane::setProjection(glm::mat4 projection) {
	this->projection = projection;
}

void GameUIPane::addLabel(shared_ptr<GameUILabel> gameUILabel) {
	gameUILabel->setOffset(offsetX, offsetY);
	gameUILabels.push_back(gameUILabel);
}

void GameUIPane::addButton(shared_ptr<GameUIButton> gameUIButton) {
	gameUIButton->setOffset(offsetX, offsetY);
	gameUIButtons.push_back(gameUIButton);
}

void GameUIPane::addPngImage(shared_ptr<GameUIPngImage> gameUIPngImage) {
	gameUIPngImage->setOffset(offsetX, offsetY);
	gameUIPngImages.push_back(gameUIPngImage);
}

void GameUIPane::onRender(double fTime, float fElapsedTime) {
	renderPngImages(fTime, fElapsedTime);
	renderButtons(fTime, fElapsedTime);
	renderLabels(fTime, fElapsedTime);
}

void GameUIPane::renderLabels(double fTime, float fElapsedTime) {
	if (gameUILabels.empty() && gameUIButtons.empty()) {
		return;
	}

	openGLRenderer->freeTypeRenderer->activate(projection);
	openGLRenderer->freeTypeRenderer->startRender();


	list<shared_ptr<GameUILabel> >::iterator labelsIterator;

	for (labelsIterator = gameUILabels.begin();
			labelsIterator != gameUILabels.end(); labelsIterator++) {
		(*labelsIterator)->onRender(fTime, fElapsedTime);
	}

	if (!gameUIButtons.empty()) {
		list<shared_ptr<GameUIButton> >::iterator buttonsIterator;

		for (buttonsIterator = gameUIButtons.begin();
				buttonsIterator != gameUIButtons.end(); buttonsIterator++) {
			(*buttonsIterator)->onRenderLabel(fTime, fElapsedTime);
		}
	}
	openGLRenderer->freeTypeRenderer->deactivate();
}

void GameUIPane::renderButtons(double fTime, float fElapsedTime) {
	if (gameUIButtons.empty()) {
		return;
	}
	openGLRenderer->figuresRenderer->activate(projection);

	list<shared_ptr<GameUIButton> >::iterator buttonsIterator;

	for (buttonsIterator = gameUIButtons.begin();
			buttonsIterator != gameUIButtons.end(); buttonsIterator++) {
		(*buttonsIterator)->onRenderBox(fTime, fElapsedTime);
	}

	openGLRenderer->figuresRenderer->deactivate();

}

void GameUIPane::renderPngImages(double fTime, float fElapsedTime) {

	if (gameUIPngImages.empty()) {
		return;
	}

	openGLRenderer->pngRenderer->activate(projection);
	list<shared_ptr<GameUIPngImage> >::iterator pngImagesIterator;

	for (pngImagesIterator = gameUIPngImages.begin();
			pngImagesIterator != gameUIPngImages.end(); pngImagesIterator++) {
		(*pngImagesIterator)->onRender(fTime, fElapsedTime);
	}

	openGLRenderer->pngRenderer->deactivate();

}

bool GameUIPane::vOnCursorPositionCallback(GLFWwindow *window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "GameUIPane::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
			<< ypos;
	//logger::info(ss);

//	if (gameUIPane->vOnCursorPositionCallback(window, xpos, ypos)) {
//		return true;
//	}

	if (!gameUIButtons.empty()) {
		list<shared_ptr<GameUIButton> >::iterator buttonsIterator;

		for (buttonsIterator = gameUIButtons.begin();
				buttonsIterator != gameUIButtons.end(); buttonsIterator++) {
			(*buttonsIterator)->vOnCursorPositionCallback(window, xpos, ypos);
		}
	}

	return false;
}

bool GameUIPane::vOnMouseButtonCallback(GLFWwindow *window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "GameUIPane::onMouseButtonCallback: button: " << button
			<< "; action: " << action << "; mods: " << mods;
	logger::info(ss);

	if (!gameUIButtons.empty()) {
		list<shared_ptr<GameUIButton> >::iterator buttonsIterator;

		for (buttonsIterator = gameUIButtons.begin();
				buttonsIterator != gameUIButtons.end(); buttonsIterator++) {
			if ((*buttonsIterator)->vOnMouseButtonCallback(window, button,
					action, mods)) {
				return true;
			}
		}
	}
//	if (gameUIPane->vOnMouseButtonCallback(window, button, action, mods)) {
//		return true;
//	}

	return false;
}

void GameUIPane::setOffset(GLfloat x, GLfloat y) {
	this->offsetX = x;
	this->offsetY = y;

	setLabelsOffset(x, y);
	setButtonsOffset(x, y);
	setPngImagesOffset(x, y);
}

void GameUIPane::setLabelsOffset(GLfloat offsetX, GLfloat offsetY) {
	if (gameUILabels.empty()) {
		return;
	}

	list<shared_ptr<GameUILabel> >::iterator labelsIterator;

	for (labelsIterator = gameUILabels.begin();
			labelsIterator != gameUILabels.end(); labelsIterator++) {
		(*labelsIterator)->setOffset(offsetX, offsetY);
	}
}

void GameUIPane::setButtonsOffset(GLfloat offsetX, GLfloat offsetY) {
	if (gameUIButtons.empty()) {
		return;
	}

	list<shared_ptr<GameUIButton> >::iterator buttonsIterator;

	for (buttonsIterator = gameUIButtons.begin();
			buttonsIterator != gameUIButtons.end(); buttonsIterator++) {
		(*buttonsIterator)->setOffset(offsetX, offsetY);
	}
}

void GameUIPane::setPngImagesOffset(GLfloat offsetX, GLfloat offsetY) {

	if (gameUIPngImages.empty()) {
		return;
	}

	list<shared_ptr<GameUIPngImage> >::iterator pngImagesIterator;

	for (pngImagesIterator = gameUIPngImages.begin();
			pngImagesIterator != gameUIPngImages.end(); pngImagesIterator++) {
		(*pngImagesIterator)->setOffset(offsetX, offsetY);
	}

}


} /* namespace base_game */

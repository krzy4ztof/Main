/*
 * GameUILabel.cpp
 *
 *  Created on: 19 lip 2020
 *      Author: Krzysztof
 */

#include "GameUILabel.h"
#include "../debugging/Logger.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/FreeTypeRenderer.h"


#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <string> // std::string
#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <memory> // shared_ptr


using std::string;
using std::shared_ptr;

namespace base_game {

GameUILabel::GameUILabel(shared_ptr<OpenGLRenderer> openGLRenderer,
		string text) :
		x(0.0f), y(0.0f), scale(1.0f), color(glm::vec3(0.0, 0.0f, 0.0f)) {
	logger::info("Create GameUILabel");
	this->freeTypeRenderer = openGLRenderer->freeTypeRenderer;
	this->text = text;
}

GameUILabel::~GameUILabel() {
	logger::info("Destroy GameUILabel");
	freeTypeRenderer.reset();
}

//void GameUILabel::onRender(double fTime, float fElapsedTime) {
//	onRender(fTime, fElapsedTime, 0.0f, 0.0f);
//}

void GameUILabel::onRender(double fTime, float fElapsedTime) {
	//freeTypeRenderer->renderText(text, offsetX + x, offsetY + y, scale, color);
	freeTypeRenderer->renderText(text, offsetX + textX, offsetY + textY, scale,
			color);
}

void GameUILabel::setPosition(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

void GameUILabel::setSize(GLfloat width, GLfloat height) {
	this->width = width;
	this->height = height;
}

void GameUILabel::setScale(GLfloat scale) {
	this->scale = scale;
}

void GameUILabel::end() {
	glm::vec2 textSize = freeTypeRenderer->getTextSize(text, scale);
	//stringstream ss;
	GLfloat posX = (width - textSize.x) / 2.0f;
	GLfloat posY = (height - textSize.y) / 2.0f;

	//gameUILabel->setPosition(offsetX + x + posX, offsetY + y + posY);
	setTextPosition(x + posX, y + posY);
}

void GameUILabel::setTextPosition(GLfloat textX, GLfloat textY) {
	this->textX = textX;
	this->textY = textY;
}


/*
void GameUILabel::initTextPosition(GLfloat scale) {
	this->scale = scale;
}
 */

string GameUILabel::getText() {
	return text;
}

glm::vec2 GameUILabel::getTextSize() {
	glm::vec2 textSize = freeTypeRenderer->getTextSize(text, scale);
	return textSize;
}

void GameUILabel::setOffset(GLfloat x, GLfloat y) {
	this->offsetX = x;
	this->offsetY = y;
}

} /* namespace base_game */

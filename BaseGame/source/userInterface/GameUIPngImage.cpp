/*
 * GameUIPngImage.cpp
 *
 *  Created on: 23 lip 2020
 *      Author: Krzysztof
 */

#include "GameUIPngImage.h"
#include "../debugging/Logger.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/SpriteSheet.h"
#include "../graphics3d/TextureRenderer.h"
#include "../graphics3d/TextureResourceLoader.h"

#include "GameUILabel.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <string> // std::string
#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <memory> // shared_ptr

using std::string;
using std::shared_ptr;
using std::make_shared;

namespace base_game {

GameUIPngImage::GameUIPngImage(shared_ptr<OpenGLRenderer> openGLRenderer,
		string filename) {
	logger::info("Create GameUIPngImage");

	this->pngRenderer = openGLRenderer->pngRenderer;
	this->pngTextureLoader = openGLRenderer->pngTextureLoader;
	spriteSheet = make_shared<SpriteSheet>();
	pngTextureLoader->init(filename, spriteSheet);

}

GameUIPngImage::~GameUIPngImage() {
	logger::info("Destroy GameUIPngImage");
	pngTextureLoader.reset();
	spriteSheet.reset();
	pngTextureLoader.reset();
	pngRenderer.reset();

}

/*
void GameUIPngImage::vOnRestore() {

}
 */

//void GameUIPngImage::onRender(double fTime, float fElapsedTime) {
//	onRender(fTime, fElapsedTime, 0.0f, 0.0f);
//}

void GameUIPngImage::onRender(double fTime, float fElapsedTime) {
	//pngRenderer->activate(projection);
	pngTextureLoader->activate(spriteSheet);

	//pngRenderer->renderRectangle(glm::vec2(20 * rem, 14 * rem),
	//		glm::vec2((20 + 24) * rem, (14 + 24) * rem), spriteSheetLogo, 0, 0);

	pngRenderer->renderRectangle(glm::vec2(offsetX + x, offsetY + y),
			glm::vec2(offsetX + x + width, offsetY + y + height), spriteSheet,
			0, 0);
	
	pngTextureLoader->deactivate();
	//pngRenderer->deactivate();
}

void GameUIPngImage::setPosition(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

void GameUIPngImage::setSize(GLfloat width, GLfloat height) {
	this->width = width;
	this->height = height;
}

void GameUIPngImage::setOffset(GLfloat x, GLfloat y) {
	this->offsetX = x;
	this->offsetY = y;
}

} /* namespace base_game */

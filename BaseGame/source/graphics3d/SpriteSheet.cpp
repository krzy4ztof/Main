/*
 * SpriteSheet.cpp
 *
 *  Created on: 2 sty 2020
 *      Author: Krzysztof
 */

#include "SpriteSheet.h"
#include "../debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <sstream> // std::stringbuf, std::stringstream
#include <glm/glm.hpp> // glm::ivec2, glm:mat4

using glm::vec2;

namespace base_game {

//SpriteSheet::SpriteSheet(int width, int height) :
//		width(width), height(height), margin(0), columns(1), rows(1), spriteWidth(
//				width), spriteHeight(height) {
SpriteSheet::SpriteSheet() :
		height(0), width(0),
		margin(0), columns(1), rows(1) {
	logger::info("Create SpriteSheet");
	glGenTextures(1, &texture);
}

SpriteSheet::~SpriteSheet() {
	logger::info("Destroy SpriteSheet");
	glDeleteTextures(1, &texture);
	delete[] data;
}

void SpriteSheet::setMargin(int margin) {
	this->margin = margin;
	recalculateSpriteHeight();
	recalculateSpriteWidth();
}

void SpriteSheet::setColumns(int columns) {
	this->columns = columns;
	recalculateSpriteWidth();
}

void SpriteSheet::setRows(int rows) {
	this->rows = rows;
	recalculateSpriteHeight();
}

void SpriteSheet::setWidth(int width) {
	this->width = width;
	recalculateSpriteWidth();
}

void SpriteSheet::setHeight(int height) {
	this->height = height;
	recalculateSpriteHeight();
}

void SpriteSheet::recalculateSpriteHeight() {
	spriteHeight = (height - margin * (1 + rows)) / rows;
}

void SpriteSheet::recalculateSpriteWidth() {
	spriteWidth = (width - margin * (1 + columns)) / columns;
}

glm::vec2 SpriteSheet::getZeroPoint(int row, int col) {
	// rectangle
	// 1-3
	// | |
	// 0-2

	// (rows-1, 0)
	// ...
	// (1,0) (1,1) (1,2)
	// (0,0) (0,1) (0,2) ... (0, columns-1)
	//
	// (row,col)

	float x = (margin + spriteWidth) * col + margin;
	float y = (margin + spriteHeight) * row + margin;

	float xf = x / width;
	float yf = y / height;

	vec2 result = vec2(xf, yf);

	return result;
}

glm::vec2 SpriteSheet::getThrdPoint(int row, int col) {
	// rectangle
	// 1-3
	// | |
	// 0-2
	float x = (margin + spriteWidth) * (col + 1);
	float y = (margin + spriteHeight) * (row + 1);

	float xf = x / width;
	float yf = y / height;

	vec2 result = vec2(xf, yf);

	return result;
}


} /* namespace base_game */

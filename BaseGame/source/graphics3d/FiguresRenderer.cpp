/*
 * FiguresRenderer.cpp
 *
 *  Created on: 24 lis 2019
 *      Author: Krzysztof
 */

#include "FiguresRenderer.h"
#include "../debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

namespace base_game {

FiguresRenderer::FiguresRenderer() {
	logger::info("Create FiguresRenderer");
	programID = 0;
	positionBuffer = 0;
	colorBuffer = 0;

}

FiguresRenderer::~FiguresRenderer() {
	logger::info("Destroy FiguresRenderer");
	this->terminate();
}

void FiguresRenderer::terminate() {
	glDeleteProgram(programID);
}

void FiguresRenderer::init(GLuint programID) {
	glGenBuffers(1, &positionBuffer);
	glGenBuffers(1, &colorBuffer);

	this->programID = programID;
}

void FiguresRenderer::activate(glm::mat4 projection) {
	glUseProgram(programID);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1,
	GL_FALSE, glm::value_ptr(projection));
}

void FiguresRenderer::deactivate() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}


void FiguresRenderer::activateTriangle(glm::vec2 fstPoint, glm::vec2 secPoint,
		glm::vec2 thrdPoint, glm::vec4 color) {
	const GLfloat positions[] = { fstPoint.x, fstPoint.y, 0.0f, 1.0f, // fstPoint
			secPoint.x, secPoint.y, 0.0f, 1.0f, // secPoint
			thrdPoint.x, thrdPoint.y, 0.0f, 1.0f //thrdPoint
	};

	const GLfloat colors[] = { color.r, color.g, color.b, color.a, //fstPoint
			color.r, color.g, color.b, color.a, //secPoint
			color.r, color.g, color.b, color.a //thrdPoint
			};

	this->activateFigure(positions, sizeof(positions), colors, sizeof(colors));

	//delete[] (colors);
	//delete[] (positions);
}

void FiguresRenderer::activateRectangle(glm::vec2 fstPoint, glm::vec2 thrdPoint,
		glm::vec4 color) {
	// rectangle
	// 1-3
	// | |
	// 0-2

	const GLfloat positions[] = { fstPoint.x, fstPoint.y, 0.0f, 1.0f, // fstPoint
			//static const GLfloat *positions = { fstPoint.x, fstPoint.y, 0.0f, 1.0f, // fstPoint
			thrdPoint.x, fstPoint.y, 0.0f, 1.0f, // secPoint
			thrdPoint.x, thrdPoint.y, 0.0f, 1.0f, //thrdPoint
			fstPoint.x, thrdPoint.y, 0.0f, 1.0f //fthPoint
			};

	const GLfloat colors[] = { color.r, color.g, color.b, color.a, //fstPoint
			//static const GLfloat *colors = { color.r, color.g, color.b, color.a, //fstPoint
			color.r, color.g, color.b, color.a, //secPoint
			color.r, color.g, color.b, color.a, //thrdPoint
			color.r, color.g, color.b, color.a //fthPoint
			};

	this->activateFigure(positions, sizeof(positions), colors, sizeof(colors));
}


void FiguresRenderer::activateFigure(const GLfloat *positions,
		GLsizeiptr positionsSize,
		const GLfloat *colors, GLsizeiptr colorsSize) {

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positionsSize, positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colorsSize, colors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
}

void FiguresRenderer::activatePoint(glm::vec2 point, GLfloat pointSize,
		glm::vec4 color) {
	const GLfloat positions[] = { point.x, point.y, 0.0f, 1.0f // point
			};

	const GLfloat colors[] = { color.r, color.g, color.b, color.a //point
			};

	this->activateFigure(positions, sizeof(positions), colors, sizeof(colors));

}

void FiguresRenderer::renderTriangle(glm::vec2 fstPoint, glm::vec2 secPoint,
		glm::vec2 thrdPoint, glm::vec4 color) {
	this->activateTriangle(fstPoint, secPoint, thrdPoint, color);
	glDrawArrays(GL_TRIANGLES, 0, 3); //0 first, 3 count
}

void FiguresRenderer::renderRectangle(glm::vec2 fstPoint, glm::vec2 thrdPoint,
		glm::vec4 color) {
	this->activateRectangle(fstPoint, thrdPoint, color);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //0 first, 4 count
}

void FiguresRenderer::renderPoint(glm::vec2 point, GLfloat size,
		glm::vec4 color) {
	this->activatePoint(point, size, color);
	glPointSize(size);
	glDrawArrays(GL_POINTS, 0, 1); // 0 first, 1 count
}
} /* namespace base_game */

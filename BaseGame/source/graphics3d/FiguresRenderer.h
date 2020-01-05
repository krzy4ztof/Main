/*
 * FiguresRenderer.h
 *
 *  Created on: 24 lis 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_FIGURESRENDERER_H_
#define GRAPHICS3D_FIGURESRENDERER_H_

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2, glm:mat4

namespace base_game {

class FiguresRenderer {
public:
	FiguresRenderer();
	virtual ~FiguresRenderer();

	void init(GLuint programID);

	/*

	 void temp_startRender();

	void temp_activate();
	void temp_deactivate();

	void temp_render();
	 */

	void activate(glm::mat4 projection);
	void deactivate();

	void renderTriangle(glm::vec2 fstPoint, glm::vec2 secPoint,
			glm::vec2 thrdPoint, glm::vec4 color);
	void renderRectangle(glm::vec2 fstPoint, glm::vec2 thrdPoint,
			glm::vec4 color);
	void renderPoint(glm::vec2 point, GLfloat size, glm::vec4 color);


protected:
	void terminate();
	void activateTriangle(glm::vec2 fstPoint, glm::vec2 secPoint,
			glm::vec2 thrdPoint, glm::vec4 color);
	void activateRectangle(glm::vec2 fstPoint, glm::vec2 thrdPoint,
			glm::vec4 color);
	void activatePoint(glm::vec2 point, GLfloat size, glm::vec4 color);
	// void dectivateTriangle();

//	void activateFigure(const GLfloat positions[], const GLfloat colors[]);
//	void activateFigure(const GLfloat *positions, const GLfloat *colors);
	void activateFigure(const GLfloat *positions, GLsizeiptr positionsSize,
			const GLfloat *colors, GLsizeiptr colorsSize);


	
private:
	GLuint programID;
	GLuint positionBuffer;
	GLuint colorBuffer;

};

} /* namespace base_game */

#endif /* GRAPHICS3D_FIGURESRENDERER_H_ */

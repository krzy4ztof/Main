/*
 * GameUILabel.h
 *
 *  Created on: 19 lip 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_GAMEUILABEL_H_
#define USERINTERFACE_GAMEUILABEL_H_

#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/FreeTypeRenderer.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <string> // std::string
#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <memory> // shared_ptr

namespace base_game {

class GameUILabel {
public:
	GameUILabel(std::shared_ptr<OpenGLRenderer> openGLRenderer,
			std::string text);
	virtual ~GameUILabel();

	//void vOnRestore();
	void onRender(double fTime, float fElapsedTime);
	//void onRender(double fTime, float fElapsedTime);

	void setPosition(GLfloat x, GLfloat y);
	void setTextPosition(GLfloat x, GLfloat y);
	void setScale(GLfloat scale);
	void setSize(GLfloat width, GLfloat height);
	void end();

	std::string getText();
	void setOffset(GLfloat x, GLfloat y);
	glm::vec2 getTextSize();


protected:
	std::shared_ptr<FreeTypeRenderer> freeTypeRenderer;

	std::string text;
	GLfloat x, y; // left, lower corner coordinates
	GLfloat width, height; //width, height
	GLfloat scale; // text scale
	GLfloat textX, textY; // text left, lower corner coorinates
	GLfloat offsetX, offsetY;

	glm::vec3 color;
};

} /* namespace base_game */

#endif /* USERINTERFACE_GAMEUILABEL_H_ */

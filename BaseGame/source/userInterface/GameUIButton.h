/*
 * GameUIButton.h
 *
 *  Created on: 21 lip 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_GAMEUIBUTTON_H_
#define USERINTERFACE_GAMEUIBUTTON_H_

#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/FiguresRenderer.h"
#include "GameUILabel.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <string> // std::string
#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <memory> // shared_ptr


namespace base_game {

class GameUIButton {
public:
	GameUIButton(std::shared_ptr<OpenGLRenderer> openGLRenderer,
			std::string text);
	virtual ~GameUIButton();

	//void vOnRestore();
	void onRenderLabel(double fTime, float fElapsedTime);
	//void onRenderLabel(double fTime, float fElapsedTime);
	void onRenderBox(double fTime, float fElapsedTime);
	//void onRenderBox(double fTime, float fElapsedTime);

	void setPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat width, GLfloat height);
	void setColor(glm::vec4 color);
	void setMouseOverColor(glm::vec4 color);


	//void setLabelOffset(GLfloat x, GLfloat y);
	void setLabelScale(GLfloat scale);
	void end();

	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);

	void setCallback(void (*callbackFunction)(void *callbackObject),
			void *callbackObject);
	void setCursorCallback(
			void (*callbackFunction)(void *callbackObject,
					boolean cursorOverBtn), void *callbackObject);
	
	void setOffset(GLfloat x, GLfloat y);


protected:
	std::shared_ptr<FiguresRenderer> figuresRenderer;
	std::shared_ptr<GameUILabel> gameUILabel;
	bool mouseOver;

	GLfloat x, y, width, height, offsetX, offsetY;
	glm::vec4 color, mouseOverColor;

	void (*callbackFunction)(void *callbackObject) = NULL;
	void *callbackObject = NULL;

	void (*callbackCursorFunction)(void *callbackCursorObject,
			boolean cursorOverButton) = NULL;
	void *callbackCursorObject = NULL;

	//void initLabelOffset();
	//(void*)


};

} /* namespace base_game */

#endif /* USERINTERFACE_GAMEUIBUTTON_H_ */

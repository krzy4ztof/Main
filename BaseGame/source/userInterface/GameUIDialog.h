/*
 * GameUIDialog.h
 *
 *  Created on: 27 lip 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_GAMEUIDIALOG_H_
#define USERINTERFACE_GAMEUIDIALOG_H_

#include "../graphics3d/OpenGLRenderer.h"
#include "GameUIPane.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLFWwindow

#include <memory> // shared_ptr
#include <glm/glm.hpp> // glm::ivec2, glm:mat4

namespace base_game {

class GameUIDialog {
public:
	GameUIDialog(std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~GameUIDialog();

	//void vOnRestore();
	void onRender(double fTime, float fElapsedTime);

	void renderDialog(double fTime, float fElapsedTime);
	void renderPane(double fTime, float fElapsedTime);

	void addPane(std::shared_ptr<GameUIPane> gameUIPane);
	void setProjection(glm::mat4 projection);

	void setPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat width, GLfloat height);

	void setBackgroundColor(glm::vec4 color);
	void setBorderColor(glm::vec4 color);
	void setBorderWidth(GLfloat width);

	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);

protected:
	std::shared_ptr<OpenGLRenderer> openGLRenderer;
	std::shared_ptr<GameUIPane> gameUIPane;
	glm::mat4 projection;

	GLfloat x, y, width, height, borderWidth;

	glm::vec4 backgroundColor, borderColor;
};

} /* namespace base_game */

#endif /* USERINTERFACE_GAMEUIDIALOG_H_ */

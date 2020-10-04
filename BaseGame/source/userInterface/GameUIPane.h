/*
 * GameUIFrame.h
 *
 *  Created on: 19 lip 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_GAMEUIPANE_H_
#define USERINTERFACE_GAMEUIPANE_H_

#include "../graphics3d/OpenGLRenderer.h"
#include "GameUILabel.h"
#include "GameUIButton.h"
#include "GameUIPngImage.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLFWwindow

#include <memory> // shared_ptr
#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <list> // list

namespace base_game {

class GameUIPane {
public:
	GameUIPane(std::shared_ptr<OpenGLRenderer> openGLRenderer);
	virtual ~GameUIPane();

	void vOnRestore();
	void onRender(double fTime, float fElapsedTime);

	void renderLabels(double fTime, float fElapsedTime);
	void renderButtons(double fTime, float fElapsedTime);
	void renderPngImages(double fTime, float fElapsedTime);

	// setWidth
	// setHeight

	// setBorderLeft
	// setBorderRight
	// setBorderTop
	// setBorderDown

	// setOffsetX
	// setOffsetY

	// addButton
	// addLabel
	// addImage
	void addLabel(std::shared_ptr<GameUILabel> gameUILabel);
	void addButton(std::shared_ptr<GameUIButton> gameUIButton);
	void addPngImage(std::shared_ptr<GameUIPngImage> gameUIPngImage);
	void setProjection(glm::mat4 projection);

	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);

	void setOffset(GLfloat x, GLfloat y);
	void setLabelsOffset(GLfloat x, GLfloat y);
	void setButtonsOffset(GLfloat x, GLfloat y);
	void setPngImagesOffset(GLfloat x, GLfloat y);

protected:
	std::shared_ptr<OpenGLRenderer> openGLRenderer;
	std::list<std::shared_ptr<GameUILabel> > gameUILabels;
	std::list<std::shared_ptr<GameUIButton> > gameUIButtons;
	std::list<std::shared_ptr<GameUIPngImage> > gameUIPngImages;
	glm::mat4 projection;

	GLfloat offsetX, offsetY;

};

} /* namespace base_game */

#endif /* USERINTERFACE_GAMEUIPANE_H_ */

/*
 * GameUIPngImage.h
 *
 *  Created on: 23 lip 2020
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_GAMEUIPNGIMAGE_H_
#define USERINTERFACE_GAMEUIPNGIMAGE_H_

#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/SpriteSheet.h"
#include "../graphics3d/TextureRenderer.h"
#include "../graphics3d/TextureResourceLoader.h"

#include "GameUILabel.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLFWwindow

#include <string> // std::string
#include <memory> // shared_ptr


namespace base_game {

class GameUIPngImage {
public:
	GameUIPngImage(std::shared_ptr<OpenGLRenderer> openGLRenderer,
			std::string filename);
	virtual ~GameUIPngImage();

	//void vOnRestore();
	void onRender(double fTime, float fElapsedTime);
	//void onRender(double fTime, float fElapsedTime);

	void setPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat width, GLfloat height);

	void setOffset(GLfloat x, GLfloat y);

protected:
	std::shared_ptr<SpriteSheet> spriteSheet;
	std::shared_ptr<PngRenderer> pngRenderer;
	std::shared_ptr<PngTextureLoader> pngTextureLoader;

	GLfloat x, y, width, height;
	GLfloat offsetX, offsetY;

};

} /* namespace base_game */

#endif /* USERINTERFACE_GAMEUIPNGIMAGE_H_ */

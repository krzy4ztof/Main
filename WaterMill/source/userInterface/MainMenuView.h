/*
 * MainMenuView.h
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#ifndef SOURCE_WATERMILLGAME_MAINMENUVIEW_H_
#define SOURCE_WATERMILLGAME_MAINMENUVIEW_H_

#include "../../../BaseGame/source/userInterface/HumanView.h"
//#include <boost/gil/extension/io/jpeg.hpp> // boost::gil::rgb8_image_t
// #include <GL/freeglut.h> // GLUT, includes glu.h and gl.h
// #include <GL/glew.h> // include GLEW and new version of GL on Windows
//#include <GLFW/glfw3.h> // GLFW helper library

// #include <GL/glew.h>// allows extension: glGenerateMipmap, GLuint
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

namespace watermill {

class MainMenuView: public base_game::HumanView {
public:
	MainMenuView();
	virtual ~MainMenuView();
	virtual void tempVLoadGameDelegate();
	// void tempOnRenderGLFW(double fTime, float fElapsedTime);
//	void tempTestImage();
//	void tempLoadTexture();
	//void tempRenderTexture();
//	void tempLoadTexture_1();
//	void tempRenderTexture_1();

	virtual void vOnRender(double fTime, float fElapsedTime);

};

} /* namespace base_game */

#endif /* SOURCE_WATERMILLGAME_MAINMENUVIEW_H_ */

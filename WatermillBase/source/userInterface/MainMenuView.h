/*
 * MainMenuView.h
 *
 *  Created on: 5 sty 2019
 *      Author: Krzysztof
 */

#ifndef SOURCE_WATERMILLGAME_MAINMENUVIEW_H_
#define SOURCE_WATERMILLGAME_MAINMENUVIEW_H_

#include "MainMenuUI.h"

#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/userInterface/HumanView.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/userInterface/QuitMessageBoxUI.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

//#include <boost/gil/extension/io/jpeg.hpp> // boost::gil::rgb8_image_t
// #include <GL/freeglut.h> // GLUT, includes glu.h and gl.h
// #include <GL/glew.h> // include GLEW and new version of GL on Windows
//#include <GLFW/glfw3.h> // GLFW helper library

// #include <GL/glew.h>// allows extension: glGenerateMipmap, GLuint
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLFWwindow

#include <memory> // shared_ptr, weak_ptr


namespace watermill_base {

class MainMenuView: public base_game::HumanView {
public:
	MainMenuView(std::shared_ptr<base_game::ResourceCache> resourceCache,
			std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer,
			std::shared_ptr<base_game::GameMessages> gameMessages);
	virtual ~MainMenuView();

	virtual void tempVLoadGameDelegate();
	virtual void vTerminate();
	virtual bool vOnKeyCallback(GLFWwindow *window, int key, int scancode,
			int action, int mods);
	// void tempOnRenderGLFW(double fTime, float fElapsedTime);
//	void tempTestImage();
//	void tempLoadTexture();
	//void tempRenderTexture();
//	void tempLoadTexture_1();
//	void tempRenderTexture_1();
	virtual bool vOnCursorPositionCallback(GLFWwindow *window, double xpos,
			double ypos);
	//virtual bool vOnCursorEnterCallback(GLFWwindow* window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow *window, int button,
			int action, int mods);
	//virtual bool vOnScrollCallback(GLFWwindow* window, double xoffset,
	//		double yoffset);


	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void tempVRender(double fTime, float fElapsedTime);

	void initQuitMessageBox(
			std::shared_ptr<base_game::ResourceCache> resourceCache,
			std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer,
			std::shared_ptr<base_game::GameMessages> gameMessages);
	void openQuitMessageBox();
	//void tempCloseQuitMessageBox();
protected:
	//std::shared_ptr<base_game::ResourceCache> shrdPtrResourceCache;
	std::shared_ptr<MainMenuUI> m_MainMenuUI;
	std::shared_ptr<base_game::QuitMessageBoxUI> m_MessageBoxUI;


};

} /* namespace watermill */

#endif /* SOURCE_WATERMILLGAME_MAINMENUVIEW_H_ */

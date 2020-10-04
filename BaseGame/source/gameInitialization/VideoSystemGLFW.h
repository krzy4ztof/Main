/*
 * VideoSystemGLFW.h
 *
 *  Created on: 31 gru 2018
 *      Author: Krzysztof
 */

#ifndef GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_
#define GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_

#include "../graphics3d/FpsCounter.h"

// #define GLEW_STATIC
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>

#include <memory> // shared_ptr

namespace base_game {

class VideoSystemGLFW {
public:

	const static int WINDOW_WIDTH;
	const static int WINDOW_HEIGHT;

	VideoSystemGLFW();
	virtual ~VideoSystemGLFW();

	int initialize();
	void onIdle();
	void onIdle_111();
	void mainLoop();
	//int tempGLUTinitialize();
	bool preRender();
	bool postRender();

	GLFWwindow* getWindow();

protected:
	GLFWwindow *window;
	//std::shared_ptr<GLFWwindow> window;
	// float angle = 0.0f;
//	double lastTime = 0;
	//GLFWcursor *cursor;

// TODO: Maybe temp_fpsCounter should be shared pointer poining also to HumanView.fpsCounter??
	FpsCounter *temp_fpsCounter;
};

} /* namespace base_game */

#endif /* GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_ */

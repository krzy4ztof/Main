/*
 * VideoSystemGLFW.h
 *
 *  Created on: 31 gru 2018
 *      Author: Krzysztof
 */

#ifndef GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_
#define GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_

// #define GLEW_STATIC
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>
// #include <GL/freeglut.h> // TODO: remove

namespace base_game {

class VideoSystemGLFW {
public:

	const static int WINDOW_WIDTH;
	const static int WINDOW_HEIGHT;


	VideoSystemGLFW();
	virtual ~VideoSystemGLFW();
	int startGLFW_222();
	int startGLFW_333_ok();

	int initialize();
	void onIdle();
	void mainLoop();
	//int tempGLUTinitialize();



protected:
	GLFWwindow* window;
	float angle = 0.0f;
	double lastTime = 0;
};

} /* namespace base_game */

#endif /* GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_ */

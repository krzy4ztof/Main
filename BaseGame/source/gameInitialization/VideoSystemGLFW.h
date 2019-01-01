/*
 * VideoSystemGLFW.h
 *
 *  Created on: 31 gru 2018
 *      Author: Krzysztof
 */

#ifndef GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_
#define GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_

#include <GLFW/glfw3.h>

namespace base_game {

class VideoSystemGLFW {
public:
	VideoSystemGLFW();
	virtual ~VideoSystemGLFW();
	int startGLFW_222();
	int startGLFW_333_ok();

	int initialize();
	void onIdle();
	int mainLoop();

protected:
	GLFWwindow* window;
	float angle = 0.0f;
	double lastTime = 0;
};

} /* namespace base_game */

#endif /* GAMEINITIALIZATION_VIDEOSYSTEMGLFW_H_ */

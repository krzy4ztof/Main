/*
 * VideoSystemGLFW.cpp
 *
 *  Created on: 31 gru 2018
 *      Author: Krzysztof
 */

#include "VideoSystemGLFW.h"
#include "GameCodeApp.h"//g_pApp
#include "../debugging/Logger.h"
#include "../inputDevices/IKeyboardHandler.h"
#include "../inputDevices/IPointerHandler.h"
#include "../graphics3d/FpsCounter.h"
#include "../utilities/Templates.h"

#include <sstream>      // std::stringstream
// #include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>

using std::stringstream;

namespace base_game {

const int VideoSystemGLFW::WINDOW_WIDTH = 640;
const int VideoSystemGLFW::WINDOW_HEIGHT = 640; //480;

VideoSystemGLFW::VideoSystemGLFW() {
	logger::info("Create VideoSystemGLFW");
	window = nullptr;
	temp_fpsCounter = new FpsCounter();

}

VideoSystemGLFW::~VideoSystemGLFW() {
	logger::info("Destroy VideoSystemGLFW");
	templates::safe_delete<FpsCounter>(temp_fpsCounter);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void VideoSystemGLFW::onIdle() {
	stringstream ss;



	if (base_game::g_pApp != nullptr) {

		double time = glfwGetTime();
		double elapsedTime = time - temp_fpsCounter->getLastTime();
		float elapsedTimeFloat = static_cast<float>(elapsedTime);

		g_pApp->onUpdateGame(time, elapsedTimeFloat);

		g_pApp->onFrameRender(time, elapsedTimeFloat);

		/* Poll for and process events */
		glfwPollEvents();

	} else {
		ss << "g_pApp not initialized " << time; // << "; angle: " << angle;
		logger::info(ss);
	}

}

bool VideoSystemGLFW::preRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

bool VideoSystemGLFW::postRender() {
	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
//	glfwPollEvents();

	return true;
}

void VideoSystemGLFW::onIdle_111() {
	stringstream ss;

	// miliseconds
	double time = glfwGetTime();
	double elapsedTime = time - temp_fpsCounter->getLastTime();
	float elapsedTimeFloat = static_cast<float>(elapsedTime);

	ss << "GLUT RENDER SCENE: time:" << time << "; elapsedTime " << elapsedTime;
	//<< "; angle: " << angle;
	//logger::info(ss);

	if (base_game::g_pApp != nullptr) {
		g_pApp->onUpdateGame(time, elapsedTimeFloat);

		if (temp_fpsCounter->renderNextFrame(time)) {
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			g_pApp->onFrameRender(time, elapsedTimeFloat);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	} else {
		ss << "g_pApp not initialized " << time; // << "; angle: " << angle;
		logger::info(ss);
	}

}

/*
 int VideoSystemGLFW::tempGLUTinitialize() {
 char fakeParam[] = "fake";
 char *fakeargv[] = { fakeParam, NULL };
 int fakeargc = 1;
 glutInit(&fakeargc, fakeargv);
 }
 */

int VideoSystemGLFW::initialize() {
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
			"GLFW Hello World - press R,1,2..",
			NULL,
			NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Initialize GLEW */
	/*
	 GLenum err = glewInit();
	 if (GLEW_OK != err) {
	 return -1;
	 }
	 */

	// START Tutorial
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// END Tutorial

	glfwSetKeyCallback(window, keyboard_handler::onKeyCallback);
	glfwSetCharCallback(window, keyboard_handler::onCharCallback);
	glfwSetCharModsCallback(window, keyboard_handler::onCharmodsCallback);

	glfwSetCursorPosCallback(window, pointer_handler::onCursorPositionCallback);
	glfwSetCursorEnterCallback(window, pointer_handler::onCursorEnterCallback);
	glfwSetMouseButtonCallback(window, pointer_handler::onMouseButtonCallback);
	glfwSetScrollCallback(window, pointer_handler::onScrollCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// stempGLUTinitialize();

	/* Initialize GLEW */
	/* Initialize GLEw after initializing context and (maybe glutInit) */
	// Initialize GLEW Start Tutorial
	glewExperimental = true; // Needed for core profile
	// END Tutorial

	temp_fpsCounter->setFirstTime(glfwGetTime());

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		return -1;
	}

	return 0;
}

void VideoSystemGLFW::mainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		this->onIdle();

		/* Swap front and back buffers */
		//glfwSwapBuffers(window);

		/* Poll for and process events */
		//glfwPollEvents();
	}
}
} /* namespace base_game */

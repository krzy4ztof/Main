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

#include <sstream>      // std::stringstream
#include <GLFW/glfw3.h>

using std::stringstream;

namespace base_game {

VideoSystemGLFW::VideoSystemGLFW() {
	logger::info("Create VideoSystemGLFW");
	GLFWwindow* window = nullptr;

}

VideoSystemGLFW::~VideoSystemGLFW() {
	logger::info("Destroy VideoSystemGLFW");
	glfwDestroyWindow(window);
	glfwTerminate();
}

void VideoSystemGLFW::onIdle() {
	stringstream ss;

	// miliseconds
	double time = glfwGetTime();
	double elapsedTime = time - lastTime;
	lastTime = time;

	//renderScene();

	//			ss << "GLUT IDLE: " << time;
	//			logger::info(ss);

	//displayFreeGlut();

	// double timeDouble = static_cast<float>(time);
	float elapsedTimeFloat = static_cast<float>(elapsedTime);

	ss << "GLUT RENDER SCENE: time:" << time << "; elapsedTime " << elapsedTime
			<< "; angle: " << angle;
	//logger::info(ss);

	if (base_game::g_pApp != nullptr) {
		//base_game::g_pApp->testGlobal();
		//base_game::g_pApp->onUpdateGame(timeDouble,elapsedTimeFloat);
		g_pApp->onUpdateGame(time, elapsedTimeFloat);

		//gameCode->onFrameRender
		// baseGameLogic->onFrameRender
		// HumanView->vOnRender
		// HumanView->tempOnRender (openGL)
		g_pApp->onFrameRender(time, elapsedTimeFloat);

	} else {
		ss << "g_pApp not initialized " << time << "; angle: " << angle;
		logger::info(ss);
	}

}

int VideoSystemGLFW::initialize() {
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "GLFW Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, keyboard_handler::onKeyCallback);
	glfwSetCharCallback(window, keyboard_handler::onCharCallback);
	glfwSetCharModsCallback(window, keyboard_handler::onCharmodsCallback);

	glfwSetCursorPosCallback(window, pointer_handler::onCursorPositionCallback);
	glfwSetCursorEnterCallback(window, pointer_handler::onCursorEnterCallback);
	glfwSetMouseButtonCallback(window, pointer_handler::onMouseButtonCallback);
	glfwSetScrollCallback(window, pointer_handler::onScrollCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	return 0;
}

int VideoSystemGLFW::mainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		this->onIdle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

int VideoSystemGLFW::startGLFW_333_ok() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear (GL_COLOR_BUFFER_BIT);
		this->onIdle();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int VideoSystemGLFW::startGLFW_222() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

} /* namespace base_game */

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
// #include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>

using std::stringstream;

namespace base_game {

const int VideoSystemGLFW::WINDOW_WIDTH = 640;
const int VideoSystemGLFW::WINDOW_HEIGHT = 640; //480;

VideoSystemGLFW::VideoSystemGLFW() {
	logger::info("Create VideoSystemGLFW");
	window = nullptr;

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

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   VideoSystem.cpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 12:49
 */

#include "VideoSystem.h"
#include "ErrorCode.h"

//#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h


//#include <cstring>// strcpy

#include "../gameInitialization/Macros.h" // GAME_TITLE
#include <iostream> // cout, endl

#include <cstdio> //fflush, printf

#include "../utilities/StringUtils.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using std::cout;
using std::endl;
using std::fflush;
using std::stringstream;

namespace base_game {

	namespace video_system {

		/* Handler for window-repaint event. Call back when the window first appears and
		whenever the window needs to be re-painted. */
		/**/
		void displayFreeGlut() {
			logger::info("display----");
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
			glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

			// Draw a Red 1x1 Square centered at origin
			glBegin(GL_QUADS); // Each set of 4 vertices form a quad
			//glColor3f(1.0f, 0.0f, 0.0f); // Red
			glColor3f(1.0f, 1.0f, 0.0f); // Yellow

			glVertex2f(-0.5f, -0.5f); // x, y
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.5f, 0.5f);
			glVertex2f(-0.5f, 0.5f);
			glEnd();

			glFlush(); // Render now
		}

		/**/

		void onChangeSize(int width, int height) {
			stringstream ss;
			ss << "GLUT Width: " << width << ", height: " << height;
			logger::trace(ss);
		}

		void onClose() {
			logger::trace("GLUT onClose");

			// !!!!!!!!!!!!!!!!!!!!
			// If glutLeaveMainLoop()
			// it is not commented out snd
			//  		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
			//		  GLUT_ACTION_GLUTMAINLOOP_RETURNS);
			// is commented out in VideoSystem::startFreeGlut then after this invocation program exits.
			// GameCodeApp destructor is not called. Memory pool destructor is not called either.

			//glutLeaveMainLoop();
			// !!!!!!!!!!!!!!!!!!!!

		}

		void onHideShow(int state) {
			stringstream ss;

			if (state == GLUT_NOT_VISIBLE) {
				ss << " GLUT window hidden";

				logger::trace(ss);

			} else {
				ss << " GLUT window visible";

				logger::trace(ss);

			}

			ss << "GLUT_NOT_VISIBLE: " << GLUT_NOT_VISIBLE << ", GLUT_VISIBLE: " << GLUT_VISIBLE;
			logger::trace(ss);

			ss << "GLUT visibilityFunction: " << state;
			logger::trace(ss);

		}


	}

	VideoSystem::VideoSystem() {
		logger::trace("Create VideoSystem");
		// Initialization
		bool somethingWentWrong = false;

		if (somethingWentWrong) {
			throw ErrorCode("EC_VIDEOSYSTEM_PROBLEM", 789);
		}
	}

	VideoSystem::VideoSystem(const VideoSystem& orig) {
		logger::trace("Create VideoSystem");
	}

	VideoSystem::~VideoSystem() {
		logger::trace("Destroy VideoSystem");
	}

	/* Main function: GLUT runs as a console application starting at main()  */

	/* */
	void VideoSystem::startFreeGlut(string title) {

		char* titleChar = string_utils::stringToChar(title);

		//char* titleChar = new char[title.length() + 1];
		//strcpy ( titleChar, title.c_str() );

		char *argv [1];
		int argc=1;
		argv [0]= strdup(titleChar);
		logger::trace("glutInit+++");
		glutInit(&argc, argv); // Initialize GLUT
		glutCreateWindow(titleChar); // Create a window with the given title

		glutInitWindowSize(320, 320); // Set the window's initial width & height
		glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

		//glutFullScreen();


		logger::trace("glutDisplayFunc+++");
		glutDisplayFunc(video_system::displayFreeGlut); // Register display callback handler for window re-paint
		//glutDisplayFunc(this->*display); // Register display callback handler for window re-paint
		//glutDisplayFunc(&VideoSystem::display);
		//glutDisplayFunc([](){display();});
		//glutDisplayFunc(VideoSystem::display);

		glutReshapeFunc(video_system::onChangeSize);

		glutCloseFunc(video_system::onClose);

		glutVisibilityFunc(video_system::onHideShow);

		// !!!!!!!!!!!!!!!!!!!!
		// Note: glutSetOption is only available with freeglut

		// Following code can be commented. But onClose() need to contain call to glutLeaveMainLoop();
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
					  GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		// !!!!!!!!!!!!!!!!!!!!

		//mainInit(argc, argv);
		logger::trace("glutMainLoop+++");
		//fflush(stdout);
		//glutMainLoop(); // Enter the infinitely event-processing loop
		//glutMainLoopEvent(); // Enter the infinitely event-processing loop

		logger::trace("after glutMainLoop+++");

		string_utils::safe_delete_char_array(titleChar);
	}

	void VideoSystem::startFreeGlutMainLoop() {
		glutMainLoop(); // Enter the infinitely event-processing loop
	}
}

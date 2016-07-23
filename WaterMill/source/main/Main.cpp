/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Krzysztof
 *
 * Created on 28 kwietnia 2016, 17:51
 */


#include <cstdlib>
#include <stdio.h>

#include<iostream> // cout

#include "../gameInitialization/Macros.hpp"
#include "../testClasses/TestClass.hpp"
#include "../gameInitialization/GameCodeApp.hpp"


//#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h


using namespace std;

/*
 *
 */



void testMain() {
	watermill::TestClass testClass;
	//testClass.simpleRun();
	//testClass.run();
	//testClass.primeSearchRun();
	//testClass.randomGeneratorRun();
	testClass.memoryPoolRun();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_QUADS); // Each set of 4 vertices form a quad
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(-0.5f, -0.5f); // x, y
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glFlush(); // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int mainOpenGl(int argc, char** argv) {

	glutInit(&argc, argv); // Initialize GLUT
	glutCreateWindow(GAME_TITLE); // Create a window with the given title
	glutInitWindowSize(320, 320); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint

	watermill::GameCodeApp * gameCodeApp;
	gameCodeApp = new watermill::GameCodeApp;

	//    bool resInit = gameCodeApp->initInstance();
	bool resInit = gameCodeApp->initInstanceShortDebug();


	int checkCpp11{457};
	//  auto anotherCpp11check = checkCpp11;

	cout << "CheckCpp11: " << checkCpp11 << endl;
	//  cout << " AnotherCheckCpp11: " << anotherCpp11check << endl;

	if (!resInit) {
		cout << "gameCodeApp init failed" << endl;
		return 1;
	} else {
		cout << "gameCodeApp init succeeded" << endl;
	}

	glutMainLoop(); // Enter the infinitely event-processing loop
	return 0;
}

int main(int argc, char** argv) {
	/*
	 * main (int argc, char* argv[])
	 * 'char** argv'  the same as   'char* argv[]' means pointer to pointer to char
	 * argv - returns address
	 */

	 testMain();
	int res = 0;
	//res = mainOpenGl(argc, argv);
	return res;

}


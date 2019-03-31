/*
 * T004figuresView.cpp
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#include "TempT004figuresView.h"

// #include "../main/OpenGLShader.h"
#include "TempShader.hpp"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>


using std::cout;
using std::endl;

namespace base_game {

TempT004figuresView::TempT004figuresView() {
	cout << "Create TempT004figuresView" << endl;
	programID = 0;
	positionBuffer = 0;
	colorBuffer = 0;
}

TempT004figuresView::~TempT004figuresView() {
	cout << "Destroy TempT004figuresView" << endl;
	this->vTerminate();
}

void TempT004figuresView::vTerminate() {

	// glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(programID);
}

void TempT004figuresView::vInit() {
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glGenBuffers(1, &positionBuffer);
	glGenBuffers(1, &colorBuffer);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("../../../assets/shaders/TempT004figuresView.vert",
			"../../../assets/shaders/TempT004figuresView.frag");


	vActivate();
}

void TempT004figuresView::vActivate() {
	HumanView::vActivate();

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	/*
	GLfloat fstTriangle[] = { -1.0f, 0.5f, 0.0f, 1.0f, //
			-0.5f, 0.5f, 0.0f, 1.0f, //
			-0.75f, 1.0f, 0.0f, 1.0f };

	GLfloat secTriangle[] = { 0.5f, 1.0f, 0.0f, 1.0f, //
			1.0f, 1.0f, 0.0f, 1.0f, //
			0.75f, 0.5f, 0.0f, 1.0f };

	GLfloat quadr[] = { -1.0f, -1.0f, 0.0f, 1.0f, //
			-0.5f, -1.0f, 0.0f, 1.0f, //
			-0.5f, -0.5f, 0.0f, 1.0f, //
			-1.0f, -0.5f, 0.0f, 1.0f };
	 */

	static const GLfloat positions[] = { -1.0f, 0.5f, 0.0f, 1.0f, // fst triangle
			-0.5f, 0.5f, 0.0f, 1.0f, //
			-0.75f, 1.0f, 0.0f, 1.0f, //
			0.5f, 1.0f, 0.0f, 1.0f, // points
			1.0f, 1.0f, 0.0f, 1.0f, //
			0.75f, 0.5f, 0.0f, 1.0f, //
			-1.0f, -1.0f, 0.0f, 1.0f, // quadr
			-0.5f, -1.0f, 0.0f, 1.0f, //
			-0.5f, -0.5f, 0.0f, 1.0f, //
			-1.0f, -0.5f, 0.0f, 1.0f };

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	static const GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f, //fst triangle
			1.0f, 0.0f, 0.0f, 1.0f, //
			1.0f, 0.0f, 0.0f, 1.0f, //
			1.0f, 0.0f, 0.0f, 1.0f, //points
			0.0f, 1.0f, 0.0f, 1.0f, //
			0.0f, 0.0f, 1.0f, 1.0f, //

			1.0f, 0.0f, 0.0f, 1.0f, //quadr
			0.0f, 1.0f, 0.0f, 1.0f, //
			0.0f, 0.0f, 1.0f, 1.0f, //
			1.0f, 1.0f, 0.0f, 1.0f };


// Bind the second and initialize it
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
// Use the program object we created earlier for rendering
	glUseProgram(programID);

}

void TempT004figuresView::vDeactivate() {
	HumanView::vDeactivate();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
}

//void TempT004figuresView::vRender(double currentTime, float fElapsedTime) {
void TempT004figuresView::vOnRender(double currentTime, float fElapsedTime) {

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glPointSize(8.0f);

	glDrawArrays(GL_POINTS, 3, 3);

	glDrawArrays(GL_TRIANGLE_FAN, 6, 4);

	//16, 32
}


namespace temp_t004_figures_view {
TempT004figuresView* openGLview = nullptr;

TempT004figuresView* getView(bool reset) {
	if (openGLview == nullptr) {
		openGLview = new TempT004figuresView();
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT004figuresView();
			openGLview->vInit();
		}
	}
	return openGLview;
}
}

} /* namespace base_game */

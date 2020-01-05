/*
 * T004figuresView.cpp
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#include "TempT004figuresView.h"
#include "../debugging/Logger.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/FiguresRenderer.h"
#include "../debugging/Logger.h"
#include "../gameInitialization/VideoSystemGLFW.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>
#include <memory> // shared_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::ortho

#include <string> // string
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;
#include <sstream>      // std::stringstream

using std::string;
using boost::filesystem::path;
using std::stringstream;
using std::shared_ptr;
using std::make_shared;

namespace base_game {

/*
TempT004figuresView::TempT004figuresView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT004figuresView");
	programID = 0;
	positionBuffer = 0;
	colorBuffer = 0;

	this->shrdPtrResourceCache = resourceCache;
}

TempT004figuresView::~TempT004figuresView() {
	logger::info("Destroy TempT004figuresView");
	this->vTerminate();
	shrdPtrResourceCache.reset();
}

void TempT004figuresView::vTerminate() {
	glDeleteProgram(programID);
}
 */

TempT004figuresView::TempT004figuresView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT004figuresView");
	//programID = 0;
	//positionBuffer = 0;
	//colorBuffer = 0;

	this->shrdPtrResourceCache = resourceCache;
	figuresRenderer = make_shared<FiguresRenderer>();

}

TempT004figuresView::~TempT004figuresView() {
	logger::info("Destroy TempT004figuresView");
	this->vTerminate();
	shrdPtrResourceCache.reset();
	figuresRenderer.reset();
}

void TempT004figuresView::vTerminate() {
	//glDeleteProgram(programID);
}


void TempT004figuresView::vInit() {
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

//	glGenBuffers(1, &positionBuffer);
//	glGenBuffers(1, &colorBuffer);

	stringstream ss;

	/*
	string vertResourceName = "temp_t004_figures_view.vert";
	ss << "vertPath: " << vertResourceName;
	logger::info(ss);

	string fragResourceName = "temp_t004_figures_view.frag";
	ss << "fragPath: " << fragResourceName;
	logger::info(ss);
	 */
	
	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);

//	GLuint programID = shaderCompiler.loadShaders(vertResourceName,
//			fragResourceName);

	GLuint programID = shaderCompiler.loadShaders("figures_renderer");
	figuresRenderer->init(programID);

	vActivate();
}

/*
 void TempT004figuresView::vInit() {
 //	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

 glGenBuffers(1, &positionBuffer);
 glGenBuffers(1, &colorBuffer);

 stringstream ss;

 string vertResourceName = "temp_t004_figures_view.vert";
 ss << "vertPath: " << vertResourceName;
 logger::info(ss);

 string fragResourceName = "temp_t004_figures_view.frag";
 ss << "fragPath: " << fragResourceName;
 logger::info(ss);

 ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);

 GLuint programID = shaderCompiler.loadShaders(vertResourceName,
 fragResourceName);
 figuresRenderer->init(programID);

 vActivate();
 }
 */

void TempT004figuresView::vActivate() {
	HumanView::vActivate();

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

//
//	 GLfloat fstTriangle[] = { -1.0f, 0.5f, 0.0f, 1.0f, //
//	 -0.5f, 0.5f, 0.0f, 1.0f, //
//	 -0.75f, 1.0f, 0.0f, 1.0f };
//
//	 GLfloat secTriangle[] = { 0.5f, 1.0f, 0.0f, 1.0f, //
//	 1.0f, 1.0f, 0.0f, 1.0f, //
//	 0.75f, 0.5f, 0.0f, 1.0f };
//
//	 GLfloat quadr[] = { -1.0f, -1.0f, 0.0f, 1.0f, //
//	 -0.5f, -1.0f, 0.0f, 1.0f, //
//	 -0.5f, -0.5f, 0.0f, 1.0f, //
//	 -1.0f, -0.5f, 0.0f, 1.0f };
//

	//figuresRenderer->activate();

	const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
// Use the program object we created earlier for rendering
	//glUseProgram(programID);

}

/*
 void TempT004figuresView::vActivate() {
 HumanView::vActivate();

 // Dark background
 glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

 //
 //	 GLfloat fstTriangle[] = { -1.0f, 0.5f, 0.0f, 1.0f, //
 //	 -0.5f, 0.5f, 0.0f, 1.0f, //
 //	 -0.75f, 1.0f, 0.0f, 1.0f };
 //
 //	 GLfloat secTriangle[] = { 0.5f, 1.0f, 0.0f, 1.0f, //
 //	 1.0f, 1.0f, 0.0f, 1.0f, //
 //	 0.75f, 0.5f, 0.0f, 1.0f };
 //
 //	 GLfloat quadr[] = { -1.0f, -1.0f, 0.0f, 1.0f, //
 //	 -0.5f, -1.0f, 0.0f, 1.0f, //
 //	 -0.5f, -0.5f, 0.0f, 1.0f, //
 //	 -1.0f, -0.5f, 0.0f, 1.0f };
 //	 

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
 */

void TempT004figuresView::vDeactivate() {
	HumanView::vDeactivate();

//	figuresRenderer->deactivate();
}
/*
 void TempT004figuresView::vDeactivate() {
 HumanView::vDeactivate();
 glBindBuffer(GL_ARRAY_BUFFER, 0);
 glDisableVertexAttribArray(0);
 glDisableVertexAttribArray(1);
 glUseProgram(0);
 }
 */
void TempT004figuresView::vOnRender(double currentTime, float fElapsedTime) {

	// figuresRenderer->temp_startRender();
	/*
	figuresRenderer->temp_activate();


	figuresRenderer->temp_render();

	figuresRenderer->temp_deactivate();
	 */

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	figuresRenderer->activate(projection);

	//figuresRenderer->temp_render();
	figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
			glm::vec2(100.0f, 0.0f), glm::vec2(50.f, 200.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	figuresRenderer->renderRectangle(glm::vec2(200.0f, 200.0f),
			glm::vec2(240.0f, 240.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	figuresRenderer->renderPoint(glm::vec2(300.0f, 400.0f), 8.0f,
			glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	//figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
	//		glm::vec2(1.0f, 0.0f), glm::vec2(0.5f, 1.0f),
	//		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	figuresRenderer->deactivate();



	/*
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glPointSize(8.0f);

	glDrawArrays(GL_POINTS, 3, 3);

	glDrawArrays(GL_TRIANGLE_FAN, 6, 4);
	 */
	//16, 32
}

namespace temp_t004_figures_view {
TempT004figuresView* openGLview = nullptr;

shared_ptr<TempT004figuresView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache) {
	if (openGLview == nullptr) {
		openGLview = new TempT004figuresView(resourceCache);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT004figuresView(resourceCache);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT004figuresView> { openGLview };
}
}

} /* namespace base_game */

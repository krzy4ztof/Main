/*
 * T004figuresView.cpp
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#include "TempT004figuresView.h"
#include "../debugging/Logger.h"
// #include "../main/OpenGLShader.h"
//#include "TempShader.hpp"
#include "../graphics3D/ShaderResourceLoader.h"
#include "../debugging/Logger.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>

#include <string> // string
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;
#include <sstream>      // std::stringstream

//using std::cout;
//using std::endl;
using std::string;
using boost::filesystem::path;
using std::stringstream;
using std::shared_ptr;

namespace base_game {

TempT004figuresView::TempT004figuresView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT004figuresView");
	// cout << "Create TempT004figuresView" << endl;
	programID = 0;
	positionBuffer = 0;
	colorBuffer = 0;

	this->shrdPtrResourceCache = resourceCache;
}

TempT004figuresView::~TempT004figuresView() {
	logger::info("Destroy TempT004figuresView");
	// cout << "Destroy TempT004figuresView" << endl;
	this->vTerminate();
	shrdPtrResourceCache.reset();
}

void TempT004figuresView::vTerminate() {

	// glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(programID);
}

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

	//programID = LoadShaders(vertResourceName.c_str(), fragResourceName.c_str());
	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();

	programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);

	// Create and compile our GLSL program from the shaders
	//programID = LoadShaders("../../../assets/shaders/TempT004figuresView.vert",
	//	"../../../assets/shaders/TempT004figuresView.frag");

	vActivate();
}

/*
 void TempT004figuresView::vInit() {
 //	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

 glGenBuffers(1, &positionBuffer);
 glGenBuffers(1, &colorBuffer);

 stringstream ss;

 //path vertPath { this->m_assetsFolder };
 path vertPath { this->shrdPtrResourceCache->assetsFolder };

 vertPath /= "shaders/TempT004figuresView.vert";
 //thisResPath /= resource.getName();
 vertPath = vertPath.make_preferred();
 string vertResourceName = vertPath.string();
 ss << "vertPath: " << vertResourceName;
 logger::info(ss);


 //path fragPath { this->m_assetsFolder };
 path fragPath { this->shrdPtrResourceCache->assetsFolder };

 fragPath /= "shaders/TempT004figuresView.frag";
 //thisResPath /= resource.getName();
 fragPath = fragPath.make_preferred();
 string fragResourceName = fragPath.string();
 ss << "fragPath: " << fragResourceName;
 logger::info(ss);

 //programID = LoadShaders(vertResourceName.c_str(), fragResourceName.c_str());
 ShaderCompiler shaderCompiler; // = new ShaderCompiler();

 programID = shaderCompiler.loadShaders(vertResourceName.c_str(),
 fragResourceName.c_str());
 
 // Create and compile our GLSL program from the shaders
 //programID = LoadShaders("../../../assets/shaders/TempT004figuresView.vert",
 //	"../../../assets/shaders/TempT004figuresView.frag");


 vActivate();
 }
 */

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

//TempT004figuresView*
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
	//return openGLview;
	return shared_ptr<TempT004figuresView> { openGLview };
}
}

} /* namespace base_game */

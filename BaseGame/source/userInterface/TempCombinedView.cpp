/*
 * T004figuresView.cpp
 *
 *  Created on: 7 lut 2019
 *      Author: Krzysztof
 */

#include "TempCombinedView.h"
#include "../debugging/Logger.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/FiguresRenderer.h"
#include "../graphics3d/FreeTypeRenderer.h"
#include "../graphics3d/FreeTypeResourceLoader.h"
#include "../debugging/Logger.h"
#include "../graphics3d/TextureRenderer.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/SpriteSheet.h"

#include "../gameInitialization/VideoSystemGLFW.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>
#include <memory> // shared_ptr

#include <glm/glm.hpp> // glm::ivec2
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

TempCombinedView::TempCombinedView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempCombinedView");

	this->shrdPtrResourceCache = resourceCache;

	figuresRenderer = make_shared<FiguresRenderer>();
	freeTypeRenderer = make_shared<FreeTypeRenderer>();

	spriteSheet = make_shared<SpriteSheet>();
	spriteSheet2 = make_shared<SpriteSheet>();
	spriteSheetPng = make_shared<SpriteSheet>();

	jpegTextureLoader = make_shared<JpegTextureLoader>(
			this->shrdPtrResourceCache);
	pngTextureLoader = make_shared<PngTextureLoader>(
			this->shrdPtrResourceCache);

//	jpegTextureLoader2 = make_shared<JpegTextureLoader>(
//			this->shrdPtrResourceCache);
	jpegRenderer = make_shared<JpegRenderer>();
	pngRenderer = make_shared<PngRenderer>();

}

TempCombinedView::~TempCombinedView() {
	logger::info("Destroy TempCombinedView");
	this->vTerminate();

	pngRenderer.reset();
	jpegRenderer.reset();

	//jpegTextureLoader2.reset();
	pngTextureLoader.reset();
	jpegTextureLoader.reset();


	spriteSheetPng.reset();
	spriteSheet2.reset();
	spriteSheet.reset();

	freeTypeRenderer.reset();
	figuresRenderer.reset();
	shrdPtrResourceCache.reset();
}

void TempCombinedView::vTerminate() {
	pngTextureLoader->terminate();
	jpegTextureLoader->terminate();


	//jpegTextureLoader2->terminate();
}


void TempCombinedView::vInit() {
	stringstream ss;

	/*
	string vertResourceName = "temp_t004_figures_view.vert";
	ss << "vertPath: " << vertResourceName;
	logger::info(ss);
	string fragResourceName = "temp_t004_figures_view.frag";
	ss << "fragPath: " << fragResourceName;
	logger::info(ss);
	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler.loadShaders(vertResourceName,
			fragResourceName);
	 */
	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler.loadShaders("figures_renderer");
//	GLuint programID = shaderCompiler.loadShaders("temp_t004_figures_view");


	figuresRenderer->init(programID);

	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters =
			freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();

	/*
	string freeTypeVertResourceName = "temp_t00f_polish_fonts_view.vert";
	string freeTypeFragResourceName = "temp_t00f_polish_fonts_view.frag";
	ShaderCompiler freeTypeShaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	GLuint freeTypeProgramID = freeTypeShaderCompiler.loadShaders(
	 freeTypeVertResourceName, freeTypeFragResourceName);
	 */
	GLuint freeTypeProgramID = shaderCompiler.loadShaders(
			"temp_t00f_polish_fonts_view");
	
	freeTypeRenderer->init(freeTypeProgramID, characters);
	freeTypeRenderer->debugCharacters();

//	jpegTextureLoader2->init("temp_t009_jpeg_gil_texture_view.jpg",
	jpegTextureLoader->init("temp_t009_jpeg_gil_texture_view.jpg",
			spriteSheet2);
	jpegTextureLoader->init("temp_g1040.jpg", spriteSheet);
	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);
	spriteSheet->setRows(2);

	pngTextureLoader->init("temp_t00d_png_gil_scanline_view_pools_alpha.png",
			spriteSheetPng);

	spriteSheetPng->setMargin(1);
	spriteSheetPng->setColumns(4);

	GLuint jpegProgramID = shaderCompiler.loadShaders("texture_renderer");

	jpegRenderer->init(jpegProgramID);
	pngRenderer->init(jpegProgramID);


	vActivate();
}

void TempCombinedView::vActivate() {
	HumanView::vActivate();

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);

}

void TempCombinedView::vDeactivate() {
	HumanView::vDeactivate();

//	figuresRenderer->deactivate();
}

void TempCombinedView::vOnRender(double currentTime, float fElapsedTime) {


	/*
	figuresRenderer->temp_activate();
	figuresRenderer->temp_render();
	figuresRenderer->temp_deactivate();
	 */

	//figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
	//		glm::vec2(100.0f, 0.0f), glm::vec2(50.f, 200.0f),
	//		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	jpegRenderer->activate(projection);
	jpegTextureLoader->activate(spriteSheet);

	//std::shared_ptr<SpriteSheet> spriteSheet =
	//		jpegTextureLoader->getSpriteSheet();

	jpegRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 1, 2); //, glm::vec2(0.5f, 0.5f),
	//	glm::vec2(0.75f, 1.0f));
	//jpegRenderer->reset();

	jpegRenderer->renderTriangle(glm::vec2(120.0f, 500.0f),
			glm::vec2(160.0f, 500.0f), glm::vec2(160.f, 600.0f), // triangle
			glm::vec2(0.75f, 0.0f), glm::vec2(0.875f, 0.0f), // texture
			glm::vec2(0.875f, 0.5f));

	jpegRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.0f), // texture
			glm::vec2(0.125f, 0.5f));


	jpegRenderer->renderMultiRectangle(glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);


//	jpegTextureLoader2->activate(spriteSheet2);
	jpegTextureLoader->activate(spriteSheet2);

	//std::shared_ptr<SpriteSheet> spriteSheet2 =
	//	jpegTextureLoader2->getSpriteSheet();

	jpegRenderer->renderRectangle(glm::vec2(400.0f, 400.0f),
			glm::vec2(430.0f, 430.0f), //rectangle
			spriteSheet2, 0, 0);
	//glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f) // texture
	//	);

	//jpegRenderer->reset();

	jpegRenderer->deactivate();

	figuresRenderer->activate(projection);

	//figuresRenderer->temp_render();
	figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
			glm::vec2(100.0f, 0.0f), glm::vec2(50.f, 200.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	figuresRenderer->renderTriangle(glm::vec2(120.0f, 0.0f),
			glm::vec2(220.0f, 0.0f), glm::vec2(170.f, 200.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));


	figuresRenderer->renderRectangle(glm::vec2(200.0f, 200.0f),
			glm::vec2(240.0f, 240.0f),
			glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	figuresRenderer->renderRectangle(glm::vec2(250.0f, 200.0f),
			glm::vec2(290.0f, 240.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));


	figuresRenderer->renderPoint(glm::vec2(300.0f, 400.0f), 8.0f,
			glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	figuresRenderer->renderPoint(glm::vec2(350.0f, 400.0f), 8.0f,
			glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	//figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
	//		glm::vec2(1.0f, 0.0f), glm::vec2(0.5f, 1.0f),
	//		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	figuresRenderer->deactivate();


//	glm::mat4 projection = glm::ortho(0.0f,
//			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
//			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));
	freeTypeRenderer->activate(projection);

	freeTypeRenderer->startRender();
	freeTypeRenderer->renderText("This is sample text", 25.0f, 25.0f, 1.0f,
			glm::vec3(0.5, 0.8f, 0.2f));
	freeTypeRenderer->renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));
	freeTypeRenderer->renderText("Ąą Ćć Ęę Łł Ńń Óó Źź Żż", 0.0f, 0.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));
	// 0.0f, 0.0f -x, y dolny rog ekranu

	freeTypeRenderer->deactivate();

	pngRenderer->activate(projection);
	pngTextureLoader->activate(spriteSheetPng);

	//pngRenderer->temp_activate();
	//pngRenderer->temp_render();

	pngRenderer->renderRectangle(glm::vec2(160.0f, 60.0f),
			glm::vec2(280.0f, 180.0f), spriteSheetPng, 0, 1);

	pngRenderer->renderTriangle(glm::vec2(200.0f, 500.0f),
			glm::vec2(300.0f, 500.0f), glm::vec2(250.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));
	//jpegRenderer->reset();

	//jpegRenderer->renderMultiRectangle(glm::vec2(190.0f, 190.0f),
	//		glm::vec2(380.0f, 380.0f), 1.0f, 1.0f);

	pngRenderer->renderMultiRectangle(glm::vec2(280.0f, 180.0f),
			glm::vec2(580.0f, 380.0f), 2.0f, 1.0f);

	pngRenderer->deactivate();




}

namespace temp_combined_view {
TempCombinedView *openGLview = nullptr;

shared_ptr<TempCombinedView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache) {
	if (openGLview == nullptr) {
		openGLview = new TempCombinedView(resourceCache);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempCombinedView(resourceCache);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempCombinedView> { openGLview };
}
}

} /* namespace base_game */

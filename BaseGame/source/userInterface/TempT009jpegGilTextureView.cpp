/*
 * T008jpegGilTextureView.cpp
 *
 *  Created on: 10 lut 2019
 *      Author: Krzysztof
 */

#include "TempT009jpegGilTextureView.h"
#include "../debugging/Logger.h"
#include "../gameInitialization/VideoSystemGLFW.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/SpriteSheet.h"
#include "../utilities/Templates.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>
#include <memory> // shared_ptr

#include <glm/glm.hpp> // glm::ivec2
#include <glm/gtc/matrix_transform.hpp> // glm::ortho

//#include "../main/vmath.h" // vmath::mat4

// TEMPORARY COMMENTED
#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

using std::shared_ptr;
using std::string;
using std::make_shared;

namespace base_game {

TempT009jpegGilTextureView::TempT009jpegGilTextureView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT009jpegGilTextureView");
	/*
	programID = 0;
	vao = 0; // vertex_array_object
	position_buffer = 0;
	index_buffer = 0;

	//texture = 0;
	uvbuffer = 0;
	 */

	this->shrdPtrResourceCache = resourceCache;

	spriteSheet = make_shared<SpriteSheet>();
	spriteSheet2 = make_shared<SpriteSheet>();

	jpegTextureLoader = new JpegTextureLoader(this->shrdPtrResourceCache);
	//jpegTextureLoader2 = new JpegTextureLoader(this->shrdPtrResourceCache);

	jpegRenderer = make_shared<JpegRenderer>();
}

TempT009jpegGilTextureView::~TempT009jpegGilTextureView() {
	logger::info("Destroy TempT009jpegGilTextureView");
	this->vTerminate();

	jpegRenderer.reset();
	templates::safe_delete<JpegTextureLoader> (jpegTextureLoader);
	//templates::safe_delete<JpegTextureLoader>(jpegTextureLoader2);
	shrdPtrResourceCache.reset();
	spriteSheet2.reset();
	spriteSheet.reset();
}

void TempT009jpegGilTextureView::vTerminate() {
	/*
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &position_buffer);
	glDeleteBuffers(1, &uvbuffer);
	 */

	jpegTextureLoader->terminate();
	//jpegTextureLoader2->terminate();
}

void TempT009jpegGilTextureView::vInit() {
	/*

	 temp_t009_jpeg_gil_texture_view.jpeg
	 136x98

	 temp_g1040.jpg
	 177x103

	 4 obrazki w poziomie
	 1px ramka
	 1px + 43px obrazek + 1px ramka + 43px + 1px + 43px + 1px  + 43px + 1px
	 4 * ( 1 + 43 ) + 1 = 177px

	 2 obrazki w pionie
	 1px ramka + 50px obrazek + 1px + 50px + 1px
	 2 * ( 1 + 50 ) + 1 = 103px

	 */
	
	//jpegTextureLoader2->init("temp_t009_jpeg_gil_texture_view.jpg",
	//		spriteSheet2);
	jpegTextureLoader->init("temp_t009_jpeg_gil_texture_view.jpg",
			spriteSheet2);

	jpegTextureLoader->init("temp_g1040.jpg", spriteSheet);

//	std::shared_ptr<SpriteSheet> spriteSheet =
//			jpegTextureLoader->getSpriteSheet();
	
	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);
	spriteSheet->setRows(2);

	//string vertResourceName = "temp_t009_jpeg_gil_texture_view.vert";
	//string fragResourceName = "temp_t009_jpeg_gil_texture_view.frag";

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	//GLuint programID = shaderCompiler.loadShaders(
	//		"temp_t009_jpeg_gil_texture_view");
	GLuint programID = shaderCompiler.loadShaders(
				"texture_renderer");

	//programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);

	jpegRenderer->init(programID);


	vActivate();
}

void TempT009jpegGilTextureView::vActivate() {
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	jpegTextureLoader->activate();
	// jpegRenderer->activate();

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

}

void TempT009jpegGilTextureView::vDeactivate() {
	HumanView::vDeactivate();

	jpegTextureLoader->deactivate();
	// jpegRenderer->deactivate();
//	jpegTextureLoader2->deactivate();


}

void TempT009jpegGilTextureView::vOnRender(double currentTime,
		float fElapsedTime) {

	//glViewport(0, 0, VideoSystemGLFW::WINDOW_WIDTH,
	//		VideoSystemGLFW::WINDOW_HEIGHT);
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));


	// jpegRenderer->temp_render();
	jpegRenderer->activate(projection);
	jpegTextureLoader->activate(spriteSheet);
	//std::shared_ptr<SpriteSheet> spriteSheet =
	//	jpegTextureLoader->getSpriteSheet();

	//jpegRenderer->activateTexture(spriteSheet.get());


	//int width = spriteSheet->getWidth();
	//int height = spriteSheet->getHeight();

	//jpegRenderer->renderRectangle();
	//jpegRenderer->renderRectangle2();
	//jpegRenderer->renderRectangle3();
	// jpegRenderer->renderTriangle();


	//jpegRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
	//			glm::vec2(180.0f, 180.0f), glm::vec2(0.5f, 0.5f),
	//			glm::vec2(0.75f, 1.0f));


	jpegRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 1, 2); // glm::vec2(0.5f, 0.5f),
	//glm::vec2(0.75f, 1.0f));

//	jpegRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
	//		glm::vec2(180.0f, 180.0f), glm::vec2(0.5f * width, 0.5f * height),
	//	glm::vec2(0.75f * width, 1.0f * height));



	//jpegRenderer->reset();


	jpegRenderer->renderTriangle(glm::vec2(120.0f, 500.0f),
			glm::vec2(160.0f, 500.0f), glm::vec2(160.f, 600.0f), // triangle
			glm::vec2(0.75f, 0.0f), // texture
			glm::vec2(0.875f, 0.0f), glm::vec2(0.875f, 0.5f));
	//jpegRenderer->reset();


	jpegRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));
	//jpegRenderer->reset();


	//jpegRenderer->renderMultiRectangle(glm::vec2(190.0f, 190.0f),
	//		glm::vec2(380.0f, 380.0f), 1.0f, 1.0f);


	jpegRenderer->renderMultiRectangle(glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);


//	jpegTextureLoader2->activate(spriteSheet2);
	jpegTextureLoader->activate(spriteSheet2);


//	std::shared_ptr<SpriteSheet> spriteSheet2 =
	//		jpegTextureLoader2->getSpriteSheet();

	//jpegRenderer->activateTexture(spriteSheet2.get());

	int width2 = spriteSheet2->getWidth();
	int height2 = spriteSheet2->getHeight();

	jpegRenderer->renderRectangle(glm::vec2(400.0f, 400.0f),
			glm::vec2(430.0f, 430.0f), //rectangle
			spriteSheet2, 0, 0);

	//glm::vec2(0.0f, 0.0f), // texture
	//glm::vec2(1.0f, 1.0f)
	//		);

	//jpegRenderer->reset();



	jpegRenderer->deactivate();


}

namespace temp_t009_jpeg_gil_texture_view {
TempT009jpegGilTextureView* openGLview = nullptr;

shared_ptr<TempT009jpegGilTextureView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache) {
	if (openGLview == nullptr) {
		openGLview = new TempT009jpegGilTextureView(resourceCache);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT009jpegGilTextureView(resourceCache);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT009jpegGilTextureView> { openGLview };
}
}

} /* namespace base_game */

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
#include "../graphics3d/OpenGLRenderer.h"
#include "TempUI.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>
#include <memory> // shared_ptr

#include <glm/glm.hpp> // glm::ivec2
#include <glm/gtc/matrix_transform.hpp> // glm::ortho

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

using std::shared_ptr;
using std::string;
using std::make_shared;

namespace base_game {

TempT009jpegGilTextureUI::TempT009jpegGilTextureUI(
		shared_ptr<OpenGLRenderer> openGLRenderer) {
//TempT009jpegGilTextureUI::TempT009jpegGilTextureUI(
//		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT009jpegGilTextureUI");
	this->openGLRenderer = openGLRenderer;

	spriteSheet = make_shared<SpriteSheet>();
	spriteSheet2 = make_shared<SpriteSheet>();

	/*
	 this->shrdPtrResourceCache = resourceCache;

	jpegTextureLoader = new JpegTextureLoader(this->shrdPtrResourceCache);

	jpegRenderer = make_shared<JpegRenderer>();
	shaderCompiler = make_shared<ShaderCompiler>(this->shrdPtrResourceCache);
	 */
}

TempT009jpegGilTextureUI::~TempT009jpegGilTextureUI() {
	logger::info("Destroy TempT009jpegGilTextureUI");
	openGLRenderer.reset();
	vTerminate();
}

void TempT009jpegGilTextureUI::vTerminate() {
	spriteSheet2.reset();
	spriteSheet.reset();

	/*
	if (shaderCompiler) {
	 *
		 * There is some bug in
		 * (Fragment/Vertex)ShaderResourceExtraData::compileShader
		 * so, we need to remove shaders here.
		 * In this way in the method
		 * ResourceCache::getHandle(Resource *resource)
		 * we need to call handle = load(resource); each time we compile shader
		 * load(resource) invokes
		 * FragmentShaderResourceExtraData::compileShader(char *pRawBuffer, uintmax_t rawSize)
		 * and
		 * VertexShaderResourceExtraData::compileShader(char *pRawBuffer, uintmax_t rawSize)
		 * these methods are important to successfully load shader again
		 *
		 * The bug should be fixed and we should not removeShaders("figures_renderer") here
		 * VertexShaderResourceExtraData::compileShader should save results in the cache for further usage
		 *
	 *
		shaderCompiler->removeShaders("texture_renderer");
	} else {
		logger::info("shader compiler destroyed");
	}
	shaderCompiler.reset();

	jpegTextureLoader->terminate();

	jpegRenderer.reset();
	templates::safe_delete<JpegTextureLoader>(jpegTextureLoader);
	shrdPtrResourceCache.reset();
	 */
}

int TempT009jpegGilTextureUI::vGetZOrder() const {
	return 1;
}

void TempT009jpegGilTextureUI::vSetZOrder(int const zOrder) const {
}

void TempT009jpegGilTextureUI::vOnRestore() {
	temp_init_part();
	temp_activate_part();

}

void TempT009jpegGilTextureUI::temp_init_part() {
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

	openGLRenderer->jpegTextureLoader->init(
			"temp_t009_jpeg_gil_texture_view.jpg",
			spriteSheet2);

	openGLRenderer->jpegTextureLoader->init("temp_g1040.jpg", spriteSheet);

	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);
	spriteSheet->setRows(2);

	//ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	/*
	GLuint programID = shaderCompiler->loadShaders("texture_renderer");
	jpegRenderer->init(programID);
	 */
	
	//vActivate();
}

void TempT009jpegGilTextureUI::temp_activate_part() {
	//HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void TempT009jpegGilTextureUI::vOnRender(double fTime, float fElapsedTime) {
	temp_vOnRender(fTime, fElapsedTime);
}

void TempT009jpegGilTextureUI::temp_vOnRender(double fTime,
		float fElapsedTime) {
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	openGLRenderer->jpegRenderer->activate(projection);
	openGLRenderer->jpegTextureLoader->activate(spriteSheet);

	openGLRenderer->jpegRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 1, 2); // glm::vec2(0.5f, 0.5f),

	openGLRenderer->jpegRenderer->renderTriangle(glm::vec2(120.0f, 500.0f),
			glm::vec2(160.0f, 500.0f), glm::vec2(160.f, 600.0f), // triangle
			glm::vec2(0.75f, 0.0f), // texture
			glm::vec2(0.875f, 0.0f), glm::vec2(0.875f, 0.5f));

	openGLRenderer->jpegRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));

	openGLRenderer->jpegRenderer->renderMultiRectangle(
			glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);

	openGLRenderer->jpegTextureLoader->activate(spriteSheet2);

	int width2 = spriteSheet2->getWidth();
	int height2 = spriteSheet2->getHeight();

	openGLRenderer->jpegRenderer->renderRectangle(glm::vec2(400.0f, 400.0f),
			glm::vec2(430.0f, 430.0f), //rectangle
			spriteSheet2, 0, 0);

	openGLRenderer->jpegTextureLoader->deactivate();
	openGLRenderer->jpegRenderer->deactivate();

}

/////

TempT009jpegGilTextureView::TempT009jpegGilTextureView(
		shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer) :
		HumanView(openGLRenderer) {
	logger::info("Create TempT009jpegGilTextureView");

	//tempT009jpegGilTextureUI.reset(new TempT009jpegGilTextureUI(resourceCache));
	tempT009jpegGilTextureUI.reset(
			new TempT009jpegGilTextureUI(openGLRenderer));
	vPushElement(tempT009jpegGilTextureUI);

	/*
	this->shrdPtrResourceCache = resourceCache;

	spriteSheet = make_shared<SpriteSheet>();
	spriteSheet2 = make_shared<SpriteSheet>();

	jpegTextureLoader = new JpegTextureLoader(this->shrdPtrResourceCache);

	jpegRenderer = make_shared<JpegRenderer>();
	 */
}

TempT009jpegGilTextureView::~TempT009jpegGilTextureView() {
	logger::info("Destroy TempT009jpegGilTextureView");
	this->vTerminate();
	tempT009jpegGilTextureUI.reset();

	/*
	jpegRenderer.reset();
	templates::safe_delete<JpegTextureLoader> (jpegTextureLoader);
	shrdPtrResourceCache.reset();
	spriteSheet2.reset();
	spriteSheet.reset();
	 */
}

void TempT009jpegGilTextureView::vTerminate() {
	tempT009jpegGilTextureUI->vTerminate();
	//jpegTextureLoader->terminate();
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
	
	/*
	jpegTextureLoader->init("temp_t009_jpeg_gil_texture_view.jpg",
			spriteSheet2);

	jpegTextureLoader->init("temp_g1040.jpg", spriteSheet);

	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);
	spriteSheet->setRows(2);

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	GLuint programID = shaderCompiler.loadShaders(
				"texture_renderer");
	jpegRenderer->init(programID);

	vActivate();
	 */
}

//void TempT009jpegGilTextureView::vActivate() {
	/*
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);
	 */
//}

//void TempT009jpegGilTextureView::vDeactivate() {
//	HumanView::vDeactivate();

	//jpegTextureLoader->deactivate();
//}

void TempT009jpegGilTextureView::tempVRender(double currentTime,
		float fElapsedTime) {
	/*
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	jpegRenderer->activate(projection);
	jpegTextureLoader->activate(spriteSheet);

	jpegRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 1, 2); // glm::vec2(0.5f, 0.5f),

	jpegRenderer->renderTriangle(glm::vec2(120.0f, 500.0f),
			glm::vec2(160.0f, 500.0f), glm::vec2(160.f, 600.0f), // triangle
			glm::vec2(0.75f, 0.0f), // texture
			glm::vec2(0.875f, 0.0f), glm::vec2(0.875f, 0.5f));

	jpegRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));

	jpegRenderer->renderMultiRectangle(glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);

	jpegTextureLoader->activate(spriteSheet2);

	int width2 = spriteSheet2->getWidth();
	int height2 = spriteSheet2->getHeight();

	jpegRenderer->renderRectangle(glm::vec2(400.0f, 400.0f),
			glm::vec2(430.0f, 430.0f), //rectangle
			spriteSheet2, 0, 0);

	jpegTextureLoader->deactivate();
	jpegRenderer->deactivate();
	 */
}

void TempT009jpegGilTextureView::vOnRender(double currentTime,
		float fElapsedTime) {
	HumanView::vOnRender(currentTime, fElapsedTime);
}

/*
 namespace temp_t009_jpeg_gil_texture_view {
TempT009jpegGilTextureView* openGLview = nullptr;

shared_ptr<TempT009jpegGilTextureView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer) {
	if (openGLview == nullptr) {
		openGLview = new TempT009jpegGilTextureView(resourceCache,
				openGLRenderer);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT009jpegGilTextureView(resourceCache,
					openGLRenderer);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT009jpegGilTextureView> { openGLview };
}
}
 */

} /* namespace base_game */

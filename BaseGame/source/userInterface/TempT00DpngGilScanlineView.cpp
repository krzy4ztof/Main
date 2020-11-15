/*
 * T00DpngGilScanlineView.cpp
 *
 *  Created on: 20 kwi 2019
 *      Author: Krzysztof
 */

#include "TempT00DpngGilScanlineView.h"
#include "../debugging/Logger.h"
#include "../gameInitialization/VideoSystemGLFW.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/TextureRenderer.h"
#include "../utilities/Templates.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "TempUI.h"

#include <GLFW/glfw3.h> // GLFWwindow

#include <glm/gtc/matrix_transform.hpp> // glm::ortho

#include <math.h> // cos, sin
#include <iostream>
#include <string> // std::string
#include <memory> // shared_ptr

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

using std::shared_ptr;
using std::string;
using std::make_shared;

namespace base_game {

TempT00DpngGilScanlineUI::TempT00DpngGilScanlineUI(
		shared_ptr<OpenGLRenderer> openGLRenderer) {
//TempT00DpngGilScanlineUI::TempT00DpngGilScanlineUI(
//		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT00DpngGilScanlineUI");
	this->openGLRenderer = openGLRenderer;
	spriteSheet = make_shared<SpriteSheet>();

	/*
	this->shrdPtrResourceCache = resourceCache;
	pngTextureLoader = new PngTextureLoader(this->shrdPtrResourceCache);

	pngRenderer = make_shared<PngRenderer>();
	shaderCompiler = make_shared<ShaderCompiler>(this->shrdPtrResourceCache);
	 */
}

TempT00DpngGilScanlineUI::~TempT00DpngGilScanlineUI() {
	logger::info("Destroy TempT00DpngGilScanlineUI");
	openGLRenderer.reset();
	vTerminate();

}

void TempT00DpngGilScanlineUI::vTerminate() {
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

	pngRenderer.reset();
	//this->vTerminate();
	pngTextureLoader->terminate();

	templates::safe_delete<PngTextureLoader>(pngTextureLoader);

	shrdPtrResourceCache.reset();
	 */
}

int TempT00DpngGilScanlineUI::vGetZOrder() const {
	return 1;
}

void TempT00DpngGilScanlineUI::vSetZOrder(int const zOrder) const {
}

void TempT00DpngGilScanlineUI::vOnRestore() {
	temp_init_part();
	temp_activate_part();

}

void TempT00DpngGilScanlineUI::temp_init_part() {
	openGLRenderer->pngTextureLoader->init(
			"temp_t00d_png_gil_scanline_view_pools_alpha.png",
			spriteSheet);
	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);

	//ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	/*
	GLuint programID = shaderCompiler->loadShaders("texture_renderer");

	pngRenderer->init(programID);
	 */
	
	//vActivate();
}

void TempT00DpngGilScanlineUI::temp_activate_part() {
	//HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void TempT00DpngGilScanlineUI::vOnRender(double fTime, float fElapsedTime) {
	temp_vOnRender(fTime, fElapsedTime);
}

void TempT00DpngGilScanlineUI::temp_vOnRender(double fTime,
		float fElapsedTime) {
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	openGLRenderer->pngRenderer->activate(projection);
	openGLRenderer->pngTextureLoader->activate(spriteSheet);

	openGLRenderer->pngRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 0, 1);

	openGLRenderer->pngRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));

	openGLRenderer->pngRenderer->renderMultiRectangle(glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);

	openGLRenderer->pngTextureLoader->deactivate();
	openGLRenderer->pngRenderer->deactivate();

}

////

TempT00DpngGilScanlineView::TempT00DpngGilScanlineView(
		shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer) :
		HumanView(openGLRenderer) {
	logger::info("Create T00DpngGilScanlineView");

	//tempT00DpngGilScanlineUI.reset(new TempT00DpngGilScanlineUI(resourceCache));
	tempT00DpngGilScanlineUI.reset(
			new TempT00DpngGilScanlineUI(openGLRenderer));
	vPushElement(tempT00DpngGilScanlineUI);
	/*
	this->shrdPtrResourceCache = resourceCache;
	spriteSheet = make_shared<SpriteSheet>();
	pngTextureLoader = new PngTextureLoader(this->shrdPtrResourceCache);

	pngRenderer = make_shared<PngRenderer>();
	 */
}

TempT00DpngGilScanlineView::~TempT00DpngGilScanlineView() {
	logger::info("Destroy T00DpngGilScanlineView");

	this->vTerminate();
	tempT00DpngGilScanlineUI.reset();
	/*
	pngRenderer.reset();
	this->vTerminate();
	templates::safe_delete<PngTextureLoader>(pngTextureLoader);
	spriteSheet.reset();

	shrdPtrResourceCache.reset();
	 */
}

void TempT00DpngGilScanlineView::vTerminate() {
	tempT00DpngGilScanlineUI->vTerminate();
	//pngTextureLoader->terminate();
}

void TempT00DpngGilScanlineView::vInit() {
	/*
	pngTextureLoader->init("temp_t00d_png_gil_scanline_view_pools_alpha.png",
			spriteSheet);
	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler.loadShaders(
			"texture_renderer");

	pngRenderer->init(programID);

	vActivate();
	 */
}

//void TempT00DpngGilScanlineView::vActivate() {
	/*
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);
	 */
//}

//void TempT00DpngGilScanlineView::vDeactivate() {
//	HumanView::vDeactivate();
	//pngTextureLoader->deactivate();
//}

void TempT00DpngGilScanlineView::tempVRender(double currentTime,
		float fElapsedTime) {
	/*
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	pngRenderer->activate(projection);
	pngTextureLoader->activate(spriteSheet);

	pngRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 0, 1);

	pngRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));

	pngRenderer->renderMultiRectangle(glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);

	pngTextureLoader->deactivate();
	pngRenderer->deactivate();
	 */
}

void TempT00DpngGilScanlineView::vOnRender(double currentTime,
		float fElapsedTime) {
	HumanView::vOnRender(currentTime, fElapsedTime);
}

/*
namespace temp_t00d_png_gil_scanline_view {
TempT00DpngGilScanlineView *openGLview = nullptr;

shared_ptr<TempT00DpngGilScanlineView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer) {
	if (openGLview == nullptr) {
		openGLview = new TempT00DpngGilScanlineView(resourceCache,
				openGLRenderer);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT00DpngGilScanlineView(resourceCache,
					openGLRenderer);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT00DpngGilScanlineView> { openGLview };
}
}
 */

} /* namespace base_game */

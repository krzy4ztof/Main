/*
 * TempT00FpolishFontsView.cpp
 *
 *  Created on: 28 kwi 2019
 *      Author: Krzysztof
 */

#include "TempT00FpolishFontsView.h"

#include "../debugging/Logger.h"
#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/FreeTypeResourceLoader.h"
#include "../graphics3d/FreeTypeCharacter.h"
#include "../graphics3d/FreeTypeRenderer.h"
#include "../graphics3d/OpenGLRenderer.h"

#include "../gameInitialization/VideoSystemGLFW.h"
#include "TempUI.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>
#include <sstream>      // std::stringstream
#include <map> // std::map
#include <string> // std::string
#include <memory> // shared_ptr

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp> // glm::ivec2
#include <glm/gtc/matrix_transform.hpp> // glm::ortho
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "vmath.h" // vmath::mat4

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

using std::map;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::stringstream;

namespace base_game {
TempT00FpolishFontsUI::TempT00FpolishFontsUI(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT00FpolishFontsUI");

	this->shrdPtrResourceCache = resourceCache;
	freeTypeRenderer = make_shared<FreeTypeRenderer>();
	shaderCompiler = make_shared<ShaderCompiler>(this->shrdPtrResourceCache);

}

TempT00FpolishFontsUI::~TempT00FpolishFontsUI() {
	logger::info("Destroy TempT00FpolishFontsUI");
	vTerminate();

}

void TempT00FpolishFontsUI::vTerminate() {
	this->temp_deactivate_part();
	//this->vTerminate();
	if (shaderCompiler) {
		/*
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
		 */
		shaderCompiler->removeShaders("fonts_renderer");
	} else {
		logger::info("shader compiler destroyed");
	}
	shaderCompiler.reset();

	freeTypeRenderer.reset();
	shrdPtrResourceCache.reset();
}

int TempT00FpolishFontsUI::vGetZOrder() const {
	return 1;
}

void TempT00FpolishFontsUI::vSetZOrder(int const zOrder) const {
}

void TempT00FpolishFontsUI::vOnRestore() {
	temp_init_part();
	temp_activate_part();

}

void TempT00FpolishFontsUI::temp_init_part() {
	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters =
			freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();

	//string vertResourceName = "fonts_renderer.vert";
	//string fragResourceName = "fonts_renderer.frag";

	//ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	//GLuint programID = shaderCompiler->loadShaders(vertResourceName,
	//		fragResourceName);
	GLuint programID = shaderCompiler->loadShaders(
			"fonts_renderer");

	freeTypeRenderer->init(programID, characters);
	freeTypeRenderer->debugCharacters();

	//vActivate();
}

void TempT00FpolishFontsUI::temp_activate_part() {
	//HumanView::vActivate();

	/*
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 */
	
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	freeTypeRenderer->activate(projection);
}

void TempT00FpolishFontsUI::temp_deactivate_part() {
	//HumanView::vDeactivate();

	/*
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	 */

	if (freeTypeRenderer) {
		freeTypeRenderer->deactivate();
	}
}


void TempT00FpolishFontsUI::vOnRender(double fTime, float fElapsedTime) {
	temp_vOnRender(fTime, fElapsedTime);
}

void TempT00FpolishFontsUI::temp_vOnRender(double fTime,
		float fElapsedTime) {
	// Clear the colorbuffer

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	freeTypeRenderer->startRender();

	freeTypeRenderer->renderText("This is sample text", 25.0f, 25.0f, 1.0f,
			glm::vec3(0.5, 0.8f, 0.2f));
	freeTypeRenderer->renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));

	freeTypeRenderer->renderText("Ąą Ćć Ęę Łł Ńń Óó Źź Żż", 0.0f, 0.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));

}




////

////

TempT00FpolishFontsView::TempT00FpolishFontsView(
		shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer) :
		HumanView(openGLRenderer) {
	logger::info("Create T00FpolishFontsView");
	tempT00FpolishFontsUI.reset(new TempT00FpolishFontsUI(resourceCache));
	vPushElement(tempT00FpolishFontsUI);

	/*
	this->shrdPtrResourceCache = resourceCache;
	freeTypeRenderer = make_shared<FreeTypeRenderer>();
	 */
}

TempT00FpolishFontsView::~TempT00FpolishFontsView() {
	logger::info("Destroy T00FpolishFontsView");
	this->vTerminate();
	tempT00FpolishFontsUI.reset();
	/*
	this->vTerminate();
	freeTypeRenderer.reset();
	shrdPtrResourceCache.reset();
	 */
}

void TempT00FpolishFontsView::vTerminate() {
	tempT00FpolishFontsUI->vTerminate();
}

void TempT00FpolishFontsView::vInit() {
	/*
	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters =
			freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();

	 string vertResourceName = "fonts_renderer.vert";
	 string fragResourceName = "fonts_renderer.frag";

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler.loadShaders(vertResourceName,
			fragResourceName);

	freeTypeRenderer->init(programID, characters);
	freeTypeRenderer->debugCharacters();
	
	vActivate();
	 */
}


//void TempT00FpolishFontsView::vActivate() {
	/*
	HumanView::vActivate();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	freeTypeRenderer->activate(projection);
	 */
//}

//void TempT00FpolishFontsView::vDeactivate() {
	/*
	HumanView::vDeactivate();

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	freeTypeRenderer->deactivate();
	 */
//}

void TempT00FpolishFontsView::tempVRender(double currentTime,
		float fElapsedTime) {
	// Clear the colorbuffer
	/*
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	freeTypeRenderer->startRender();

	freeTypeRenderer->renderText("This is sample text", 25.0f, 25.0f, 1.0f,
			glm::vec3(0.5, 0.8f, 0.2f));
	freeTypeRenderer->renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));

	freeTypeRenderer->renderText("Ąą Ćć Ęę Łł Ńń Óó Źź Żż", 0.0f, 0.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));
	 */
}

void TempT00FpolishFontsView::vOnRender(double currentTime,
		float fElapsedTime) {
	HumanView::vOnRender(currentTime, fElapsedTime);
}

/*
namespace temp_t00f_polish_fonts_view {
TempT00FpolishFontsView *openGLview = nullptr;

shared_ptr<TempT00FpolishFontsView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer) {
	if (openGLview == nullptr) {
		openGLview = new TempT00FpolishFontsView(resourceCache, openGLRenderer);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT00FpolishFontsView(resourceCache,
					openGLRenderer);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT00FpolishFontsView> { openGLview };
}
}
 */

} /* namespace base_game */


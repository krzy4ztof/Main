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
#include "../graphics3d/OpenGLRenderer.h"
#include "TempUI.h"

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

TempT004figuresUI::TempT004figuresUI(shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT004figuresUI");

	this->shrdPtrResourceCache = resourceCache;
	figuresRenderer = make_shared<FiguresRenderer>();
	shaderCompiler = make_shared<ShaderCompiler>(this->shrdPtrResourceCache);
}

TempT004figuresUI::~TempT004figuresUI() {
	logger::info("Destroy TempT004figuresUI");
	vTerminate();
}

void TempT004figuresUI::vTerminate() {
	stringstream ss;
	ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
	logger::info(ss);
	ss << "shaderCompiler: " << shaderCompiler.use_count();
	logger::info(ss);
	ss << "figuresRenderer: " << figuresRenderer.use_count();
	logger::info(ss);

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

		shaderCompiler->removeShaders("figures_renderer");
	} else {
		logger::info("shader compiler destroyed");
	}
	shaderCompiler.reset();
	figuresRenderer.reset();

	ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
	logger::info(ss);

	shrdPtrResourceCache.reset();

	ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
	logger::info(ss);
	ss << "shaderCompiler: " << shaderCompiler.use_count();
	logger::info(ss);
	ss << "figuresRenderer: " << figuresRenderer.use_count();
	logger::info(ss);

}

int TempT004figuresUI::vGetZOrder() const {
	return 1;
}

void TempT004figuresUI::vSetZOrder(int const zOrder) const {
}

void TempT004figuresUI::vOnRestore() {
	temp_init_part();
	temp_activate_part();

}

void TempT004figuresUI::temp_init_part() {
	stringstream ss;

	//ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler->loadShaders("figures_renderer");
	figuresRenderer->init(programID);

	// vActivate();
}

void TempT004figuresUI::temp_activate_part() {
	//HumanView::vActivate();

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
}

void TempT004figuresUI::vOnRender(double fTime, float fElapsedTime) {
	temp_vOnRender(fTime, fElapsedTime);
}

void TempT004figuresUI::temp_vOnRender(double fTime, float fElapsedTime) {
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	figuresRenderer->activate(projection);

	figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
			glm::vec2(100.0f, 0.0f), glm::vec2(50.f, 200.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	figuresRenderer->renderRectangle(glm::vec2(200.0f, 200.0f),
			glm::vec2(240.0f, 240.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	figuresRenderer->renderPoint(glm::vec2(300.0f, 400.0f), 8.0f,
			glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	figuresRenderer->deactivate();
}

TempT004figuresView::TempT004figuresView(
		shared_ptr<ResourceCache> resourceCache,
		std::shared_ptr<OpenGLRenderer> openGLRenderer) :
		HumanView(openGLRenderer) {
	logger::info("Create TempT004figuresView");

	tempT004figuresUI.reset(new TempT004figuresUI(resourceCache));
	vPushElement(tempT004figuresUI);

	//this->shrdPtrResourceCache = resourceCache;
	//figuresRenderer = make_shared<FiguresRenderer>();

}

TempT004figuresView::~TempT004figuresView() {
	logger::info("Destroy TempT004figuresView");
	this->vTerminate();
	tempT004figuresUI.reset();
	//shrdPtrResourceCache.reset();
	//figuresRenderer.reset();
}

void TempT004figuresView::vTerminate() {
	tempT004figuresUI->vTerminate();
}



void TempT004figuresView::vInit() {
	/*
	stringstream ss;

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler.loadShaders("figures_renderer");
	figuresRenderer->init(programID);

	vActivate();
	 */
}

//void TempT004figuresView::vActivate() {
	/*
	HumanView::vActivate();

	// Dark background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	 */
//}


//void TempT004figuresView::vDeactivate() {
//	HumanView::vDeactivate();
//}


void TempT004figuresView::tempVRender(double currentTime, float fElapsedTime) {
	/*
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	figuresRenderer->activate(projection);

	figuresRenderer->renderTriangle(glm::vec2(0.0f, 0.0f),
			glm::vec2(100.0f, 0.0f), glm::vec2(50.f, 200.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	figuresRenderer->renderRectangle(glm::vec2(200.0f, 200.0f),
			glm::vec2(240.0f, 240.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	figuresRenderer->renderPoint(glm::vec2(300.0f, 400.0f), 8.0f,
			glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	figuresRenderer->deactivate();
	 */
}


void TempT004figuresView::vOnRender(double currentTime, float fElapsedTime) {
	HumanView::vOnRender(currentTime, fElapsedTime);
}

/*
namespace temp_t004_figures_view {
TempT004figuresView* openGLview = nullptr;

shared_ptr<TempT004figuresView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache,
		shared_ptr<OpenGLRenderer> openGLRenderer) {
	if (openGLview == nullptr) {
		openGLview = new TempT004figuresView(resourceCache, openGLRenderer);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT004figuresView(resourceCache, openGLRenderer);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT004figuresView> { openGLview };
}
}
 */

} /* namespace base_game */

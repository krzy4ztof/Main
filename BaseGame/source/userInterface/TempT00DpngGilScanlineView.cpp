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

#include <GLFW/glfw3.h> // GLFWwindow

#include <glm/gtc/matrix_transform.hpp> // glm::ortho

#include <math.h> // cos, sin
#include <iostream>
#include <string> // std::string
#include <memory> // shared_ptr

// TEMPORARY COMMENTED
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

using std::shared_ptr;
using std::string;
using std::make_shared;

namespace base_game {

TempT00DpngGilScanlineView::TempT00DpngGilScanlineView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create T00DpngGilScanlineView");
	/*
	programID = 0;
	vao = 0; // vertex_array_object
	position_buffer = 0;
	index_buffer = 0;

	uvbuffer = 0;
	*/
	// texture = 0;

	this->shrdPtrResourceCache = resourceCache;
	spriteSheet = make_shared<SpriteSheet>();
	pngTextureLoader = new PngTextureLoader(this->shrdPtrResourceCache);

	pngRenderer = make_shared<PngRenderer>();
}

TempT00DpngGilScanlineView::~TempT00DpngGilScanlineView() {
	logger::info("Destroy T00DpngGilScanlineView");

	pngRenderer.reset();
	this->vTerminate();
	templates::safe_delete<PngTextureLoader>(pngTextureLoader);
	spriteSheet.reset();

	shrdPtrResourceCache.reset();
}

void TempT00DpngGilScanlineView::vTerminate() {
	/*
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &position_buffer);
	glDeleteBuffers(1, &uvbuffer);
	 */
	
	pngTextureLoader->terminate();
}

void TempT00DpngGilScanlineView::vInit() {
	pngTextureLoader->init("temp_t00d_png_gil_scanline_view_pools_alpha.png",
			spriteSheet);

	spriteSheet->setMargin(1);
	spriteSheet->setColumns(4);
	// spriteSheet->setRows(2);

	/*
	string vertResourceName = "temp_t00d_png_gil_scanline_view.vert";
	string fragResourceName = "temp_t00d_png_gil_scanline_view.frag";

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);
	 */

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache);
	GLuint programID = shaderCompiler.loadShaders(
			"texture_renderer");

	//	"temp_t00d_png_gil_scanline_view");


	//programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);

	pngRenderer->init(programID);

	/*
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &position_buffer);
	glGenBuffers(1, &index_buffer);
	glGenTextures(1, &texture);
	glGenBuffers(1, &uvbuffer);
	 */
	
	vActivate();
}

void TempT00DpngGilScanlineView::vActivate() {
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	//pngTextureLoader->activate(spriteSheet);

	/*
	glBindVertexArray(vao);


	static const GLushort vertex_indices[] = {
	// square
	// 1-3
	// | |
	// 0-2

			0, 1, 2, //
			2, 1, 3, //
			// triangle
			//  6
			//  ^
			// 4-5
			4, 5, 6, //

			//rectangle
			// 8--10
			// |   |
			// 7---9
			7, 8, 9, //
			9, 8, 10, //
			// bottom rectanglee
			// 12--14
			// |    |
			// 11--13
			11, 12, 13, //
			13, 12, 14 //

			};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices),
			vertex_indices,
			GL_STATIC_DRAW);

	static const GLfloat vertex_positions[] = {
	// square

			-0.25f, -0.25f, 1.0f, //0
			-0.25f, 0.25f, 1.0f, //1
			0.25f, -0.25f, 1.0f, //2
			0.25f, 0.25f, 1.0f, //3

			// triangle
			-1.0f, 0.5f, 1.0f, // 4
			-0.5f, 0.5f, 1.0f, // 5
			-0.75f, 1.0f, 1.0f, // 6

			// rectangle
			-0.75f, -0.75f, 1.0f, // 7
			-0.75, -0.5f, 1.0f, //8
			0.75f, -0.75f, 1.0f, // 9
			0.75f, -0.5f, 1.0f, //10
			// bottom rectangle
			-1.0f, -1.0f, 1.0f, // 11
			-1.0f, -0.8f, 1.0f, // 12
			1.0f, -1.0f, 1.0f, //13
			1.0f, -0.8f, 1.0f //14
			};

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	static const GLfloat g_uv_buffer_data[] = {
	// square
	// 1-3
	// | |
	// 0-2
			0.0f, 0.0f, //0
			0.0f, 1.0f, //1
			1.0f, 0.0f, //2
			1.0f, 1.0f, //3
			// triangle
			//  6
			//  ^
			// 4-5
			// triangle
			0.0f, 0.0f, // 4
			1.0f, 0.0f, // 5
			0.5f, 1.0f, // 6

			//rectangle
			// 8--10
			// |   |
			// 7---9
			// rectangle - 3 texture squares
			0.0f, 0.0f, //7
			0.0f, 1.0f, //8
			3.0f, 0.0f, //9 // where 3.0 - 3 texture squares
			3.0f, 1.0f, //10
			// bottom rectangle
			// 12--14
			// |    |
			// 11--13
			// bottom rectangle - 2 texture triangles
			0.0f, 0.0f, //11
			0.0f, 1.0f, //12
			2.0f, 0.0f, //13 // where 2.0 - 2 texture squares
			2.0f, 1.0f //14
			};

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data,
	GL_STATIC_DRAW);

	glVertexAttribPointer(1, // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	glEnableVertexAttribArray(1);

	glUseProgram(programID);
	 */
}

void TempT00DpngGilScanlineView::vDeactivate() {
	HumanView::vDeactivate();

	pngTextureLoader->deactivate();

	/*
	glBindTexture(GL_TEXTURE_2D, 0);            //TO REMOVE patrz TempT009jpeg..

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);
	 */
}

void TempT00DpngGilScanlineView::vOnRender(double currentTime,
		float fElapsedTime) {

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	// jpegRenderer->temp_render();
	pngRenderer->activate(projection);
	pngTextureLoader->activate(spriteSheet);

	//pngRenderer->temp_activate();
	//pngRenderer->temp_render();

	pngRenderer->renderRectangle(glm::vec2(60.0f, 60.0f),
			glm::vec2(180.0f, 180.0f), spriteSheet, 0, 1);

	pngRenderer->renderTriangle(glm::vec2(0.0f, 500.0f),
			glm::vec2(100.0f, 500.0f), glm::vec2(50.f, 600.0f), // triangle
			glm::vec2(0.0f, 0.0f), // texture
			glm::vec2(0.25f, 0.0f), glm::vec2(0.125f, 0.5f));
	//jpegRenderer->reset();

	//jpegRenderer->renderMultiRectangle(glm::vec2(190.0f, 190.0f),
	//		glm::vec2(380.0f, 380.0f), 1.0f, 1.0f);

	pngRenderer->renderMultiRectangle(glm::vec2(180.0f, 180.0f),
			glm::vec2(480.0f, 380.0f), 2.0f, 5.0f);

	pngRenderer->deactivate();


}

/*
 void TempT00DpngGilScanlineView::vOnRender(double currentTime,
 float fElapsedTime) {
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glViewport(0, 0, VideoSystemGLFW::WINDOW_WIDTH,
			VideoSystemGLFW::WINDOW_HEIGHT);

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// square, triangle, rectangle, bottom rectangle
	glDrawElements(GL_TRIANGLES, 2 * 3 + 3 + 2 * 3 + 2 * 3, GL_UNSIGNED_SHORT,
			0);
}
 */

namespace temp_t00d_png_gil_scanline_view {
TempT00DpngGilScanlineView *openGLview = nullptr;

shared_ptr<TempT00DpngGilScanlineView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache) {
	if (openGLview == nullptr) {
		openGLview = new TempT00DpngGilScanlineView(resourceCache);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT00DpngGilScanlineView(resourceCache);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT00DpngGilScanlineView> { openGLview };
}
}

} /* namespace base_game */

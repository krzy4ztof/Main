/*
 * T008jpegGilTextureView.cpp
 *
 *  Created on: 10 lut 2019
 *      Author: Krzysztof
 */

#include "TempT009jpegGilTextureView.h"
#include "../debugging/Logger.h"
//#include "../main/OpenGLShader.h"
//#include "TempShader.hpp"

// #include "../main/OpenGLwithGLFW.h"
#include "../gameInitialization/VideoSystemGLFW.h"
#include "../graphics3D/ShaderResourceLoader.h"
#include "../graphics3D/TextureResourceLoader.h"
#include "../utilities/Templates.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>

//#include "../main/vmath.h" // vmath::mat4

// TEMPORARY COMMENTED
#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

//using std::cout;
//using std::endl;
using std::shared_ptr;
using std::string;

namespace base_game {

TempT009jpegGilTextureView::TempT009jpegGilTextureView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TempT009jpegGilTextureView");
	// cout << "Create TempT009jpegGilTextureView" << endl;
	programID = 0;
	vao = 0; // vertex_array_object
	position_buffer = 0;
	index_buffer = 0;

	//texture = 0;
	uvbuffer = 0;

	this->shrdPtrResourceCache = resourceCache;
	jpgTextureLoader = new JpgTextureLoader(this->shrdPtrResourceCache);

}

TempT009jpegGilTextureView::~TempT009jpegGilTextureView() {
	logger::info("Destroy TempT009jpegGilTextureView");
	// cout << "Destroy TempT009jpegGilTextureView" << endl;
	this->vTerminate();

	templates::safe_delete<JpgTextureLoader> (jpgTextureLoader);
	shrdPtrResourceCache.reset();
}

void TempT009jpegGilTextureView::vTerminate() {
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &position_buffer);
	glDeleteBuffers(1, &uvbuffer);

	jpgTextureLoader->terminate();
//	glDeleteTextures(1, &texture);

}

void TempT009jpegGilTextureView::vInit() {
	//testCopyImage();
	//jpgTextureLoader textureLoader(this->shrdPtrResourceCache);
	jpgTextureLoader->init("temp_t009_jpeg_gil_texture_view.jpg");


	string vertResourceName = "temp_t009_jpeg_gil_texture_view.vert";
	string fragResourceName = "temp_t009_jpeg_gil_texture_view.frag";

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);

	/*
	programID = LoadShaders(
			"../Watermill/assets/shaders/temp_t009_jpeg_gil_texture_view.vert",
			"../Watermill/assets/shaders/temp_t009_jpeg_gil_texture_view.frag");
	 */

	/*
	programID = LoadShaders(
			"../../../assets/shaders/TempT009jpegGilTextureView.vert",
			"../../../assets/shaders/TempT009jpegGilTextureView.frag");
	 
	 */

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &position_buffer);
	glGenBuffers(1, &index_buffer);
	//glGenBuffers(1, &color_buffer);
	//glGenTextures(1, &texture); // -> textureLoader.init()
	glGenBuffers(1, &uvbuffer);

	vActivate();
}

void TempT009jpegGilTextureView::vActivate() {
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	jpgTextureLoader->activate();

	/*
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, texture);
	// Specify the amount of storage we want to use for the texture

	int img_width = rgb8_image.width();
	int img_height = rgb8_image.height();

	//const int texSize = 100; //128
	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			img_width, img_height);       // 256 x 256 texels


	float * data = new float[img_width * img_height * 4];

	// generate_texture() is a function that fills memory with image data
	//generate_texture(data, texSize, texSize);

	image_to_texture(data);

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			img_width, img_height,     // 256 x 256 texels, replace entire image
			GL_RGBA,        // Four channel data
			GL_FLOAT, // Floating point data
			//GL_INT,       // Floating point data
			data);       //

	// Free the memory we allocated before - \GL now has our data
	delete[] data;
	// STOP TEXTURE
	 */

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

	//GLuint uvbuffer;
	//glGenBuffers(1, &uvbuffer);
	//glEnableVertexAttribArray(1);
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
}

/*
void TempT009jpegGilTextureView::vActivateOK_jpeg() {
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, texture);
	// Specify the amount of storage we want to use for the texture

	int img_width = rgb8_image.width();
	int img_height = rgb8_image.height();

	//const int texSize = 100; //128
	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			img_width, img_height);       // 256 x 256 texels

	float * data = new float[img_width * img_height * 4];

	// generate_texture() is a function that fills memory with image data
	//generate_texture(data, texSize, texSize);

	image_to_texture(data);

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			img_width, img_height,     // 256 x 256 texels, replace entire image
			GL_RGBA,        // Four channel data
			GL_FLOAT, // Floating point data
			//GL_INT,       // Floating point data
			data);       //

	// Free the memory we allocated before - \GL now has our data
	delete[] data;
	// STOP TEXTURE

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

	//GLuint uvbuffer;
	//glGenBuffers(1, &uvbuffer);
	//glEnableVertexAttribArray(1);
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
}
 */

/*
void TempT009jpegGilTextureView::vActivateOK() {
	HumanView::vActivate();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, texture);
	// Specify the amount of storage we want to use for the texture

	const int texSize = 48; //128
	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			texSize, texSize);       // 256 x 256 texels

	// Define some data to upload into the texture
	float * data = new float[texSize * texSize * 4];

	// generate_texture() is a function that fills memory with image data
	// generate_texture(data, texSize, texSize);

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			texSize, texSize,       // 256 x 256 texels, replace entire image
			GL_RGBA,        // Four channel data
			GL_FLOAT,       // Floating point data
			data);          // Pointer to data

	// Free the memory we allocated before - \GL now has our data
	delete[] data;
	// STOP TEXTURE

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

	//GLuint uvbuffer;
	//glGenBuffers(1, &uvbuffer);
	//glEnableVertexAttribArray(1);
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
}
 */


void TempT009jpegGilTextureView::vDeactivate() {
	HumanView::vDeactivate();

	//glBindTexture(GL_TEXTURE_2D, 0);
	jpgTextureLoader->deactivate();

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);
}

/*
	// TEMPORARY COMMENTED
	namespace bg = boost::gil;

	bg::read_image(
			"../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view.jpg",
			rgb8_image, bg::jpeg_tag { });
//	bg::read_image("../../../assets/graphics/TempT009jpegGilTextureView.jpg",
	//			rgb8_image, bg::jpeg_tag { });

	cout << "Width: " << rgb8_image.width() << "; Height: "
			<< rgb8_image.height() << endl;
	// Width: 136; Height: 98

	bg::rgb8_pixel_t px = *const_view(rgb8_image).at(5, 10);
	cout << "The pixel at 5,10 is " << (int) px[0] << ',' << (int) px[1] << ','
			<< (int) px[2] << endl;

	// Scale the image to 100x100 pixels using bilinear resampling
	bg::rgb8_image_t square100x100(100, 100);

	bg::resize_view(bg::const_view(rgb8_image), bg::view(square100x100),
			bg::bilinear_sampler { });

	bg::write_view(
			"../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view-resized.jpg",
			bg::const_view(square100x100), bg::jpeg_tag { });
}
 */

void TempT009jpegGilTextureView::vOnRender(double currentTime,
		float fElapsedTime) {
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	//glViewport(0, 0, OpenGLwithGLFW::WINDOW_WIDTH,
	//		OpenGLwithGLFW::WINDOW_HEIGHT);
	glViewport(0, 0, VideoSystemGLFW::WINDOW_WIDTH,
			VideoSystemGLFW::WINDOW_HEIGHT);

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	//glUseProgram (programID);

	// square, triangle, rectangle, bottom rectangle
	glDrawElements(GL_TRIANGLES, 2 * 3 + 3 + 2 * 3 + 2 * 3, GL_UNSIGNED_SHORT,
			0);
	// glDrawElements(GL_TRIANGLES, 2 * 3 + 3, GL_UNSIGNED_SHORT, 0);

}

/*
void TempT009jpegGilTextureView::image_to_texture(float * data) {
	namespace bg = boost::gil;
	int img_width = rgb8_image.width();
	int img_height = rgb8_image.height();

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			bg::rgb8_pixel_t px = *const_view(rgb8_image).at(x, y);

			data[((img_height - y - 1) * img_width + x) * 4 + 0] = (float) px[0]
					/ 255;
			data[((img_height - y - 1) * img_width + x) * 4 + 1] = (float) px[1]
					/ 255;
			data[((img_height - y - 1) * img_width + x) * 4 + 2] = (float) px[2]
					/ 255;
			data[((img_height - y - 1) * img_width + x) * 4 + 3] = 1.0f;

		}
	}

}
 */

/*
void TempT009jpegGilTextureView::generate_texture(float * data, int width,
		int height) {
	int x, y;

	for (y = 0; y < 32; y++) {
		for (x = 0; x < 32; x++) {
			data[(y * width + x) * 4 + 0] = 0.0f;
			data[(y * width + x) * 4 + 1] = 1.0f; // GREEN
			data[(y * width + x) * 4 + 2] = 0.0f;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}

	for (y = 0; y < 32; y++) {
		for (x = 32; x < width; x++) {
			data[(y * width + x) * 4 + 0] = 1.0f; // RED
			data[(y * width + x) * 4 + 1] = 1.0f; // GREEN = YELLOW
			data[(y * width + x) * 4 + 2] = 0.0f;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}

	for (y = 32; y < height; y++) {
		for (x = 0; x < 32; x++) {
			data[(y * width + x) * 4 + 0] = 0.0f;
			data[(y * width + x) * 4 + 1] = 0.0f;
			data[(y * width + x) * 4 + 2] = 1.0f; // BLUE
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}

	for (y = 32; y < height; y++) {
		for (x = 32; x < width; x++) {
			data[(y * width + x) * 4 + 0] = 0.0f;
			data[(y * width + x) * 4 + 1] = 1.0f; // GREEN
			data[(y * width + x) * 4 + 2] = 0.0f;
			data[(y * width + x) * 4 + 3] = 1.0f;
		}
	}

}
 */

namespace temp_t009_jpeg_gil_texture_view {
TempT009jpegGilTextureView* openGLview = nullptr;

//TempT009jpegGilTextureView* getView(bool reset,
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

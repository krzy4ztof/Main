/*
 * JpegRenderer.cpp
 *
 *  Created on: 8 gru 2019
 *      Author: Krzysztof
 */

#include "TextureRenderer.h"
#include "../debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint, GLsizeiptr

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <memory> // shared_ptr
#include <glm/glm.hpp> // glm::ivec2, glm:mat4

using std::shared_ptr;
using glm::vec2;

namespace base_game {

TextureRenderer::TextureRenderer() {
	logger::info("Create TextureRenderer");
	programID = 0;
	vao = 0; // vertex_array_object
	position_buffer = 0;
	index_buffer = 0;

	uvbuffer = 0;
}

TextureRenderer::~TextureRenderer() {
	logger::info("Destroy TextureRenderer");

	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &position_buffer);
	glDeleteBuffers(1, &uvbuffer);
}

void TextureRenderer::init(GLuint programID) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &position_buffer);
	glGenBuffers(1, &index_buffer);
	glGenBuffers(1, &uvbuffer);

	this->programID = programID;
}

void TextureRenderer::activate(glm::mat4 projection) {
	glUseProgram(programID);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1,
	GL_FALSE, glm::value_ptr(projection));
}

void TextureRenderer::deactivate() {
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);
}

void TextureRenderer::activateFigure(const GLushort *vertex_indices,
		GLsizeiptr vertex_indices_size, const GLfloat *vertex_positions,
		GLsizeiptr vertex_positions_size, const GLfloat *g_uv_buffer_data,
		GLsizeiptr g_uv_buffer_data_size) {
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_indices_size,
			vertex_indices,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_positions_size, vertex_positions,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, g_uv_buffer_data_size, g_uv_buffer_data,
	GL_STATIC_DRAW);

	glVertexAttribPointer(1, // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	glEnableVertexAttribArray(1);

}

void TextureRenderer::renderRectangle(glm::vec2 zeroPoint,
		glm::vec2 thrdPoint,
		shared_ptr<SpriteSheet> spriteSheet, int spriteRow,
		int spriteCol) {

	glm::vec2 zeroPointTexture = spriteSheet->getZeroPoint(spriteRow,
			spriteCol);
	glm::vec2 thrdPointTexture = spriteSheet->getThrdPoint(spriteRow,
			spriteCol);

	this->activateRectangle(zeroPoint, thrdPoint, zeroPointTexture,
			thrdPointTexture);
	glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_SHORT, 0);

}

void TextureRenderer::renderMultiRectangle(glm::vec2 zeroPoint,
		glm::vec2 thrdPoint, GLfloat numberX, GLfloat numberY) {
	this->activateRectangle(zeroPoint, thrdPoint, glm::vec2(0.0f, 0.0f),
			glm::vec2(numberX, numberY));
	glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_SHORT, 0);
}


void TextureRenderer::renderTriangle(glm::vec2 zeroPoint, glm::vec2 fstPoint,
		glm::vec2 secPoint, glm::vec2 zeroPointTexture,
		glm::vec2 fstPointTexture, glm::vec2 secPointTexture) {
	this->activateTriangle(zeroPoint, fstPoint, secPoint, zeroPointTexture,
			fstPointTexture, secPointTexture);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

void TextureRenderer::activateTriangle(glm::vec2 zeroPoint, glm::vec2 fstPoint,
		glm::vec2 secPoint, glm::vec2 zeroPointTexture,
		glm::vec2 fstPointTexture, glm::vec2 secPointTexture) {

	const GLushort vertex_indices[] = {
	// triangle
	//  2
	//  ^
	// 0-1
			0, 1, 2 //
			};

	const GLfloat vertex_positions[] = {
	// triangle
			zeroPoint.x, zeroPoint.y, 1.0f, // 0
			fstPoint.x, fstPoint.y, 1.0f, // 1
			secPoint.x, secPoint.y, 1.0f // 2
			};

	const GLfloat g_uv_buffer_data[] = {
	// triangle
	//  2
	//  ^
	// 0-1
	// triangle
			zeroPointTexture.x, zeroPointTexture.y, // 0
			fstPointTexture.x, fstPointTexture.y, // 1
			secPointTexture.x, secPointTexture.y // 2
			};

	this->activateFigure(vertex_indices, sizeof(vertex_indices),
			vertex_positions, sizeof(vertex_positions), g_uv_buffer_data,
			sizeof(g_uv_buffer_data));

}

void TextureRenderer::activateRectangle(glm::vec2 zeroPoint,
		glm::vec2 thrdPoint,
		glm::vec2 zeroPointTexture, glm::vec2 thrdPointTexture) {

	// 	static const GLushort vertex_indices[] = {
	const GLushort vertex_indices[] = {
	// square
	// 1-3
	// | |
	// 0-2

			0, 1, 2, //
			2, 1, 3 //
			};

	const GLfloat vertex_positions[] = { zeroPoint.x, zeroPoint.y, 1.0f, // 0
			zeroPoint.x, thrdPoint.y, 1.0f, // 1
	thrdPoint.x, zeroPoint.y, 1.0f,//2
			thrdPoint.x, thrdPoint.y, 1.0f // 3
			};

	const GLfloat g_uv_buffer_data[] = {
	// square
	// 1-3
	// | |
	// 0-2
			zeroPointTexture.x, zeroPointTexture.y, //0
			zeroPointTexture.x, thrdPointTexture.y, //1 // where numberY - numberY texture squares
			thrdPointTexture.x, zeroPointTexture.y, //2 // where numberX - numberX texture squares
			thrdPointTexture.x, thrdPointTexture.y //3
			};

	this->activateFigure(vertex_indices, sizeof(vertex_indices),
			vertex_positions, sizeof(vertex_positions), g_uv_buffer_data,
			sizeof(g_uv_buffer_data));

}

PngRenderer::PngRenderer() {
	logger::info("Create PngRenderer");

}

PngRenderer::~PngRenderer() {
	logger::info("Destroy PngRenderer");
}

void PngRenderer::activate(glm::mat4 projection) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	TextureRenderer::activate(projection);
}

void PngRenderer::deactivate() {
	glDisable(GL_BLEND);

	TextureRenderer::deactivate();
}

JpegRenderer::JpegRenderer() {
	logger::info("Create JpegRenderer");
}

JpegRenderer::~JpegRenderer() {
	logger::info("Destroy JpegRenderer");
}


void PngRenderer::temp_render() {
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// square, triangle, rectangle, bottom rectangle
	glDrawElements(GL_TRIANGLES, 2 * 3 + 3 + 2 * 3 + 2 * 3, GL_UNSIGNED_SHORT,
			0);
}

void PngRenderer::temp_activate() {

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
}

void JpegRenderer::temp_activate() {
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
			// bottom rectangle
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
}

void JpegRenderer::temp_render() {
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;


	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// square, triangle, rectangle, bottom rectangle
	glDrawElements(GL_TRIANGLES, 2 * 3 + 3 + 2 * 3 + 2 * 3, GL_UNSIGNED_SHORT,
			0);
}

} /* namespace base_game */

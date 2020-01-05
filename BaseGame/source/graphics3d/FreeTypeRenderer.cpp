/*
 * FreeTypeRenderer.cpp
 *
 *  Created on: 18 lis 2019
 *      Author: Krzysztof
 */

#include "FreeTypeRenderer.h"
#include "FreeTypeCharacter.h"
#include "../debugging/Logger.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <map> // std::map
#include <memory> // shared_ptr
#include <string> // std::string
#include <sstream>      // std::stringstream

using std::map;
using std::shared_ptr;
using std::string;
using std::stringstream;

namespace base_game {

//FreeTypeRenderer::FreeTypeRenderer(
//	shared_ptr<map<GLushort, FreeTypeCharacter>> characters) {
FreeTypeRenderer::FreeTypeRenderer() {

	logger::info("Create FreeTypeRenderer");
	//this->characters = characters;

	programID = 0;
	VAO = 0;
	VBO = 0;

}



FreeTypeRenderer::~FreeTypeRenderer() {
	logger::info("Destroy FreeTypeRenderer");
	this->terminate();
}

void FreeTypeRenderer::terminate() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &VBO);
}


void FreeTypeRenderer::init(GLuint programID,
		std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	this->programID = programID;
	this->characters = characters;
}

void FreeTypeRenderer::activate(glm::mat4 projection) {

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
	 glEnable(GL_CULL_FACE);
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 */

	// Tylko dolna cwiartka ekranu
	//glm::mat4 projection = glm::ortho(0.0f,
	//static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_WIDTH * 2), 0.0f,
	//static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_HEIGHT * 2));
	/*
	 glm::mat4 projection = glm::ortho(0.0f,
	 static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
	 static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));
	 */

	// porownac z:
	//glViewport(0, 0, VideoSystemGLFW::WINDOW_WIDTH,
	//	VideoSystemGLFW::WINDOW_HEIGHT);
	glUseProgram(programID);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1,
	GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
	GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void FreeTypeRenderer::deactivate() {
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	/*
	 HumanView::vDeactivate();

	 glDisable(GL_CULL_FACE);
	 glDisable(GL_BLEND);
	 */

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glUseProgram(0);
}


void FreeTypeRenderer::renderLetter(FreeTypeCharacter ch, GLfloat &x,
		GLfloat y, GLfloat scale) {

	GLfloat xpos = x + ch.Bearing.x * scale;
	GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

	GLfloat w = ch.Size.x * scale;
	GLfloat h = ch.Size.y * scale;
	// Update VBO for each character
	GLfloat vertices[6][4] = { { xpos, ypos + h, 0.0, 0.0 }, { xpos, ypos, 0.0,
			1.0 }, { xpos + w, ypos, 1.0, 1.0 },

	{ xpos, ypos + h, 0.0, 0.0 }, { xpos + w, ypos, 1.0, 1.0 }, { xpos + w, ypos
			+ h, 1.0, 0.0 } };
	// Render glyph texture over quad
	glBindTexture(GL_TEXTURE_2D, ch.TextureID);
	// Update content of VBO memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
	x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
}

GLubyte FreeTypeRenderer::renderUShortLetter(GLubyte charC,
		GLubyte prevChar, GLfloat &x, GLfloat y, GLfloat scale) {

	stringstream ss;

	ss << "charC: " << std::hex << (GLushort) charC << "; prevChar: "
			<< (GLushort) prevChar; // << endl;
	logger::info(ss);

	GLushort shortC = prevChar * 0x100 + charC;

	ss << "renderUshort -> shortC: " << std::hex << shortC << std::dec;
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;

	FreeTypeCharacter ch;
	it = characters->find(shortC);

	if (it == characters->end()) {
		ch = characters->at(0x00);
	} else {
		ch = it->second;
	}

	this->renderLetter(ch, x, y, scale);

	return 0x00;
}

GLubyte FreeTypeRenderer::renderUByteLetter(GLubyte charC, GLfloat &x,
		GLfloat y, GLfloat scale) {
	stringstream ss;

	FreeTypeCharacter ch;
	if (charC >= 0 && charC < FreeTypeCharacter::MAX_STD_CHAR) {
		ch = characters->at(charC);
		this->renderLetter(ch, x, y, scale);
		//x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)

	} else if (charC == 0xc3) {
		logger::info("0xc3");
		return charC;
	} else if (charC == 0xc4) {
		logger::info("0xc4");
		return charC;
	} else if (charC == 0xc5) {
		logger::info("0xc5");
		return charC;
	} else {

		ss << charC << ": " << std::hex << (short) charC << std::dec << " |"
				<< (charC) << "|";
		logger::info(ss);
	}
	return 0x00;
}

void FreeTypeRenderer::startRender() {
	glUseProgram(programID);
}

void FreeTypeRenderer::renderText(std::string text, GLfloat x, GLfloat y,
		GLfloat scale, glm::vec3 color) {
	// Activate corresponding render state
	//s.Use();
	glUniform3f(glGetUniformLocation(programID, "textColor"), color.x, color.y,
			color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray (VAO);

	// Iterate through all characters
	std::string::const_iterator c;

	GLubyte prevChar = 0x00;

	for (c = text.begin(); c != text.end(); c++) {

		GLubyte charC = (*c);
		if (charC == 0xc3) {
			logger::info("charC - 0xc3");
		} else if (charC == 0xc4) {
			logger::info("charC - 0xc4");
		} else if (charC == 0xc5) {
			logger::info("charC - 0xc5");
		}

		GLushort shortC = (*c);
		if (shortC == 0xffc3) {
			logger::info("shortC - 0xffc3");
		} else if (shortC == 0xffc4) {
			logger::info("shortC - 0xffc4");
		} else if (shortC == 0xffc5) {
			logger::info("shortC - 0xffc5");
		}

		if (prevChar == 0xc3 || prevChar == 0xc4 || prevChar == 0xc5) {
			prevChar = this->renderUShortLetter(charC, prevChar, x, y, scale);
		} else {
			prevChar = this->renderUByteLetter(charC, x, y, scale);

		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FreeTypeRenderer::debugCharacters() {
	stringstream ss;
	logger::info("--------- DEBUG START FreeTypeRenderer -------");

	ss << "debug: " << characters->size();
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;
	for (it = characters->begin(); it != characters->end(); ++it) {
		ss << "Key: " << std::hex << it->first; // << endl;
		logger::info(ss);

	}

	logger::info("--------- DEBUG END FreeTypeRenderer -------");
}

} /* namespace base_game */

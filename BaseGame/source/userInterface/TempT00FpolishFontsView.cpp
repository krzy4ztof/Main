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

#include "../gameInitialization/VideoSystemGLFW.h"

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

// TEMPORARY COMMENTED
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

// const GLubyte TempT00FpolishFontsView::MAX_STD_CHAR = 128;

TempT00FpolishFontsView::TempT00FpolishFontsView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create T00FpolishFontsView");
	//programID = 0;

	/*

	 VAO = 0;
	 VBO = 0;
	 */

	this->shrdPtrResourceCache = resourceCache;

	freeTypeRenderer = make_shared<FreeTypeRenderer>();
}

/*
 TempT00FpolishFontsView::TempT00FpolishFontsView(
 shared_ptr<ResourceCache> resourceCache) {
 logger::info("Create T00FpolishFontsView");
	programID = 0;
	VAO = 0;
	VBO = 0;

	this->shrdPtrResourceCache = resourceCache;
}
 */

/*
TempT00FpolishFontsView::~TempT00FpolishFontsView() {
	logger::info("Destroy T00FpolishFontsView");
	// cout << "Destroy T00FpolishFontsView" << endl;
	this->vTerminate();
	freeTypeRenderer.reset();
	shrdPtrResourceCache.reset();
	characters.reset();
}
 */

TempT00FpolishFontsView::~TempT00FpolishFontsView() {
	logger::info("Destroy T00FpolishFontsView");
	// cout << "Destroy T00FpolishFontsView" << endl;
	this->vTerminate();
	freeTypeRenderer.reset();
	shrdPtrResourceCache.reset();
	//characters.reset();
}

void TempT00FpolishFontsView::vTerminate() {
//	glDeleteVertexArrays(1, &VAO);
	// glDeleteProgram(programID);
	//glDeleteBuffers(1, &VBO);
}


/*
void TempT00FpolishFontsView::vTerminate() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &VBO);
}
 */

/*
void TempT00FpolishFontsView::debugCharacters() {
	stringstream ss;
	logger::info("--------- DEBUG START TempT00FpolishFontsView -------");

	ss << "debug: " << characters->size();
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;
	for (it = characters->begin(); it != characters->end(); ++it) {
		ss << "Key: " << std::hex << it->first; // << endl;
		logger::info(ss);

	}

	logger::info("--------- DEBUG END TempT00FpolishFontsView -------");
}
 */

/*
 void TempT00FpolishFontsView::vInit() {
 FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
 characters = freeTypeLoader.initFreetype();
 freeTypeLoader.debugCharacters();

 this->debugCharacters();

 //freeTypeRenderer = make_shared<FreeTypeRenderer>(characters);


 glGenVertexArrays(1, &VAO);
 glGenBuffers(1, &VBO);

 string vertResourceName = "temp_t00f_polish_fonts_view.vert";
 string fragResourceName = "temp_t00f_polish_fonts_view.frag";

 ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
 programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);

 vActivate();
 }
 */

void TempT00FpolishFontsView::vInit() {
	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters =
			freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();

	//this->debugCharacters();

	//freeTypeRenderer = make_shared<FreeTypeRenderer>(characters);
	



//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);

	string vertResourceName = "temp_t00f_polish_fonts_view.vert";
	string fragResourceName = "temp_t00f_polish_fonts_view.frag";

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	GLuint programID = shaderCompiler.loadShaders(vertResourceName,
			fragResourceName);

	freeTypeRenderer->init(programID, characters);
	freeTypeRenderer->debugCharacters();
	
	vActivate();
}


void TempT00FpolishFontsView::vActivate() {
	HumanView::vActivate();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Tylko dolna cwiartka ekranu
	//glm::mat4 projection = glm::ortho(0.0f,
	//static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_WIDTH * 2), 0.0f,
	//static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_HEIGHT * 2));

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	// porownac z:
	//glViewport(0, 0, VideoSystemGLFW::WINDOW_WIDTH,
	//	VideoSystemGLFW::WINDOW_HEIGHT);

	freeTypeRenderer->activate(projection);

	/*
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
	 */
}

/*
 void TempT00FpolishFontsView::vActivate() {
 HumanView::vActivate();

 glEnable(GL_CULL_FACE);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 // Tylko dolna cwiartka ekranu
 //glm::mat4 projection = glm::ortho(0.0f,
 //static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_WIDTH * 2), 0.0f,
 //static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_HEIGHT * 2));

	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

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
 */

/*
void TempT00FpolishFontsView::RenderLetter(FreeTypeCharacter ch, GLfloat &x,
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

GLubyte TempT00FpolishFontsView::RenderUShortLetter(GLubyte charC,
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

	this->RenderLetter(ch, x, y, scale);

	return 0x00;
}

GLubyte TempT00FpolishFontsView::RenderUByteLetter(GLubyte charC, GLfloat &x,
		GLfloat y, GLfloat scale) {
	stringstream ss;

	FreeTypeCharacter ch;
	if (charC >= 0 && charC < MAX_STD_CHAR) {
		ch = characters->at(charC);
		this->RenderLetter(ch, x, y, scale);
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

void TempT00FpolishFontsView::RenderText(std::string text, GLfloat x, GLfloat y,
		GLfloat scale, glm::vec3 color) {
	// Activate corresponding render state
	//s.Use();
	glUniform3f(glGetUniformLocation(programID, "textColor"), color.x, color.y,
			color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

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
			prevChar = this->RenderUShortLetter(charC, prevChar, x, y, scale);
		} else {
			prevChar = this->RenderUByteLetter(charC, x, y, scale);

		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
 */


void TempT00FpolishFontsView::vDeactivate() {
	HumanView::vDeactivate();

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	freeTypeRenderer->deactivate();
	/*
	 glBindVertexArray(0);
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glDisableVertexAttribArray(0);

	 glUseProgram(0);
	 */
}

/*
 void TempT00FpolishFontsView::vDeactivate() {
 HumanView::vDeactivate();

 glDisable(GL_CULL_FACE);
 glDisable(GL_BLEND);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glUseProgram(0);
}
 */

void TempT00FpolishFontsView::vOnRender(double currentTime,
		float fElapsedTime) {
	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	freeTypeRenderer->startRender();
	//glUseProgram(programID);

	freeTypeRenderer->renderText("This is sample text", 25.0f, 25.0f, 1.0f,
			glm::vec3(0.5, 0.8f, 0.2f));
	freeTypeRenderer->renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));

	freeTypeRenderer->renderText("Ąą Ćć Ęę Łł Ńń Óó Źź Żż", 0.0f, 0.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));
}

namespace temp_t00f_polish_fonts_view {
TempT00FpolishFontsView *openGLview = nullptr;

shared_ptr<TempT00FpolishFontsView> getView(bool reset,
		shared_ptr<ResourceCache> resourceCache) {
	if (openGLview == nullptr) {
		openGLview = new TempT00FpolishFontsView(resourceCache);
		openGLview->vInit();
	} else {
		if (reset) {
			delete (openGLview);
			openGLview = new TempT00FpolishFontsView(resourceCache);
			openGLview->vInit();
		}
	}
	return shared_ptr<TempT00FpolishFontsView> { openGLview };
}
}
} /* namespace base_game */


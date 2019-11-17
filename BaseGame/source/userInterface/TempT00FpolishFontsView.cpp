/*
 * TempT00FpolishFontsView.cpp
 *
 *  Created on: 28 kwi 2019
 *      Author: Krzysztof
 */

#include "TempT00FpolishFontsView.h"

#include "../debugging/Logger.h"
//#include "../main/OpenGLShader.h"
//#include "TempShader.hpp"
#include "../graphics3D/ShaderResourceLoader.h"
#include "../graphics3D/FreeTypeResourceLoader.h"
#include "../graphics3D/FreeTypeCharacter.h"

//#include "../main/OpenGLwithGLFW.h"
#include "../gameInitialization/VideoSystemGLFW.h"

// #include "../main/shader.h"

#include <GLFW/glfw3.h> // GLFWwindow
#include <math.h> // cos, sin
#include <iostream>
#include <sstream>      // std::stringstream
#include <map> // std::map
#include <string> // std::string

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp> // glm::ivec2
#include <glm/gtc/matrix_transform.hpp> // glm::ortho
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//#include "../main/vmath.h" // vmath::mat4
#include "vmath.h" // vmath::mat4

// TEMPORARY COMMENTED
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

//using std::cout;
//using std::endl;
using std::map;
using std::shared_ptr;
using std::string;
using std::stringstream;

namespace base_game {

const GLubyte TempT00FpolishFontsView::MAX_STD_CHAR = 128;

TempT00FpolishFontsView::TempT00FpolishFontsView(
		shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create T00FpolishFontsView");
	// cout << "Create T00FpolishFontsView" << endl;
	programID = 0;
	VAO = 0;
	VBO = 0;

	this->shrdPtrResourceCache = resourceCache;
}

TempT00FpolishFontsView::~TempT00FpolishFontsView() {
	logger::info("Destroy T00FpolishFontsView");
	// cout << "Destroy T00FpolishFontsView" << endl;
	this->vTerminate();
	shrdPtrResourceCache.reset();
	characters.reset();
}

void TempT00FpolishFontsView::vTerminate() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programID);
	glDeleteBuffers(1, &VBO);

	/*
	 glDeleteVertexArrays(1, &vao);
	 glDeleteProgram (programID);
	 glDeleteBuffers(1, &position_buffer);
	 glDeleteBuffers(1, &uvbuffer);
	 */

//	glDeleteTextures(1, &texture);
}

/*
void TempT00FpolishFontsView::initCharacter(FT_Face face, FT_ULong char_code,
		GLushort char_code_out) {
	stringstream ss;

	ss << "[" << (int) (char_code) << "]:[" << char(char_code) << "] ";
	logger::info(ss);

	// Load character glyph
	if (FT_Load_Char(face, char_code, FT_LOAD_RENDER)) {
		logger::error("ERROR::FREETYTPE: Failed to load Glyph");
		// std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		return;
	}
	// Generate texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
	GL_TEXTURE_2D, 0,
	GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
	GL_RED,
	GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	// Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Now store character for later use
	T00Fcharacter character = { texture, glm::ivec2(face->glyph->bitmap.width,
			face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left,
			face->glyph->bitmap_top), face->glyph->advance.x };
	Characters.insert(
			std::pair<GLushort, T00Fcharacter>(char_code_out, character));
}
 */


void TempT00FpolishFontsView::debugCharacters() {
	stringstream ss;

	logger::info("--------- DEBUG START TempT00FpolishFontsView -------");
	//cout << "--------- DEBUG START-------" << endl;

	ss << "debug: " << characters->size();
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;
	for (it = characters->begin(); it != characters->end(); ++it) {
		ss << "Key: " << std::hex << it->first; // << endl;
		logger::info(ss);

	}

	logger::info("--------- DEBUG END TempT00FpolishFontsView -------");

	//cout << "--------- DEBUG END-------" << endl;

}


/*
void TempT00FpolishFontsView::initCharacter(FT_Face face, FT_ULong char_code) {
	this->initCharacter(face, char_code, char_code);
}
 */

/*
void TempT00FpolishFontsView::initFreetypeCharacters(FT_Face face) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	stringstream ss;

	for (GLubyte c = 0; c < MAX_STD_CHAR; c++) {
		initCharacter(face, c);
	}
	logger::info("");
	//cout << endl;
	logger::info("-----------------------");

	//cout << "-----------------------" << endl;

//	FT_ULong codes[18] = { 260, 261, 262, 263, 280, 281, 321, 322, 323, 324, 211,
	//		243, 346, 347, 377, 378, 379, 380 };

	FT_ULong codes[18] = { 177, 230, 234, 179, 241, 243, 182, 188, 191, 161,
			198, 202, 163, 209, 211, 166, 172, 175 };

	for (FT_ULong code : codes) {
		ss << "[" << (int) (code) << "]:[" << char(code) << "] ";

	}
	logger::info(ss);
	// cout << endl;

	// A
	this->initCharacter(face, 0x0104, 0xc484);
	// a
	this->initCharacter(face, 0x0105, 0xc485);

	// C
	this->initCharacter(face, 0x0106, 0xc486);
	// c
	this->initCharacter(face, 0x0107, 0xc487);

	// E
	this->initCharacter(face, 0x0118, 0xc498);
	// e
	this->initCharacter(face, 0x0119, 0xc499);

	// L
	this->initCharacter(face, 0x0141, 0xc581);
	// l
	this->initCharacter(face, 0x0142, 0xc582);

	// N
	this->initCharacter(face, 0x0143, 0xc583);
	// n
	this->initCharacter(face, 0x0144, 0xc584);

	// O
	this->initCharacter(face, 0x00D3, 0xc393);
	// o
	this->initCharacter(face, 0x00F3, 0xc3b3);

	// S
	this->initCharacter(face, 0x015A, 0xc59a);
	// s
	this->initCharacter(face, 0x015B, 0xc59b);

	// X
	this->initCharacter(face, 0x0179, 0xc5b9);
	// x
	this->initCharacter(face, 0x017A, 0xc5ba);

	// Z
	this->initCharacter(face, 0x017B, 0xc5bb);
	// z
	this->initCharacter(face, 0x017C, 0xc5bc);

	glBindTexture(GL_TEXTURE_2D, 0);

}
 */

/*
void TempT00FpolishFontsView::initFreetype() {
	FT_Library ft = nullptr;
	FT_Face face = nullptr;

	FT_Error ft_error = FT_Init_FreeType(&ft);

	if (ft_error) {
		logger::error("ERROR::FREETYPE: Could not init FreeType Library");
		//cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
	}

	ft_error =
			FT_New_Face(ft,
					"../WaterMill/assets/graphics/temp_t00f_polish_fonts_view-ariali.ttf",
					0, &face);

	if (ft_error == FT_Err_Unknown_File_Format) {
		logger::error("ERROR::FREETYPE: Failed to load font");
		logger::error(
				"... the font file could be opened and read, but it appears");
		logger::error("... that its font format is unsupported");

	} else if (ft_error) {
		logger::error("ERROR::FREETYPE: Failed to load font");
		logger::error(
				"... another error code means that the font file could not");
		logger::error("... be opened or read, or that it is broken...");
	}

 ft_error = FT_Set_Pixel_Sizes(face, // handle to face object
 0, // pixel_width
 48); // pixel_height

	if (ft_error) {
		logger::error("ERROR::FREETYPE: Could not set pixel sizes");
		// cout << "ERROR::FREETYPE: Could not set pixel sizes" << endl;
	}

	initFreetypeCharacters(face);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

}
 */

void TempT00FpolishFontsView::vInit() {
	//initFreetype();
	//this->debugCharacters();
	// initFreetypeCharacters();

	FreeTypeLoader freeTypeLoader(this->shrdPtrResourceCache);
	characters = freeTypeLoader.initFreetype();
	freeTypeLoader.debugCharacters();
	//Characters = freeTypeLoader.temp_getCharacters();

	this->debugCharacters();


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	string vertResourceName = "temp_t00f_polish_fonts_view.vert";
	string fragResourceName = "temp_t00f_polish_fonts_view.frag";

	ShaderCompiler shaderCompiler(this->shrdPtrResourceCache); // = new ShaderCompiler();
	programID = shaderCompiler.loadShaders(vertResourceName, fragResourceName);

	//programID = LoadShaders(
	//		"../../../assets/shaders/temp_t00f_polish_fonts_view.vert",
	//		"../../../assets/shaders/temp_t00f_polish_fonts_view.frag");



	vActivate();
}

void TempT00FpolishFontsView::vActivate() {
	//IOpenGLView::vActivate();
	HumanView::vActivate();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	/* Tylko dolna cwiartka ekranu
	 glm::mat4 projection = glm::ortho(0.0f,
	 static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_WIDTH * 2), 0.0f,
	 static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_HEIGHT * 2));
	 */

	/*
	 glm::mat4 projection = glm::ortho(0.0f,
	 static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_WIDTH), 0.0f,
	 static_cast<GLfloat>(OpenGLwithGLFW::WINDOW_HEIGHT));
	 */
	glm::mat4 projection = glm::ortho(0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_WIDTH), 0.0f,
			static_cast<GLfloat>(VideoSystemGLFW::WINDOW_HEIGHT));

	// porownac z:
	//glViewport(0, 0, VideoSystemGLFW::WINDOW_WIDTH,
	//	VideoSystemGLFW::WINDOW_HEIGHT);

	glUseProgram(programID);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1,
	GL_FALSE, glm::value_ptr(projection));

	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
	GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void TempT00FpolishFontsView::RenderLetter(FreeTypeCharacter ch, GLfloat &x,
		GLfloat y, GLfloat scale) {
	//T00Fcharacter ch = Characters[*c];

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

// unsigned char T00FpolishFontsView::RenderFirstLetter(unsigned char charC,

GLubyte TempT00FpolishFontsView::RenderUShortLetter(GLubyte charC,
		GLubyte prevChar, GLfloat& x, GLfloat y, GLfloat scale) {

	stringstream ss;

	ss << "charC: " << std::hex << (GLushort) charC << "; prevChar: "
			<< (GLushort) prevChar; // << endl;
	logger::info(ss);

	GLushort shortC = prevChar * 0x100 + charC;

	ss << "renderUshort -> shortC: " << std::hex << shortC << std::dec;
	//	<< endl;
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;

	FreeTypeCharacter ch;
	// it = Characters.find(shortC);
	it = characters->find(shortC);

	//it = Characters.find(50308);

	//if (it == Characters.end()) {
	//	ch = Characters[0x00];
	if (it == characters->end()) {
		//ch = characters.get()[0x00];
		//ch = characters->[0x00];
		ch = characters->at(0x00);
	} else {
		ch = it->second;
	}

	this->RenderLetter(ch, x, y, scale);

	return 0x00;
}

GLubyte TempT00FpolishFontsView::RenderUByteLetter(GLubyte charC, GLfloat& x,
		GLfloat y, GLfloat scale) {
	stringstream ss;

	FreeTypeCharacter ch;
	if (charC >= 0 && charC < MAX_STD_CHAR) {
		//ch = Characters[*c];
		//ch = characters.get()[charC];

		//ch = Characters[charC];
		ch = characters->at(charC);
		this->RenderLetter(ch, x, y, scale);
		//x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)

	} else if (charC == 0xc3) {
		//cout << "0xc3" << endl;
		logger::info("0xc3");
		return charC;
	} else if (charC == 0xc4) {
		//cout << "0xc4" << endl;
		logger::info("0xc4");
		return charC;
	} else if (charC == 0xc5) {
		//cout << "0xc5" << endl;
		logger::info("0xc5");
		return charC;
	} else {

		ss << charC << ": " << std::hex << (short) charC << std::dec << " |"
				<< (charC) << "|"; // << endl;
		logger::info (ss);
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
	// unsigned char prevChar = 0x00;

	for (c = text.begin(); c != text.end(); c++) {

		GLubyte charC = (*c);
		if (charC == 0xc3) {
			logger::info("charC - 0xc3");

			//cout << "charC - 0xc3" << endl;
		} else if (charC == 0xc4) {
			logger::info("charC - 0xc4");
			//cout << "charC - 0xc4" << endl;
		} else if (charC == 0xc5) {
			//cout << "charC - 0xc5" << endl;
			logger::info("charC - 0xc5");
		}

		GLushort shortC = (*c);
		if (shortC == 0xffc3) {
			//cout << "shortC - 0xffc3" << endl;
			logger::info("shortC - 0xffc3");
		} else if (shortC == 0xffc4) {
			//cout << "shortC - 0xffc4" << endl;
			logger::info("shortC - 0xffc4");
		} else if (shortC == 0xffc5) {
			//cout << "shortC - 0xffc5" << endl;
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

void TempT00FpolishFontsView::vDeactivate() {
	//IOpenGLView::vDeactivate();
	HumanView::vDeactivate();

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glUseProgram(0);

	/*
	 glBindTexture(GL_TEXTURE_2D, 0);

	 glBindVertexArray(0);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glDisableVertexAttribArray(0);
	 glDisableVertexAttribArray(1);

	 glUseProgram(0);
	 */
}

void TempT00FpolishFontsView::vOnRender(double currentTime,
		float fElapsedTime) {
	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);

	RenderText("This is sample text", 25.0f, 25.0f, 1.0f,
			glm::vec3(0.5, 0.8f, 0.2f));
	RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));

	//RenderText("Ą", 0.0f, 0.0f, 0.5f,
	//		glm::vec3(0.3, 0.7f, 0.9f));

	RenderText("Ąą Ćć Ęę Łł Ńń Óó Źź Żż", 0.0f, 0.0f, 0.5f,
			glm::vec3(0.3, 0.7f, 0.9f));

//	RenderText("Aa Cc Ee Ll nn Oo Zz", 0.0f, 0.0f, 0.5f,
	//		glm::vec3(0.3, 0.7f, 0.9f));

	/*
	 static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	 static const GLfloat one = 1.0f;

	 glViewport(0, 0, OpenGLwithGLFW::WINDOW_WIDTH,
	 OpenGLwithGLFW::WINDOW_HEIGHT);
	 glClearBufferfv(GL_COLOR, 0, black);
	 glClearBufferfv(GL_DEPTH, 0, &one);

	 //glUseProgram (programID);

	 // square, triangle, rectangle, bottom rectangle
	 glDrawElements(GL_TRIANGLES, 2 * 3 + 3 + 2 * 3 + 2 * 3, GL_UNSIGNED_SHORT,
	 0);
	 // glDrawElements(GL_TRIANGLES, 2 * 3 + 3, GL_UNSIGNED_SHORT, 0);
	 *
	 */
}

namespace temp_t00f_polish_fonts_view {
TempT00FpolishFontsView* openGLview = nullptr;

//TempT00FpolishFontsView*
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
	//return openGLview;
	return shared_ptr<TempT00FpolishFontsView> { openGLview };
}
}
///////////
} /* namespace base_game */


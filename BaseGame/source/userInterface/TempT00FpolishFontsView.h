/*
 * TempT00FpolishFontsView.h
 *
 *  Created on: 28 kwi 2019
 *      Author: Krzysztof
 */

#ifndef USERINTERFACE_TEMPT00FPOLISHFONTSVIEW_H_
#define USERINTERFACE_TEMPT00FPOLISHFONTSVIEW_H_

#include "HumanView.h"
// #include "../main/shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

//#include <boost/gil/extension/io/png.hpp> // boost::gil::rgb8_image_t

#include <map> // std::map
#include <glm/glm.hpp> // glm::ivec2
#include <string> // std::string

namespace base_game {

struct T00Fcharacter {
	GLuint TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint Advance;    // Offset to advance to next glyph
};

class TempT00FpolishFontsView: public HumanView {
public:
	const static GLubyte MAX_STD_CHAR;

	TempT00FpolishFontsView();
	virtual ~TempT00FpolishFontsView();

	virtual void vInit();
	virtual void vOnRender(double fTime, float fElapsedTime);

	virtual void vTerminate();
	virtual void vActivate();
	virtual void vDeactivate();

protected:
	GLuint programID;
	GLuint VAO, VBO;

	//boost::gil::rgba8_image_t rgba8_image; // boost::gil::image

	// Freetype
	// FT_Face face;
	std::map<GLushort, T00Fcharacter> Characters;

	void initFreetype();
	void initFreetypeCharacters(FT_Face face);
	void initCharacter(FT_Face face, FT_ULong char_code);
	void initCharacter(FT_Face face, FT_ULong char_code,
			GLushort char_code_out);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale,
			glm::vec3 color);

	GLubyte RenderUByteLetter(GLubyte charC, GLfloat& x, GLfloat y,
			GLfloat scale);

	GLubyte RenderUShortLetter(GLubyte charC, GLubyte prevChar, GLfloat& x,
			GLfloat y, GLfloat scale);

	void RenderLetter(T00Fcharacter ch, GLfloat& x, GLfloat y, GLfloat scale);

	void debugCharacters();

};

namespace temp_t00f_polish_fonts_view {
TempT00FpolishFontsView* getView(bool reset);
}

} /* namespace opengl_tests */

#endif /* USERINTERFACE_TEMPT00FPOLISHFONTSVIEW_H_ */

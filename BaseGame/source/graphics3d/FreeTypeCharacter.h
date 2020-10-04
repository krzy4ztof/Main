/*
 * FreeTypeCharacter.h
 *
 *  Created on: 13 lis 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_FREETYPECHARACTER_H_
#define GRAPHICS3D_FREETYPECHARACTER_H_

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2

namespace base_game {

struct FreeTypeCharacter {
	const static GLubyte MAX_STD_CHAR;
	const static GLuint PIXEL_HEIGHT;

	GLuint TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint Advance;    // Offset to advance to next glyph
	//GLuint height; // Text height
};
} /* namespace base_game */

#endif /* GRAPHICS3D_FREETYPECHARACTER_H_ */

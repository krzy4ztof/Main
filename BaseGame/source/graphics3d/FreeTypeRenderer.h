/*
 * FreeTypeRenderer.h
 *
 *  Created on: 18 lis 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_FREETYPERENDERER_H_
#define GRAPHICS3D_FREETYPERENDERER_H_

// #include "../resourceCache/ResourceCache.h"
#include "FreeTypeCharacter.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2, glm:mat4

#include <map> // std::map
#include <memory> // shared_ptr
#include <string> // std::string

namespace base_game {

class FreeTypeRenderer {
public:
	FreeTypeRenderer();
	// FreeTypeRenderer(std::shared_ptr<ResourceCache> resourceCache);
	//FreeTypeRenderer(
	//	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters);
	virtual ~FreeTypeRenderer();

	void startRender();
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale,
			glm::vec3 color);

	void init(GLuint programID,
			std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters);

	void activate(glm::mat4 projection);
	void deactivate();

	void debugCharacters();

protected:
	void terminate();

	GLubyte renderUByteLetter(GLubyte charC, GLfloat &x, GLfloat y,
			GLfloat scale);

	GLubyte renderUShortLetter(GLubyte charC, GLubyte prevChar, GLfloat &x,
			GLfloat y, GLfloat scale);

//	void RenderLetter(T00Fcharacter ch, GLfloat& x, GLfloat y, GLfloat scale);
	void renderLetter(FreeTypeCharacter ch, GLfloat &x, GLfloat y,
			GLfloat scale);

private:
	GLuint programID;
	GLuint VAO, VBO;

	std::shared_ptr<std::map<GLushort, FreeTypeCharacter>> characters;

};

} /* namespace base_game */

#endif /* GRAPHICS3D_FREETYPERENDERER_H_ */

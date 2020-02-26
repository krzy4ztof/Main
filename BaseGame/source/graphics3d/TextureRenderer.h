/*
 * JpegRenderer.h
 *
 *  Created on: 8 gru 2019
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_TEXTURERENDERER_H_
#define GRAPHICS3D_TEXTURERENDERER_H_

#include "SpriteSheet.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <memory> // shared_ptr

namespace base_game {

class TextureRenderer {
public:
	TextureRenderer();
	virtual ~TextureRenderer();

	virtual void activate(glm::mat4 projection);
	virtual void deactivate();
	void init(GLuint programID);

	void renderRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint,
			std::shared_ptr<SpriteSheet> spriteSheet, int spriteRow,
			int spriteCol);

	void renderMultiRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint,
			GLfloat numberX, GLfloat numberY);
	void renderTriangle(glm::vec2 zeroPoint, glm::vec2 fstPoint,
			glm::vec2 secPoint, glm::vec2 zeroPointTexture,
			glm::vec2 fstPointTexture, glm::vec2 secPointTexture);


protected:
	void activateRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint,
			glm::vec2 zeroPointTexture, glm::vec2 thrdPointTexture);

	void activateFigure(const GLushort *vertex_indices,
			GLsizeiptr vertex_indices_size, const GLfloat *vertex_positions,
			GLsizeiptr vertex_positions_size, const GLfloat *g_uv_buffer_data,
			GLsizeiptr g_uv_buffer_data_size);

	void activateTriangle(glm::vec2 zeroPoint, glm::vec2 fstPoint,
			glm::vec2 secPoint, glm::vec2 zeroPointTexture,
			glm::vec2 fstPointTexture, glm::vec2 secPointTexture);


	GLuint programID;
	GLuint vao; // vertex_array_object
	GLuint position_buffer;
	GLuint index_buffer;
	GLuint uvbuffer;
};

class PngRenderer: public TextureRenderer {
public:
	PngRenderer();
	virtual ~PngRenderer();
	void temp_render();
	void temp_activate();

	virtual void activate(glm::mat4 projection);
	virtual void deactivate();


protected:
};

class JpegRenderer: public TextureRenderer {
public:
	JpegRenderer();
	virtual ~JpegRenderer();

	void temp_render();

protected:
	void temp_activate();
};

} /* namespace base_game */

#endif /* GRAPHICS3D_TEXTURERENDERER_H_ */

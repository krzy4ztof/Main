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

	void activate(glm::mat4 projection);
	void deactivate();
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

	// GLuint texture;
	GLuint uvbuffer;

};

class PngRenderer: public TextureRenderer {
public:
	PngRenderer();
	virtual ~PngRenderer();
	void temp_render();
	void temp_activate();

protected:
};

class JpegRenderer: public TextureRenderer {
public:
	JpegRenderer();
	virtual ~JpegRenderer();
	// void activate(glm::mat4 projection);
	// void deactivate();
	// void reset();

	//void activateTexture(SpriteSheet *spriteSheet);
//	void init(GLuint programID);
	void temp_render();
	//void renderRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint);

	//void renderRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint,
	//		std::shared_ptr<SpriteSheet> spriteSheet, int spriteRow,
	//		int spriteCol);

	// glm::vec2 zeroPointTexture, glm::vec2 thrdPointTexture);
//	void renderMultiRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint,
//			GLfloat numberX, GLfloat numberY);
	//void renderRectangle3();
//	void renderTriangle(glm::vec2 zeroPoint, glm::vec2 fstPoint,
//			glm::vec2 secPoint, glm::vec2 zeroPointTexture,
//			glm::vec2 fstPointTexture, glm::vec2 secPointTexture);

protected:
//	void activateRectangle(glm::vec2 zeroPoint, glm::vec2 thrdPoint,
//			glm::vec2 zeroPointTexture, glm::vec2 thrdPointTexture);
	//void activateRectangle2();
	//void activateRectangle3();

//	void activateTriangle(glm::vec2 zeroPoint, glm::vec2 fstPoint,
//			glm::vec2 secPoint, glm::vec2 zeroPointTexture,
//			glm::vec2 fstPointTexture, glm::vec2 secPointTexture);
//	void activateFigure(const GLushort *vertex_indices,
//			GLsizeiptr vertex_indices_size, const GLfloat *vertex_positions,
//			GLsizeiptr vertex_positions_size, const GLfloat *g_uv_buffer_data,
//			GLsizeiptr g_uv_buffer_data_size);
	void temp_activate();

//	void terminate();
	// GLuint vertex_array_object;
	/*
	GLuint programID;
	GLuint vao; // vertex_array_object
	GLuint position_buffer;
	GLuint index_buffer;

	// GLuint texture;
	GLuint uvbuffer;
	*/
};

} /* namespace base_game */

#endif /* GRAPHICS3D_TEXTURERENDERER_H_ */

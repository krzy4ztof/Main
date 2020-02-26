/*
 * SpriteSheet.h
 *
 *  Created on: 2 sty 2020
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_SPRITESHEET_H_
#define GRAPHICS3D_SPRITESHEET_H_

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <glm/glm.hpp> // glm::ivec2, glm:mat4

namespace base_game {

class SpriteSheet {
public:
	SpriteSheet();
	virtual ~SpriteSheet();

	int getWidth() {
		return width;
	}

	void setWidth(int width);

	int getHeight() {
		return height;
	}

	void setHeight(int height);

	void setMargin(int margin);

	void setColumns(int columns);

	void setRows(int rows);

	glm::vec2 getZeroPoint(int row, int col);
	glm::vec2 getThrdPoint(int row, int col);


	float *data;
	GLuint texture;
protected:
	void recalculateSpriteHeight();
	void recalculateSpriteWidth();

private:
	int width;
	int height;
	int margin;
	int columns;
	int spriteWidth;
	int spriteHeight;
	int rows;

};

} /* namespace base_game */

#endif /* GRAPHICS3D_SPRITESHEET_H_ */

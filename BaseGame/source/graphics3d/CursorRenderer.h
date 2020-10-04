/*
 * CursorRenderer.h
 *
 *  Created on: 22 wrz 2020
 *      Author: Krzysztof
 */

#ifndef GRAPHICS3D_CURSORRENDERER_H_
#define GRAPHICS3D_CURSORRENDERER_H_

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>

#include <memory> // shared_ptr

namespace base_game {

class CursorRenderer {
public:
	//CursorRenderer(std::shared_ptr<GLFWwindow> window);
	//CursorRenderer(GLFWwindow *window);

	CursorRenderer();
	virtual ~CursorRenderer();

	void activateHandCursor();
	void activateArrowCursor();

	void init(GLFWwindow *window);

protected:
//	std::shared_ptr<GLFWwindow> window;
	GLFWwindow *window;
	GLFWcursor *handCursor;
//	std::shared_ptr<GLFWcursor> handCursor;

};

} /* namespace base_game */

#endif /* GRAPHICS3D_CURSORRENDERER_H_ */

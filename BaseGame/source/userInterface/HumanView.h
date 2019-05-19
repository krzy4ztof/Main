#ifndef HUMANVIEW_H
#define HUMANVIEW_H

#include "IGameView.h"
#include "../inputDevices/IPointerHandler.h"
#include "../inputDevices/IKeyboardHandler.h"

#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow
#include <memory> // shared_ptr, weak_ptr

namespace base_game {
class HumanView: public IGameView {
public:
	HumanView();
	virtual ~HumanView();

	virtual void vOnRestore();
	virtual void vOnRender(double fTime, float fElapsedTime);
	virtual void vOnAttach(unsigned int vid, unsigned int aid);
	virtual void describeYourself();

	// Start Freeglut
	/*
	 virtual bool vOnKeyboardFunc(unsigned char key, int x, int y);
	 virtual bool vOnKeyboardUpFunc(unsigned char key, int x, int y);
	 virtual bool vOnSpecialFunc(int key, int x, int y);
	 virtual bool vOnSpecialUpFunc(int key, int x, int y);
	 */

	/*
	 virtual bool vOnMouseFunc(int button, int state, int x, int y);
	 virtual bool vOnMotionFunc(int x, int y);
	 virtual bool vOnPassiveMotionFunc(int x, int y);
	 virtual bool vOnMouseWheelFunc(int wheel, int direction, int x, int y);
	 */
	// End Freeglut

	virtual bool vOnKeyCallback(GLFWwindow* window, int key, int scancode,
			int action, int mods);
	virtual bool vOnCharCallback(GLFWwindow* window, unsigned int codepoint);
	virtual bool vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
			int mods);
	virtual bool vOnCursorPositionCallback(GLFWwindow* window, double xpos,
			double ypos);
	virtual bool vOnCursorEnterCallback(GLFWwindow* window, int entered);
	virtual bool vOnMouseButtonCallback(GLFWwindow* window, int button,
			int action, int mods);
	virtual bool vOnScrollCallback(GLFWwindow* window, double xoffset,
			double yoffset);

	//	void tempOnRender(double fTime, float fElapsedTime);
	//void tempOnRenderGLFW(double fTime, float fElapsedTime);
	virtual void tempVLoadGameDelegate();

protected:
	unsigned int m_ViewId;
	unsigned int m_ActorId;
	std::shared_ptr<IPointerHandler> m_PointerHandler;
	std::shared_ptr<IKeyboardHandler> m_KeyboardHandler;

	float tempAngle;
};
}

#endif // HUMANVIEW_H

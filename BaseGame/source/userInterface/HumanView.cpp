#include "HumanView.h"
#include "../debugging/Logger.h"
#include "../inputDevices/MovementController.h"

// #include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLFWwindow
//#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <sstream>      // std::stringstream
#include <memory> // shared_ptr, weak_ptr, make_shared

using std::stringstream;
using std::make_shared;
using std::shared_ptr;

namespace base_game {
HumanView::HumanView() {
	logger::info("Create HumanView");
	tempAngle = 0.0f;

	m_PointerHandler = nullptr;
	m_KeyboardHandler = nullptr;

	m_ViewId = 0;
	m_ActorId = 0;
}

HumanView::~HumanView() {
	logger::info("Destroy HumanView");
	m_KeyboardHandler.reset();
	m_PointerHandler.reset();
}

void HumanView::vOnAttach(unsigned int vid, unsigned int aid) {
	m_ViewId = vid;
	m_ActorId = aid;
}

void HumanView::vOnRestore() {
	logger::info("vOnRestore HumanView");
}

void HumanView::vOnRender(double fTime, float fElapsedTime) {
	//logger::info("vOnRender HumanView");

	/*
	bool glfw = true;

	if (glfw) {
		tempOnRenderGLFW(fTime, fElapsedTime);
	} else {
		//	tempOnRender(fTime, fElapsedTime);
	}
	 */
}

void HumanView::describeYourself() {
	logger::info("HumanView describeYourself");
}

/*
bool HumanView::vOnKeyboardFunc(unsigned char key, int x, int y) {
	stringstream ss;

	ss << "HUMAN-VIEW KEYBOARD: key:" << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);


	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnKeyboardFunc(key, x, y);
		return true;
	} else {
		return false;
	}

	// return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)
}

bool HumanView::vOnKeyboardUpFunc(unsigned char key, int x, int y) {
	stringstream ss;

	ss << "HUMAN-VIEW KEYBOARD-UP: key:" << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnKeyboardUpFunc(key, x, y);
		return true;
	} else {
		return false;
	}

	// return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool HumanView::vOnSpecialFunc(int key, int x, int y) {
	stringstream ss;

	ss << "HUMAN-VIEW SPECIAL: key:" << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnSpecialFunc(key, x, y);
		return true;
	} else {
		return false;
	}

	// return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)
}

bool HumanView::vOnSpecialUpFunc(int key, int x, int y) {
	stringstream ss;

	ss << "HUMAN-VIEW SPECIAL-UP: " << key << "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnSpecialUpFunc(key, x, y);
		return true;
	} else {
		return false;
	}
	// return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}
 */

/*
bool HumanView::vOnMouseFunc(int button, int state, int x, int y) {
	stringstream ss;
	ss << "HUMAN-VIEW MOUSE: button:" << button << "; state: " << state
			<< "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnMouseFunc(button, state, x, y);
		return true;
	} else {
		return false;
	}
	// return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool HumanView::vOnMotionFunc(int x, int y) {
	stringstream ss;
	ss << "HUMAN-VIEW MOTION: x:" << x << "; y: " << y;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnMotionFunc(x, y);
		return true;
	} else {
		return false;
	}
	//return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool HumanView::vOnPassiveMotionFunc(int x, int y) {
	stringstream ss;
	ss << "HUMAN-VIEW PASSIVE-MOTION: x:" << x << "; y: " << y;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnPassiveMotionFunc(x, y);
		return true;
	} else {
		return false;
	}
	//return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool HumanView::vOnMouseWheelFunc(int wheel, int direction, int x, int y) {
	stringstream ss;
	ss << "HUMAN-VIEW MOUSE: wheel:" << wheel << "; direction: " << direction
			<< "; x: " << x << "; y: " << y;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnMouseWheelFunc(wheel, direction, x, y);
		return true;
	} else {
		return false;
	}
	//return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}
 */

bool HumanView::vOnKeyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "HumanView::onKeyCallback: key: " << key << "; scancode: " << scancode
			<< "; action: " << action << "; mods: " << mods;
	// logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnKeyCallback(window, key, scancode, action, mods);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCharCallback(GLFWwindow* window, unsigned int codepoint) {
	stringstream ss;
	ss << "HumanView::onCharCallback: codepoint: " << codepoint;
	//logger::info(ss);

	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnCharCallback(window, codepoint);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCharmodsCallback(GLFWwindow* window, unsigned int codepoint,
		int mods) {
	stringstream ss;
	ss << "HumanView::onCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	//logger::info(ss);
	
	if (m_KeyboardHandler) {
		m_KeyboardHandler->vOnCharmodsCallback(window, codepoint, mods);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCursorPositionCallback(GLFWwindow* window, double xpos,
		double ypos) {
	stringstream ss;
	ss << "HumanView::onCursorPositionCallback: xpos: " << xpos << "; ypos: "
			<< ypos;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnCursorPositionCallback(window, xpos, ypos);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnCursorEnterCallback(GLFWwindow* window, int entered) {
	stringstream ss;
	ss << "HumanView::onCursorEnterCallback: entered: " << entered;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnCursorEnterCallback(window, entered);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnMouseButtonCallback(GLFWwindow* window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "HumanView::onMouseButtonCallback: button: " << button << "; action: "
			<< action << "; mods: " << mods;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnMouseButtonCallback(window, button, action, mods);
		return true;
	} else {
		return false;
	}
}

bool HumanView::vOnScrollCallback(GLFWwindow* window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "HumanView::onScrollCallback: xoffset: " << xoffset << "; yoffset: "
			<< yoffset;
	//logger::info(ss);

	if (m_PointerHandler) {
		m_PointerHandler->vOnScrollCallback(window, xoffset, yoffset);
		return true;
	} else {
		return false;
	}
}


/*
void HumanView::tempOnRender(double fTime, float fElapsedTime) {

	//	stringstream ss;
	//float angle = 0.0f;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(1.0f, 0.0f, 0.0f); // Red
	glColor3f(0.0f, 1.0f, 1.0f); //blue

	// Reset transformations
	glLoadIdentity();
	// Set the camera

#ifdef __linux__
	// TODO: not working on Windows

	gluLookAt( 0.0f, 0.0f, 10.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

 #endif //
	glRotatef(tempAngle, 0.0f, 1.0f, 0.0f);

	glBegin (GL_TRIANGLES);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0);
	glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();

	//if (angle < 3.0f){
	tempAngle += 0.1f;
	//}
	glutSwapBuffers();

}
 */

/*
void HumanView::tempOnRenderGLFW(double fTime, float fElapsedTime) {

	//	stringstream ss;
	//float angle = 0.0f;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(1.0f, 0.0f, 0.0f); // Red
	glColor3f(0.0f, 1.0f, 1.0f); //blue

	// Reset transformations
	glLoadIdentity();
	// Set the camera

	glRotatef(tempAngle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0);
	glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();


	//if (angle < 3.0f){
	tempAngle += 0.1f;
	//}
	//glutSwapBuffers();

}
 */

void HumanView::tempVLoadGameDelegate() {
	shared_ptr<MovementController> movementController = make_shared<
			MovementController>();
	m_PointerHandler = movementController;
	m_KeyboardHandler = movementController;

}
}

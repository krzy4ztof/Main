#include "HumanView.h"
#include "../debugging/Logger.h"
#include "../inputDevices/MovementController.h"

#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
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
	tempOnRender(fTime, fElapsedTime);

}

void HumanView::describeYourself() {
	logger::info("HumanView describeYourself");
}

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

void HumanView::tempOnRender(double fTime, float fElapsedTime) {

	//	stringstream ss;
	//float angle = 0.0f;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); // Red

	// Reset transformations
	glLoadIdentity();
	// Set the camera

#ifdef __linux__
	// TODO: not working on Windows

	gluLookAt( 0.0f, 0.0f, 10.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

#endif /* __linux__ */
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

void HumanView::tempVLoadGameDelegate() {
	shared_ptr<MovementController> movementController = make_shared<
			MovementController>();
	m_PointerHandler = movementController;
	m_KeyboardHandler = movementController;

}
}

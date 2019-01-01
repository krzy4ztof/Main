/*
 * MovementController.cpp
 *
 *  Created on: 30 gru 2018
 *      Author: Krzysztof
 */

#include "MovementController.h"
#include "../debugging/Logger.h"

#include <sstream>      // std::stringstream
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h

using std::stringstream;
using std::shared_ptr;

namespace base_game {

MovementController::MovementController() {
	logger::info("Create MovementController");

}

MovementController::~MovementController() {
	logger::info("Destroy MovementController");
}

bool MovementController::vOnKeyboardFunc(unsigned char key, int x, int y) {
	stringstream ss;

	int intKey = key;

	ss << "MOVEMENT-CONTROLLER KEYBOARD: key:" << key << "; x: " << x << "; y: "
			<< y << "; key code: " << intKey;
	logger::info(ss);

	int modifier = glutGetModifiers();

	if (modifier == GLUT_ACTIVE_SHIFT) {
		logger::info("MODIFIER: active shift");
	} else if (modifier == GLUT_ACTIVE_CTRL) {
		logger::info("MODIFIER: active ctrl");
	} else if (modifier == GLUT_ACTIVE_ALT) {
		logger::info("MODIFIER: active alt");
	}

	if (key == 'w' || key == 'W' || key == 23) {
		logger::info("UP pressed");
	} else if (key == 's' || key == 'S' || key == 19) {
		logger::info("DOWN pressed");
	} else if (key == 'a' || key == 'A' || key == 1) {
		logger::info("LEFT pressed");
	} else if (key == 'd' || key == 'D' || key == 4) {
		logger::info("RIGHT pressed");
	}

	ss << "sizeof u_char: " << sizeof(unsigned char) << "; sizeof int"
			<< sizeof(int);
	logger::info(ss);
	




	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)
}

bool MovementController::vOnKeyboardUpFunc(unsigned char key, int x, int y) {
	stringstream ss;

	ss << "MOVEMENT-CONTROLLER KEYBOARD-UP: key:" << key << "; x: " << x
			<< "; y: " << y;
//	logger::info(ss);

	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool MovementController::vOnSpecialFunc(int key, int x, int y) {
	stringstream ss;

	ss << "MOVEMENT-CONTROLLER SPECIAL: key:" << key << "; x: " << x << "; y: "
			<< y;
	logger::info(ss);

	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)
}

bool MovementController::vOnSpecialUpFunc(int key, int x, int y) {
	stringstream ss;

	ss << "MOVEMENT-CONTROLLER SPECIAL-UP: " << key << "; x: " << x << "; y: "
			<< y;
//	logger::info(ss);

	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool MovementController::vOnMouseFunc(int button, int state, int x, int y) {
	stringstream ss;
	ss << "MOVEMENT-CONTROLLER MOUSE: button:" << button << "; state: " << state
			<< "; x: " << x << "; y: " << y;
//	logger::info(ss);
	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool MovementController::vOnMotionFunc(int x, int y) {
	stringstream ss;
	ss << "MOVEMENT-CONTROLLER MOTION: x:" << x << "; y: " << y;
//	logger::info(ss);
	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool MovementController::vOnPassiveMotionFunc(int x, int y) {
	stringstream ss;
	ss << "MOVEMENT-CONTROLLER PASSIVE-MOTION: x:" << x << "; y: " << y;
//	logger::info(ss);
	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool MovementController::vOnMouseWheelFunc(int wheel, int direction, int x,
		int y) {
	stringstream ss;
	ss << "MOVEMENT-CONTROLLER MOUSE: wheel:" << wheel << "; direction: "
			<< direction << "; x: " << x << "; y: " << y;
//	logger::info(ss);
	return true; // stops further processing of vOnKeyboardFunc

	// return false; // allows to continue further processing of vOnKeyboardFunc // default -> return 0 (when view is not handling event)

}

bool MovementController::vOnKeyCallback(GLFWwindow* window, int key,
		int scancode,
		int action, int mods) {
	stringstream ss;
	ss << "MovementController::onKeyCallback: key: " << key << "; scancode: "
			<< scancode
			<< "; action: " << action << "; mods: " << mods;
	logger::info(ss);

	if (key == GLFW_KEY_W) {
		ss << "UP ";
	} else if (key == GLFW_KEY_S) {
		ss << "DOWN ";
	} else if (key == GLFW_KEY_A) {
		ss << "LEFT ";
	} else if (key == GLFW_KEY_D) {
		ss << "RIGHT ";
	}

	if (action == GLFW_PRESS) {
		ss << "PRESSED";
	} else if (action == GLFW_REPEAT) {
		ss << "REPEATED";
	} else if (action == GLFW_RELEASE) {
		ss << "RELEASED";
	}

	logger::info(ss);


	return true;
}

bool MovementController::vOnCharCallback(GLFWwindow* window,
		unsigned int codepoint) {
	stringstream ss;
	ss << "MovementController::onCharCallback: codepoint: " << codepoint;
	//logger::info(ss);

	return true;
}

bool MovementController::vOnCharmodsCallback(GLFWwindow* window,
		unsigned int codepoint,
		int mods) {
	stringstream ss;
	ss << "MovementController::onCharmodsCallback: codepoint: " << codepoint
			<< "; mods: " << mods;
	//logger::info(ss);

	return true;
}

bool MovementController::vOnCursorPositionCallback(GLFWwindow* window,
		double xpos,
		double ypos) {
	stringstream ss;
	ss << "MovementController::onCursorPositionCallback: xpos: " << xpos
			<< "; ypos: "
			<< ypos;
	//logger::info(ss);

	return true;
}

bool MovementController::vOnCursorEnterCallback(GLFWwindow* window,
		int entered) {
	stringstream ss;
	ss << "MovementController::onCursorEnterCallback: entered: " << entered;
	logger::info(ss);

	return true;
}

bool MovementController::vOnMouseButtonCallback(GLFWwindow* window, int button,
		int action, int mods) {
	stringstream ss;
	ss << "MovementController::onMouseButtonCallback: button: " << button
			<< "; action: "
			<< action << "; mods: " << mods;
	logger::info(ss);

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		ss << "LEFT MOUSE BUTTON ";
	} else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		ss << "MIDDLE MOUSE BUTTON ";
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		ss << "RIGHT MOUSE BUTTON ";
	} else if (button == GLFW_MOUSE_BUTTON_LAST) {
		ss << "LAST MOUSE BUTTON ";
	}

	if (action == GLFW_PRESS) {
		ss << "PRESSED";
	} else if (action == GLFW_REPEAT) {
		ss << "REPEATED";
	} else if (action == GLFW_RELEASE) {
		ss << "RELEASED";
	}

	logger::info(ss);

	return true;
}

bool MovementController::vOnScrollCallback(GLFWwindow* window, double xoffset,
		double yoffset) {
	stringstream ss;
	ss << "MovementController::onScrollCallback: xoffset: " << xoffset
			<< "; yoffset: "
			<< yoffset;
	//logger::info(ss);

	return true;
}


} /* namespace base_game */

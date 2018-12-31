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

} /* namespace base_game */

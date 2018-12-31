#include "IGameView.h"
#include "../debugging/Logger.h"

namespace base_game {
	IGameView::~IGameView() {
		logger::info("Destroy IGameView");
	}

bool IGameView::vOnKeyboardFunc(unsigned char key, int x, int y) {
	return false;
}

bool IGameView::vOnKeyboardUpFunc(unsigned char key, int x, int y) {
	return false;
}

bool IGameView::vOnSpecialFunc(int key, int x, int y) {
	return false;
}

bool IGameView::vOnSpecialUpFunc(int key, int x, int y) {
	return false;
}

bool IGameView::vOnMouseFunc(int button, int state, int x, int y) {
	return false;
}

bool IGameView::vOnMotionFunc(int x, int y) {
	return false;
}

bool IGameView::vOnPassiveMotionFunc(int x, int y) {
	return false;
}

bool IGameView::vOnMouseWheelFunc(int wheel, int direction, int x, int y) {
	return false;
}


}

/*
 * ScreenElementScene.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#include "ScreenElementScene.h"
#include "../debugging/Logger.h"

namespace base_game {

ScreenElementScene::ScreenElementScene() {
	logger::info("Create ScreenElementScene");

}

ScreenElementScene::~ScreenElementScene() {
	logger::info("Destroy ScreenElementScene");
}

void ScreenElementScene::vTerminate() {

}

int ScreenElementScene::vGetZOrder() const {
	return 0;
}

void ScreenElementScene::vSetZOrder(int const zOrder) const {
}

bool ScreenElementScene::vIsVisible() const {
	return true;
}
void ScreenElementScene::vSetVisible(bool visible) {
}

void ScreenElementScene::vOnRestore() {
	// TODO: implement
}

void ScreenElementScene::vOnRender(double fTime, float fElapsedTime) {
// TODO: implement
}

void ScreenElementScene::vOnUpdate(int deltaMS) {
//	OnUpdate(deltaMS);
}
;


} /* namespace base_game */

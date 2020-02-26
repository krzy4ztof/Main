/*
 * MainMenuUI.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#include "MainMenuUI.h"
#include "../debugging/Logger.h"

namespace base_game {

MainMenuUI::MainMenuUI() {
	logger::info("Create MainMenuUI");

}

MainMenuUI::~MainMenuUI() {
	logger::info("Destroy MainMenuUI");
}

void MainMenuUI::vTerminate() {

}

int MainMenuUI::vGetZOrder() const {
	return 1;
}

void MainMenuUI::vSetZOrder(int const zOrder) const {
}

void MainMenuUI::vOnRestore() {
	// TODO: implement
}

void MainMenuUI::vOnRender(double fTime, float fElapsedTime) {
// TODO: implement
}
;

} /* namespace base_game */

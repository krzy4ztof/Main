/*
 * BaseUI.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: Krzysztof
 */

#include "BaseUI.h"
#include "../debugging/Logger.h"

namespace base_game {

BaseUI::BaseUI() :
		m_bIsVisible(true) {
	logger::info("Create BaseUI");

}

BaseUI::~BaseUI() {
	logger::info("Destroy BaseUI");
}

bool BaseUI::vIsVisible() const {
	return m_bIsVisible;
}

void BaseUI::vSetVisible(bool visible) {
	m_bIsVisible = visible;
}

void BaseUI::vOnUpdate(int) {

}

} /* namespace base_game */

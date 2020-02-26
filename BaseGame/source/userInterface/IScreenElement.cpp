/*
 * IScreenElement.cpp
 *
 *  Created on: 20 sty 2020
 *      Author: Krzysztof
 */

#include "IScreenElement.h"
#include "../debugging/Logger.h"

namespace base_game {

IScreenElement::IScreenElement() {
	logger::info("Create IScreenElement");

}

IScreenElement::~IScreenElement() {
	logger::info("Destroy IScreenElement");
}

namespace iscreen_element {
bool compareByZOrder(const IScreenElement &first,
		const IScreenElement &second) {
	return (first.vGetZOrder() < second.vGetZOrder());

}
}

} /* namespace base_game */

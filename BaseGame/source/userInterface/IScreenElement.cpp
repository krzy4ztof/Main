/*
 * IScreenElement.cpp
 *
 *  Created on: 20 sty 2020
 *      Author: Krzysztof
 */

#include "IScreenElement.h"
#include "../debugging/Logger.h"
#include <memory> // shared_ptr

using std::shared_ptr;

namespace base_game {

IScreenElement::IScreenElement() {
	logger::info("Create IScreenElement");

}

IScreenElement::~IScreenElement() {
	logger::info("Destroy IScreenElement");
}

bool const IScreenElement::operator <(IScreenElement const &other) {
	return vGetZOrder() < other.vGetZOrder();
}

/*
namespace iscreen_element {

bool compareByZOrder(const std::shared_ptr<IScreenElement> &first,
		const std::shared_ptr<IScreenElement> &second) {
	return (first.vGetZOrder() < second.vGetZOrder());

}

 }
 */

} /* namespace base_game */

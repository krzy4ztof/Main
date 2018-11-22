/*
 * MessageParams.cpp
 *
 *  Created on: 12 lis 2018
 *      Author: Krzysztof
 */

#include "MessageParams.h"
#include "../debugging/Logger.h"

#include <sstream>      // std::stringstream
#include <string> // string

using std::string;
using std::stringstream;

namespace base_game {

MessageParams::MessageParams(string language, string encoding) {
	logger::info("Create MessageParams");
	this->language = language;
	this->encoding = encoding;

}

MessageParams::~MessageParams() {
	logger::info("Destroy MessageParams");
}

string MessageParams::getLanguage() {
	return language;

}

string MessageParams::getEncoding() {
	return encoding;
}

string MessageParams::getCode() {
	if (!encoding.empty()) {
		return language + "." + encoding;
	} else {
		return language;
	}
}

void MessageParams::describeYourself() {
	stringstream ss;
	ss << "MessageParams[language]: " << language
			<< "; MessageParams[encoding]:" << encoding;
	logger::info(ss);
}

} /* namespace base_game */

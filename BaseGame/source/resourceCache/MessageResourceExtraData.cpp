/*
 * MessageResourceExtraData.cpp
 *
 *  Created on: 12 lis 2018
 *      Author: Krzysztof
 */

#include "MessageResourceExtraData.h"

#include "../debugging/Logger.h"

#include <vector> // vector
#include <string> // string

using std::vector;
using std::string;

namespace base_game {

MessageResourceExtraData::MessageResourceExtraData() {
	logger::info("Create MessageResourceExtraData");

}

MessageResourceExtraData::~MessageResourceExtraData() {
	logger::info("Destroy MessageResourceExtraData");
}

void MessageResourceExtraData::init(char* pRawBuffer, uintmax_t rawSize) {
//skopiowac pRawBuffer do data
	for (int i = 0; i < rawSize; i++) {
		data.push_back(*(pRawBuffer + i));
	}

}

vector<char> MessageResourceExtraData::getData() {
	return data;
}


string MessageResourceExtraData::vToString() {
	return "MessageResourceExtraData";
}


} /* namespace base_game */

/*
 * BmpResourceExtraData.cpp
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#include "BmpResourceExtraData.h"

#include "../debugging/Logger.h"

#include <vector> // vector
#include <string> // string

using std::vector;
using std::string;

namespace base_game {

BmpResourceExtraData::BmpResourceExtraData() {
	logger::info("Create BmpResourceExtraData");

}

BmpResourceExtraData::~BmpResourceExtraData() {
	logger::info("Destroy BmpResourceExtraData");
}

void BmpResourceExtraData::init(char* pRawBuffer, uintmax_t rawSize) {
//skopiowac pRawBuffer do data

	/*
	for (int i = 0; i < rawSize; i++) {
		data.push_back(*(pRawBuffer + i));
	}
	 */
}

vector<char> BmpResourceExtraData::getData() {
	return data;
}

string BmpResourceExtraData::vToString() {
	return "BmpResourceExtraData";
}

} /* namespace base_game */

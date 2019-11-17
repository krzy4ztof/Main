/*
 * IResourceExtraData.cpp
 *
 *  Created on: 5 sie 2018
 *      Author: Krzysztof
 */

#include "IResourceExtraData.h"
#include "../debugging/Logger.h"

namespace base_game {

IResourceExtraData::IResourceExtraData() {
	logger::trace("Create IResourceExtraData");

}

IResourceExtraData::~IResourceExtraData() {
	logger::trace("Destroy IResourceExtraData");
}

} /* namespace base_game */

/*
 * MessageLoader.cpp
 *
 *  Created on: 12 lis 2018
 *      Author: Krzysztof
 */

#include "MessageLoader.h"
#include "MessageResourceExtraData.h"
#include "../debugging/Logger.h"

#include <string> // string
#include <memory> // shared_ptr

using std::string;
using std::shared_ptr;

namespace base_game {

MessageLoader::MessageLoader() {
	logger::info("Create MessageLoader");
}

MessageLoader::~MessageLoader() {
	logger::info("Destroy MessageLoader");
}

string MessageLoader::vGetPattern() {
	return "*.mo";
}

bool MessageLoader::vUseRawFile() {
	return false;
}

bool MessageLoader::vDiscardRawBufferAfterLoad() {
	return true;
	//return false;
}

uintmax_t MessageLoader::vGetLoadedResourceSize(char *rawBuffer,
		uintmax_t rawSize) {
	// ?
	return rawSize;
}

/*
bool MessageLoader::vAddNullZero() {
	//TODO: scriptLoader will return true
	return true;
}
 */

bool MessageLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {
	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<MessageResourceExtraData> pExtraData = shared_ptr<
			MessageResourceExtraData>(new MessageResourceExtraData());
	pExtraData->init(rawBuffer, rawSize);
	handle->setExtraData(pExtraData);

	return true;
}



namespace message_loader {
shared_ptr<IResourceLoader> createMessageLoader() {
	MessageLoader* loader = new MessageLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}
}

} /* namespace base_game */

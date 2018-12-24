/*
 * ScriptResourceLoader.cpp
 *
 *  Created on: 25 lis 2018
 *      Author: Krzysztof
 */

#include "ScriptResourceLoader.h"

//#include "ScriptResourceExtraData.h"
#include "../debugging/Logger.h"

#include <string> // string
#include <memory> // shared_ptr

using std::string;
using std::shared_ptr;

namespace base_game {

ScriptResourceLoader::ScriptResourceLoader() {
	logger::info("Create ScriptResourceLoader");

}

ScriptResourceLoader::~ScriptResourceLoader() {
	logger::info("Destroy ScriptResourceLoader");
}

string ScriptResourceLoader::vGetPattern() {
	return "*.lua";
}

bool ScriptResourceLoader::vUseRawFile() {
	// Modification of CodeComplete code due to modification in vLoadResource modification

	return true; // modyfikacja wzgl CodeComplete
	//return false;
}

bool ScriptResourceLoader::vDiscardRawBufferAfterLoad() {
	return true;
	//return false;
}

bool ScriptResourceLoader::vAddNullZero() {
	//TODO: scriptLoader will return true
	return true;
	//return false;
}


uintmax_t ScriptResourceLoader::vGetLoadedResourceSize(char *rawBuffer,
		uintmax_t rawSize) {
	// ?
	return rawSize;
}


bool ScriptResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {
	// ?


	if (rawSize <= 0) {
		return false;
	}

	return true;

	/*
	 * 	if (!g_pApp->m_pGame || g_pApp->m_pGame->CanRunLua())
	 LuaStateManager::Get()->VExecuteString(rawBuffer);
	 *
	 */

	/*
	shared_ptr<ScriptResourceExtraData> pExtraData = shared_ptr<
			ScriptResourceExtraData>(new ScriptResourceExtraData());

	pExtraData->init(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);
	 */
	/*
	shared_ptr < MessageResourceExtraData > pExtraData = shared_ptr
			< MessageResourceExtraData > (new MessageResourceExtraData());

	pExtraData->init(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);
	 */
	/*
	 shared_ptr<XmlResourceExtraData> pExtraData = shared_ptr<
	 XmlResourceExtraData>(new XmlResourceExtraData());
	 pExtraData->parseXml(rawBuffer, rawSize);

	 handle->setExtraData(pExtraData);
	 */

	return true;
}

namespace script_resource_loader {
shared_ptr<IResourceLoader> createScriptResourceLoader() {
	ScriptResourceLoader* loader = new ScriptResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}

}

} /* namespace base_game */

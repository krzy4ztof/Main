/*
 * ScriptResourceLoader.h
 *
 *  Created on: 25 lis 2018
 *      Author: Krzysztof
 */

#ifndef LUASCRIPTING_SCRIPTRESOURCELOADER_H_
#define LUASCRIPTING_SCRIPTRESOURCELOADER_H_

#include "../resourceCache/IResourceLoader.h"

#include <string> // string
#include <memory> // shared_ptr

namespace base_game {

class ScriptResourceLoader: public IResourceLoader {
public:
	ScriptResourceLoader();
	virtual ~ScriptResourceLoader();

	virtual bool vUseRawFile();

	virtual bool vDiscardRawBufferAfterLoad();

	virtual bool vAddNullZero();

	virtual boost::uintmax_t vGetLoadedResourceSize(char *rawBuffer,
			boost::uintmax_t rawSize);

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);

	virtual std::string vGetPattern();
};

namespace script_resource_loader {
std::shared_ptr<IResourceLoader> createScriptResourceLoader();
}

} /* namespace base_game */

#endif /* LUASCRIPTING_SCRIPTRESOURCELOADER_H_ */

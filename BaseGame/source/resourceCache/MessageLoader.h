/*
 * MessageLoader.h
 *
 *  Created on: 12 lis 2018
 *      Author: Krzysztof
 */

#ifndef RESOURCECACHE_MESSAGELOADER_H_
#define RESOURCECACHE_MESSAGELOADER_H_

#include "IResourceLoader.h"

#include <string> // string
#include <memory> // shared_ptr
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {

class MessageLoader: public IResourceLoader {
public:
	MessageLoader();
	virtual ~MessageLoader();

	virtual bool vUseRawFile();

	virtual bool vDiscardRawBufferAfterLoad();

	virtual boost::uintmax_t vGetLoadedResourceSize(char *rawBuffer,
			boost::uintmax_t rawSize);

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);

	virtual std::string vGetPattern();

	// virtual bool vAddNullZero();
};

namespace message_loader {
std::shared_ptr<IResourceLoader> createMessageLoader();
}

} /* namespace base_game */

#endif /* RESOURCECACHE_MESSAGELOADER_H_ */

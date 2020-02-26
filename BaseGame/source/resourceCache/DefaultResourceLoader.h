#ifndef DEFAULTRESOURCELOADER_H
#define DEFAULTRESOURCELOADER_H

#include "IResourceLoader.h"
#include "ResourceHandle.h"
#include <string> // string
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <memory> // shared_ptr

namespace base_game {
class DefaultResourceLoader: public IResourceLoader {
public:
	DefaultResourceLoader();
	virtual ~DefaultResourceLoader();

	virtual bool vUseRawFile();

	virtual bool vDiscardRawBufferAfterLoad();

	virtual boost::uintmax_t vGetLoadedResourceSize(char *rawBuffer,
			boost::uintmax_t rawSize);

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);

	virtual std::string vGetPattern();

protected:

private:
};
}

#endif // DEFAULTRESOURCELOADER_H

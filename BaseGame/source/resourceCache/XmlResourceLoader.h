#ifndef XMLRESOURCELOADER_H
#define XMLRESOURCELOADER_H

#include "IResourceLoader.h"
#include "ResourceHandle.h"
#include <memory> // shared_ptr
#include <string> // string
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {
class XmlResourceLoader: public IResourceLoader {
public:
	XmlResourceLoader();
	virtual ~XmlResourceLoader();

	virtual bool vUseRawFile() {
		return false;
	}

	virtual bool vDiscardRawBufferAfterLoad() {
		return true;
	}

	virtual boost::uintmax_t vGetLoadedResourceSize(char *rawBuffer,
			boost::uintmax_t rawSize) {
		return rawSize;
	}

	virtual bool vLoadResource(char *rawBuffer, boost::uintmax_t rawSize,
			std::shared_ptr<ResourceHandle> handle);

	virtual std::string vGetPattern();

protected:

private:
};

namespace xml_resource_loader {
std::shared_ptr<IResourceLoader> createXmlResourceLoader();
}
}
#endif // XMLRESOURCELOADER_H

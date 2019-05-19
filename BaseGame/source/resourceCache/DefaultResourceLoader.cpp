#include "DefaultResourceLoader.h"
#include "ResourceHandle.h"
#include "../debugging/Logger.h"

#include <string> // string
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <memory> // shared_ptr

using std::string;
using boost::uintmax_t;
using std::shared_ptr;

namespace base_game {
DefaultResourceLoader::DefaultResourceLoader() {
	logger::trace("Create DefaultResourceLoader");
}

DefaultResourceLoader::~DefaultResourceLoader() {
	logger::trace("Destroy DefaultResourceLoader");
}

string DefaultResourceLoader::vGetPattern() {
	return "*";
}

bool DefaultResourceLoader::vUseRawFile() {
	return true;
}

bool DefaultResourceLoader::vDiscardRawBufferAfterLoad() {
	return true;
}

uintmax_t DefaultResourceLoader::vGetLoadedResourceSize(char *rawBuffer,
		uintmax_t rawSize) {
	return rawSize;
}

bool DefaultResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {
	return true;
}

}

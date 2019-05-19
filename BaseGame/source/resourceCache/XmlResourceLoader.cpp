#include "XmlResourceLoader.h"
#include "../debugging/Logger.h"
#include "XmlResourceExtraData.h";

#include <memory> // shared_ptr
#include <string> // string
#include <boost/cstdint.hpp> // boost::uintmax_t

using std::shared_ptr;
using std::string;
using boost::uintmax_t;

namespace base_game {
XmlResourceLoader::XmlResourceLoader() {
	logger::trace("Create XmlResourceLoader");
}

XmlResourceLoader::~XmlResourceLoader() {
	logger::trace("Destroy XmlResourceLoader");
}

string XmlResourceLoader::vGetPattern() {
	return "*.xml";
}

bool XmlResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {

	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<XmlResourceExtraData> pExtraData = shared_ptr<
			XmlResourceExtraData>(new XmlResourceExtraData());
	pExtraData->parseXml(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);
//	handle->setExtraData(shared_ptr<XmlResourceExtraData>(pExtraData));

	return true;
}

namespace xml_resource_loader {
shared_ptr<IResourceLoader> createXmlResourceLoader() {
	XmlResourceLoader* loader = new XmlResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}
}
}

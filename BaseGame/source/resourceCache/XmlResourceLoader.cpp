#include "XmlResourceLoader.h"
#include "../debugging/Logger.h"

#include <memory> // shared_ptr
#include <string> // string
using std::shared_ptr;
using std::string;

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


	namespace xml_resource_loader {
		shared_ptr<IResourceLoader> createXmlResourceLoader() {
			XmlResourceLoader* loader = new XmlResourceLoader();
			shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
			return pointer;
		}
	}
}

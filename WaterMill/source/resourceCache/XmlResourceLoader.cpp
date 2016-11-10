#include "XmlResourceLoader.h"
#include "../debugging/Logger.h"

#include <memory> // shared_ptr
using std::shared_ptr;

namespace base_game {
	XmlResourceLoader::XmlResourceLoader() {
		logger::trace("Create XmlResourceLoader");
	}

	XmlResourceLoader::~XmlResourceLoader() {
		logger::trace("Destroy XmlResourceLoader");
	}

	namespace xml_resource_loader {
		shared_ptr<IResourceLoader> createXmlResourceLoader() {
			XmlResourceLoader* loader = new XmlResourceLoader();
			shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
			return pointer;
		}
	}
}

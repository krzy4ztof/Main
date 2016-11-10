#include "IResourceLoader.h"
#include "../debugging/Logger.h"

namespace base_game {
	IResourceLoader::IResourceLoader() {
		logger::trace("Create IResourceLoader");
	}

	IResourceLoader::~IResourceLoader() {
		logger::trace("Destroy IResourceLoader");
	}
}

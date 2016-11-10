#include "IResourceLoader.h"
#include "../debugging/Logger.h"

namespace base_game {
	IResourceLoader::IResourceLoader() {
		logger::info("Create IResourceLoader");
	}

	IResourceLoader::~IResourceLoader() {
		logger::info("Destroy IResourceLoader");
	}
}

#include "ResourceHandle.h"
#include "../debugging/Logger.h"
#include "Resource.h"

#include <sstream>      // std::stringstream

namespace base_game {
	ResourceHandle::ResourceHandle(Resource& resource):m_resource(resource) {
		logger::info("Create ResourceHandle");
	}

	ResourceHandle::~ResourceHandle() {
		logger::info("Destroy ResourceHandle");
	}

	Resource ResourceHandle::getResource() {
		return m_resource;
	}
}

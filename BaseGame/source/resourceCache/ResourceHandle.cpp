#include "ResourceHandle.h"
#include "../debugging/Logger.h"
#include "Resource.h"

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <sstream>      // std::stringstream
#include <memory> //std::shared_ptr
#include <string> // string

using boost::uintmax_t;
using std::shared_ptr;
using std::string;

namespace base_game {

ResourceHandle::ResourceHandle(Resource& resource, char *buffer,
		boost::uintmax_t size, ResourceCache *pResourceCache) :
		m_resource(resource), m_buffer(buffer), m_size(size), m_pResourceCache(
				pResourceCache) {

		logger::info("Create ResourceHandle");
	}

	ResourceHandle::~ResourceHandle() {
		logger::info("Destroy ResourceHandle");
	}

	Resource ResourceHandle::getResource() {
		return m_resource;
	}

const string ResourceHandle::getName() {
	return m_resource.getName();
}
;

uintmax_t ResourceHandle::getSize() const {
	return m_size;
}
;
char* ResourceHandle::getBuffer() const {
	return m_buffer;
}
;
	

std::shared_ptr<IResourceExtraData> ResourceHandle::getExtraData() {
	return m_extraData;
}

void ResourceHandle::setExtraData(
		std::shared_ptr<IResourceExtraData> extraData) {
	m_extraData = extraData;
}
}

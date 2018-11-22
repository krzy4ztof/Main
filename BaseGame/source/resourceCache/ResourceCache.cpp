#include "ResourceCache.h"
#include "IResourceFile.h"
#include "IResourceLoader.h"
#include "../debugging/Logger.h"
#include "../utilities/PropertyTreeUtils.h"
#include "../utilities/Templates.h"
#include "DefaultResourceLoader.h"

#include <sstream>      // std::stringstream

#include <string> // string
#include <list> // list
#include <map> // map

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp> // read_xml
#include <boost/optional.hpp> // boost::optional
#include <boost/cstdint.hpp> // boost::uintmax_t

using std::string;
using std::shared_ptr;
using std::stringstream;
using std::list;
using std::map;

using boost::property_tree::ptree;
using boost::property_tree::read_xml;
using boost::optional;
using boost::uintmax_t;

namespace base_game {

ResourceCache::ResourceCache(const string& assetsFolder,
		const unsigned int sizeInMb, shared_ptr<IResourceFile> shPtrResFile) {
	logger::info("Create ResourceCache");

	m_cacheSize = sizeInMb * 1024 * 1024;				// total memory size
	m_allocated = 0;								// total memory allocated
	m_resourceFile = shPtrResFile;
	this->assetsFolder = assetsFolder;
}

ResourceCache::~ResourceCache() {
	logger::info("Destroy ResourceCache");
	while (!m_resourceHandles.empty()) {
		freeOneResource();
	}

	m_resourceFile.reset();
	//templates::safe_delete<IResourceFile>(m_resourceFile);
	//SAFE_DELETE(m_file);

	/*
	 while (!m_lru.empty())
	 {
	 FreeOneResource();
	 }
	 SAFE_DELETE(m_file);
	 */

}

bool ResourceCache::init() {
	bool retValue = false;
	if (m_resourceFile->vOpen()) {
		registerLoader(
				shared_ptr<IResourceLoader>(new DefaultResourceLoader()));
		retValue = true;
	}
	return retValue;
}

//
// ResCache::RegisterLoader						- Chapter 8, page 225
//
//    The loaders are discussed on the page referenced above - this method simply adds the loader
//    to the resource cache.
//
void ResourceCache::registerLoader(shared_ptr<IResourceLoader> loader) {
	m_resourceLoaders.push_front(loader);
}

optional<shared_ptr<ResourceHandle>> ResourceCache::getHandle(
		Resource *resource) {
	logger::info("ResourceCache::getHandle");
	optional<shared_ptr<ResourceHandle>> handle(find(resource));
	//if (handle==NULL) {
	if (!handle.is_initialized()) {

		handle = load(resource);
		//GCC_ASSERT(handle);
	} else {
		update(handle.get());
	}
	return optional<shared_ptr<ResourceHandle>>(handle);
}

optional<shared_ptr<IResourceLoader>> ResourceCache::findResourceLoader(
		const Resource& resource) {

	// shared_ptr<IResourceLoader> loader;

	list<shared_ptr<IResourceLoader> >::iterator resourceLoadersIterator;

	// DefaultLoader appears at the m_resourceLoaders list as the last.
	// DefaultLoader is added to the m_resourceLoaders list in  ResourceCache::init()
	// Other loaders are added by ResourceCache::registerLoader
	// ResourceCache::registerLoader uses push_front to add the loader.
	// In this way first loader (i.e. DefaultLoader) becomes the last one during the iteration.
	for (resourceLoadersIterator = m_resourceLoaders.begin();
			resourceLoadersIterator != m_resourceLoaders.end();
			resourceLoadersIterator++) {

		stringstream ss;

		ss << "Pattern " << resourceLoadersIterator->get()->vGetPattern();

		logger::info(ss);

		bool result = (*resourceLoadersIterator)->matchesPattern(
				resource.getName());

		if (result) {

			return optional<shared_ptr<IResourceLoader>> {
					*resourceLoadersIterator };

//			return (*resourceLoadersIterator);
		}

		// WILDCARD MATCH - pattern compared to resource->getName()
	}

	return optional<shared_ptr<IResourceLoader>> { };

}

optional<shared_ptr<ResourceHandle>> ResourceCache::load(Resource* resource) {
	// see shared_ptr<ResHandle> ResCache::Load(Resource *r)

	// Find loader to load resource

	//std::list< std::shared_ptr < IResourceLoader > > m_resourceLoaders;
	stringstream ss;

	shared_ptr<ResourceHandle> handle;

	optional<shared_ptr<IResourceLoader>> loader = this->findResourceLoader(
			*resource);

	if (!loader.is_initialized()) {
		logger::error("Default resource loader not found!");
		return shared_ptr<ResourceHandle> { };

	}

	uintmax_t rawSize = m_resourceFile->vGetRawResourceSize(*resource);
	ss << "rawSize: " << rawSize;
	logger::info(ss);

	if (rawSize <= 0) {
		logger::error("Resource size returned -1 - Resource not found");

		return shared_ptr<ResourceHandle> { };
	}

	uintmax_t allocSize = rawSize;

	// string pat2 = loader->operator ->()->vGetPattern();

	if (loader.get()->vAddNullZero()) {
		allocSize += 1;
	}

	char* pRawBuffer = nullptr;
	if (loader.get()->vUseRawFile()) {
		pRawBuffer = allocate(allocSize);
	} else {
		// XML cannot be loaded as Raw File. Its contents need to be parsed first.
		pRawBuffer = new char[allocSize];
	}

	memset(pRawBuffer, 0, allocSize);

	if (pRawBuffer == nullptr) {
		return shared_ptr<ResourceHandle> { };
	}

	uintmax_t getRawResource = m_resourceFile->vGetRawResource(*resource,
			pRawBuffer);

	if (getRawResource <= 0) {
		return shared_ptr<ResourceHandle> { };
	}

	ss << "allocSizeX: " << allocSize;
	logger::info(ss);



	for (int i = 0; i < allocSize; i++) {
		ss << *(pRawBuffer + i);
		// ss << " | ";
	}

	logger::info(ss);

	char* pBuffer = nullptr;
	uintmax_t size = 0;
	
	if (loader.get()->vUseRawFile()) {
		pBuffer = pRawBuffer; //pRawBuffer already allocated

		handle = shared_ptr<ResourceHandle> { new ResourceHandle(*resource,
				pBuffer, rawSize, this) };
	} else {
		// XML cannot be loaded as Raw File. Its contents need to be parsed first.

		size = loader.get()->vGetLoadedResourceSize(pRawBuffer, rawSize);
		pBuffer = allocate(size);

		if (pRawBuffer == nullptr || pBuffer == nullptr) {
			return shared_ptr<ResourceHandle> { };
		}

		handle = shared_ptr<ResourceHandle> { new ResourceHandle(*resource,
				pBuffer, size, this) };

		bool success = loader.get()->vLoadResource(pRawBuffer, rawSize, handle);

		if (loader.get()->vDiscardRawBufferAfterLoad()) {
			templates::safe_delete_array<char>(pRawBuffer);

			/*
			if (pRawBuffer) {
				delete[] (pRawBuffer);
				(pRawBuffer) = nullptr;
			}
			 */
		}

		if (!success) {
			return shared_ptr<ResourceHandle> { };
		}


	}

	if (handle) {
		m_resourceHandles.push_front(handle);

		const string resourceName = handle->getResource().getName();

		m_resources[resourceName] = handle;
	}

	// Load resource with loader
	logger::info("ResourceCache::load");

	// return tempLoad(resource);
	return handle;

}

char* ResourceCache::allocate(uintmax_t size) {

	if (!makeRoom(size)) {
		return nullptr;
	}

	char* mem = new char[size];
	if (mem) {
		m_allocated += size;
	}

	return mem;
}

bool ResourceCache::makeRoom(uintmax_t size) {
	if (size > m_cacheSize) {
		return false;
	}

	// return null if there's no possible way to allocate the memory
	while (size > (m_cacheSize - m_allocated)) {
		// The cache is empty, and there's still not enough room.
		if (m_resourceHandles.empty()) // m_lru.empty()
			return false;

		freeOneResource();
	}

	return true;
}

/*
shared_ptr<ResourceHandle> ResourceCache::tempLoad(Resource *resource) {

	// this->m_resourceFile->vSaveFolderMode();
 this->m_resourceFile->vTempReadResource(*resource);

	shared_ptr<IResourceLoader> loader;
	shared_ptr<ResourceHandle> handle;

	handle = shared_ptr<ResourceHandle>(
			new ResourceHandle(*resource, nullptr, 0, nullptr));
	return handle;
}
 */

optional<shared_ptr<ResourceHandle>> ResourceCache::find(Resource * resource) {
	logger::info("ResourceCache::find");
	map<string, shared_ptr<ResourceHandle> >::iterator iter = m_resources.find(
			resource->getName());
	if (iter == m_resources.end())
		return optional<shared_ptr<ResourceHandle>> { };

	return optional<shared_ptr<ResourceHandle>>(iter->second);
}

//
// ResCache::Update									- Chapter 8, page 228
//
void ResourceCache::update(shared_ptr<ResourceHandle> handle) {
	logger::info("ResourceCache::update");
	m_resourceHandles.remove(handle);
	m_resourceHandles.push_front(handle);
}

void ResourceCache::freeOneResource() {
	list<shared_ptr<ResourceHandle> >::iterator gonner =
			m_resourceHandles.end();
	gonner--;

	shared_ptr<ResourceHandle> handle = *gonner;

	m_resourceHandles.pop_back();
	//m_resources.erase(handle->m_resource.m_name);
	m_resources.erase(handle->getResource().getName());

	// Note - you can't change the resource cache size yet - the resource bits could still actually be
	// used by some sybsystem holding onto the ResHandle. Only when it goes out of scope can the memory
	// be actually free again.
}

int ResourceCache::preLoad(const string& pattern) {
	return tempPreLoad(pattern);
}

int ResourceCache::tempPreLoad(const string& pattern) {

	Resource resource("TestImage.jpg");

	optional<shared_ptr<ResourceHandle>> handle = getHandle(&resource);

	return 1;
}

/*
 void ResourceCache::tempLoadAndReturnRootXmlElement(const string& resourceName, ptree& tree) {
 stringstream ss;
 ss << "tempLoadAndReturnRootXmlElement: " << assetsFolder << " + " << resourceName;
 logger::trace(ss);
 string filename = assetsFolder + resourceName;

 read_xml(filename, tree);
 }
 */

}

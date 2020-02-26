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
#include <regex>// std::regex, std::match

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp> // read_xml
#include <boost/optional.hpp> // boost::optional
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;  boost::filesystem::ifstream;

using std::string;
using std::shared_ptr;
using std::stringstream;
using std::list;
using std::map;
using std::regex;
using std::regex_match;

using boost::property_tree::ptree;
using boost::property_tree::read_xml;
using boost::optional;
using boost::uintmax_t;
using boost::filesystem::ofstream;
using boost::filesystem::path;

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
}

string ResourceCache::getAssetsFolder() {
	return assetsFolder;
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

	this->debugSaveAsFile(pRawBuffer, allocSize);

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

void ResourceCache::debugSaveAsFile(char* pRawBuffer, uintmax_t allocSize) {
	stringstream ss;
	string fileName = "debug_resource_cache";
	ss << "Debug-Save-As-File: " << fileName;
	logger::info(ss);

	path inPath { fileName };

	ofstream ofs(inPath, std::ios::binary);

	for (uintmax_t i = 0; i < allocSize; i++) {
		ofs << *(pRawBuffer + i);
	}

	//ofs << "x";
	//ofs << "y";

	// ofs.write(pRawBuffer, allocSize);
	ofs.close();
}

void ResourceCache::debugPrint() {
	stringstream ss;
	logger::info("debugPrint -> m_resourceHandles");

	list<shared_ptr<ResourceHandle>>::iterator itHandle;
	for (itHandle = m_resourceHandles.begin();
			itHandle != m_resourceHandles.end(); ++itHandle) {
		ss << (*itHandle)->getName();
		logger::info(ss);
	}
	logger::info("debugPrint -> m_resources");

	map<string, shared_ptr<ResourceHandle> >::iterator itResource;
	for (itResource = m_resources.begin(); itResource != m_resources.end();
			++itResource) {
		ss << itResource->first << " => " << itResource->second->getName();
		logger::info(ss);
	}
	logger::info("debugPrint -> end");

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
	stringstream ss;

	logger::info("ResourceCache::find");
	string name = resource->getName();
	ss << "Name: " << name;

	logger::info(ss);
	this->debugPrint();

	map<string, shared_ptr<ResourceHandle> >::iterator iter = m_resources.find(
			name);
	if (iter == m_resources.end())
		return optional<shared_ptr<ResourceHandle>> { };

	return optional<shared_ptr<ResourceHandle>>(iter->second);
}

//
// ResCache::Update									- Chapter 8, page 228
//
void ResourceCache::update(shared_ptr<ResourceHandle> handle) {
	logger::info("ResourceCache::update");

	// check
	m_resourceHandles.remove(handle);
	m_resourceHandles.push_front(handle);
}

/*
void ResourceCache::freeResource(Resource *resource) {
	optional<shared_ptr<ResourceHandle>> handle(find(resource));
	if (handle.is_initialized()) {
		this->free(*handle);
		//m_resourceHandles.remove(*handle);
		//m_resources.erase(resource->getName());
	}
}
 */

void ResourceCache::free(shared_ptr<ResourceHandle> gonner) {
	debugPrint();
	m_resourceHandles.remove(gonner);
	m_resources.erase(gonner->getResource().getName());
	debugPrint();

	// m_resourceHandles.pop_front();


	// Note - the resource might still be in use by something,
	// so the cache can't actually count the memory freed until the
	// ResHandle pointing to it is destroyed.

	//m_allocated -= gonner->m_resource.m_size;
	//delete gonner;
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

bool ResourceCache::wildcardMatch(const string& pattern,
		const string& resourceName) {

	stringstream ss;
	ss << "Pattern " << pattern << " fileName: " << resourceName;
	logger::info(ss);

	string regexExpr = "^\\S*\\." + pattern + "$";

	// string regexExpr = "^\\S*\\.txt$";
	regex expr { regexExpr };

	bool matchResult = regex_match(resourceName, expr);

	if (matchResult) {
		ss << resourceName << " MATCHES: " << pattern;
		logger::info(ss);

		return true;
	} else {
		ss << resourceName << " DOES NOT MATCH " << pattern;
		logger::info(ss);

		return false;

	}
}

int ResourceCache::preLoad(const string& pattern) {
	return this->preLoad(pattern, nullptr);
}

//int ResourceCache::preload(const string& pattern,
//		void (*progressCallback)()) {
int ResourceCache::preLoad(const string& pattern,
		void (*progressCallback)(int, bool&)) {
//	{

	stringstream ss;
	if (m_resourceFile == nullptr) {
		return 0;
	}

	int numFiles = m_resourceFile->vGetNumResources();
	int loaded = 0;
	bool cancel = false;

	for (int i = 0; i < numFiles; ++i) {
		string resourceName = m_resourceFile->vGetResourceName(i);

		ss << "ResourceName: " << resourceName;
		logger::info(ss);

		Resource resource(resourceName);

		if (this->wildcardMatch(pattern, resourceName)) {

			// shared_ptr<ResourceHandle> handle = this->getHandle(&resource);
			optional<shared_ptr<ResourceHandle>> handle = getHandle(&resource);

			++loaded;
		}

		/*
		 if (WildcardMatch(pattern.c_str(), resource.m_name.c_str())) {
		 shared_ptr<ResHandle> handle = g_pApp->m_ResCache->GetHandle(
		 &resource);
		 ++loaded;
		 }
		 */

		if (progressCallback != nullptr) {
			progressCallback(i * 100 / numFiles, cancel);
//			progressCallback();
		}
	}
	return loaded;

	/*
	 if (m_file == NULL)
	 return 0;

	 int numFiles = m_file->VGetNumResources();
	 int loaded = 0;
	 bool cancel = false;
	 for (int i = 0; i < numFiles; ++i) {
	 Resource resource(m_file->VGetResourceName(i));

	 if (WildcardMatch(pattern.c_str(), resource.m_name.c_str())) {
	 shared_ptr<ResHandle> handle = g_pApp->m_ResCache->GetHandle(
	 &resource);
	 ++loaded;
	 }

	 if (progressCallback != NULL) {
	 progressCallback(i * 100 / numFiles, cancel);
	 }
	 }
	 return loaded;
	 */

	// return tempPreLoad(pattern);
}

/*
 int ResourceCache::tempPreLoad(const string& pattern) {

 Resource resource("TestImage.jpg");

 optional<shared_ptr<ResourceHandle>> handle = getHandle(&resource);

 return 1;
 }
 */

/*
 void ResourceCache::tempLoadAndReturnRootXmlElement(const string& resourceName, ptree& tree) {
 stringstream ss;
 ss << "tempLoadAndReturnRootXmlElement: " << assetsFolder << " + " << resourceName;
 logger::trace(ss);
 string filename = assetsFolder + resourceName;

 read_xml(filename, tree);
 }
 */

namespace resource_cache {
void showPreLoadProgress(int progress, bool& cancel) {
	stringstream ss;
	ss << "Progress: " << progress << "%";
	logger::info(ss);
}
}

}

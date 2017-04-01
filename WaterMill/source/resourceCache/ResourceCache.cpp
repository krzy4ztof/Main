#include "ResourceCache.h"
#include "IResourceFile.h"
#include "IResourceLoader.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream


#include <string> // string
#include <list> // list
#include <map> // map

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "../utilities/PropertyTreeUtils.h"
#include "../utilities/Templates.h"
#include "DefaultResourceLoader.h"

using std::string;
using std::shared_ptr;
using std::stringstream;
using std::list;
using std::map;


using boost::property_tree::ptree;
using boost::property_tree::read_xml;

namespace base_game {

	ResourceCache::ResourceCache(const string& assetsFolder, const unsigned int sizeInMb, IResourceFile *resFile) {
		logger::info("Create ResourceCache");

		cacheSize = sizeInMb * 1024 * 1024;				// total memory size
		allocated = 0;									// total memory allocated
		m_resourceFile = resFile;
		this->assetsFolder = assetsFolder;
	}

	ResourceCache::~ResourceCache() {
		logger::info("Destroy ResourceCache");
		while (!m_resourceHandles.empty()) {
			freeOneResource();
		}

		templates::safe_delete<IResourceFile>(m_resourceFile);
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
		if ( m_resourceFile->vOpen() ) {
			registerLoader(shared_ptr<IResourceLoader>(new DefaultResourceLoader()));
			retValue = true;
		}
		return retValue;
	}

	//
	// ResCache::RegisterLoader						- Chapter 8, page 225
	//
	//    The loaders are discussed on the page refereced above - this method simply adds the loader
	//    to the resource cache.
	//
	void ResourceCache::registerLoader(shared_ptr<IResourceLoader> loader ) {
		m_resourceLoaders.push_front(loader);
	}

	shared_ptr<ResourceHandle> ResourceCache::getHandle(Resource *resource) {
		logger::info("ResourceCache::getHandle");
		shared_ptr<ResourceHandle> handle(find(resource));
		//if (handle==NULL) {
		if (handle==nullptr) {

			handle = load(resource);
			//GCC_ASSERT(handle);
		} else {
			update(handle);
		}
		return handle;
	}

	shared_ptr<ResourceHandle> ResourceCache::load(Resource *resource) {
	logger::info("ResourceCache::load");
	return tempLoad(resource);
	}

	shared_ptr<ResourceHandle> ResourceCache::tempLoad(Resource *resource) {
		shared_ptr<IResourceLoader> loader;
		shared_ptr<ResourceHandle> handle;

		handle = shared_ptr<ResourceHandle>(new ResourceHandle(*resource));
		return handle;
	}

	shared_ptr<ResourceHandle> ResourceCache::find(Resource * resource) {
	logger::info("ResourceCache::find");
		map<string, shared_ptr < ResourceHandle  > >::iterator iter = m_resources.find(resource->getName());
		if (iter==m_resources.end())
			return shared_ptr<ResourceHandle>();

		return iter->second;
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
		list< shared_ptr <ResourceHandle > >::iterator gonner = m_resourceHandles.end();
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

		shared_ptr<ResourceHandle> handle = getHandle(&resource);


		return 1;
	}




	void ResourceCache::tempLoadAndReturnRootXmlElement(const string& resourceName, ptree& tree) {
		stringstream ss;
		ss << "tempLoadAndReturnRootXmlElement: " << assetsFolder << " + " << resourceName;
		logger::trace(ss);
		string filename = assetsFolder + resourceName;

		read_xml(filename, tree);
	}



}

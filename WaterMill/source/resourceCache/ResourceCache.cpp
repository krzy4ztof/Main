#include "ResourceCache.h"
#include "IResourceFile.h"
#include "IResourceLoader.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream


#include <string> // string

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "../utilities/PropertyTreeUtils.h"

using std::string;
using std::shared_ptr;
using std::stringstream;

using boost::property_tree::ptree;
using boost::property_tree::read_xml;


namespace base_game {

	ResourceCache::ResourceCache(const string& assetsFolder, const unsigned int sizeInMb, IResourceFile *resFile) {
		//ctor
		cacheSize = sizeInMb * 1024 * 1024;				// total memory size
		allocated = 0;									// total memory allocated
		resourceFile = resFile;

		//	assetsFolder = assetsFolderX;
		this->assetsFolder = assetsFolder;
	}

	ResourceCache::~ResourceCache() {
		//dtor
	}

	int ResourceCache::preLoad(const string& pattern) {
		return 1;
	}

	//
	// ResCache::RegisterLoader						- Chapter 8, page 225
	//
	//    The loaders are discussed on the page refereced above - this method simply adds the loader
	//    to the resource cache.
	//
	void ResourceCache::registerLoader(shared_ptr<IResourceLoader> loader ) {
		resourceLoaders.push_front(loader);
	}


	void ResourceCache::tempLoadAndReturnRootXmlElement(const string& resourceName, ptree& tree) {
		stringstream ss;
		ss << "tempLoadAndReturnRootXmlElement: " << assetsFolder << " + " << resourceName;
		logger::info(ss);

		string filename = assetsFolder + "actors/" + resourceName;

		//ptree tree;
		read_xml(filename, tree);

		//property_tree_utils::print_tree(tree,0);

		//		loadRootNode(tree);
		//return tree;
	}

	namespace resource_cache {
		void safe_delete(ResourceCache* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}
}

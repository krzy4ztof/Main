#include "ResourceCache.h"
#include "IResourceFile.h"

namespace watermill {

	ResourceCache::ResourceCache(const unsigned int sizeInMb, IResourceFile *resFile) {
		//ctor
		cacheSize = sizeInMb * 1024 * 1024;				// total memory size
		allocated = 0;									// total memory allocated
		resourceFile = resFile;
	}

	ResourceCache::~ResourceCache() {
		//dtor
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

#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H
#include "IResourceFile.h"

namespace watermill {
	class ResourceCache {
		public:
			ResourceCache(const unsigned int sizeInMb, IResourceFile *file);
			virtual ~ResourceCache();

		protected:

		private:
			IResourceFile *resourceFile;

			unsigned int cacheSize;			// total memory size
			unsigned int allocated;			// total memory allocated
	};
}
#endif // RESOURCECACHE_H

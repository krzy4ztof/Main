#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H
#include "IResourceFile.h"
#include "IResourceLoader.h"

#include <string> // string
#include <memory> // shared_ptr
#include <list> // list
#include <boost/property_tree/ptree.hpp> // ptree

namespace base_game {
	class ResourceCache {
		public:
			ResourceCache(const std::string& assetsFolder, const unsigned int sizeInMb, IResourceFile *file);
			virtual ~ResourceCache();
			int preLoad(const std::string& pattern);
			void registerLoader( std::shared_ptr<IResourceLoader> loader );

			void tempLoadAndReturnRootXmlElement(const std::string& resourceName, boost::property_tree::ptree& tree);

		protected:

		private:
			std::list< std::shared_ptr < IResourceLoader > > resourceLoaders;

			IResourceFile *resourceFile;

			unsigned int cacheSize;			// total memory size
			unsigned int allocated;			// total memory allocated
			std::string assetsFolder;
	};
}
#endif // RESOURCECACHE_H

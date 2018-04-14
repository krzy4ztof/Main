#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H
#include "IResourceFile.h"
#include "IResourceLoader.h"
#include "ResourceHandle.h"


#include <string> // string
#include <memory> // shared_ptr
#include <list> // list
#include <map> // map
#include <boost/property_tree/ptree.hpp> // ptree
#include <boost/optional.hpp> // boost::optional


namespace base_game {
	class ResourceCache {
		public:
	ResourceCache(const std::string& assetsFolder, const unsigned int sizeInMb,
			std::shared_ptr<IResourceFile> shPtrFile);
			virtual ~ResourceCache();

			bool init();
			void registerLoader( std::shared_ptr<IResourceLoader> loader );


			boost::optional<std::shared_ptr<ResourceHandle>> getHandle(
			Resource* resource);

			int preLoad(const std::string& pattern);
			int tempPreLoad(const std::string& pattern);

	std::string tempGetAssetsFolder() {
		return assetsFolder;
	}
	;

		//	void tempLoadAndReturnRootXmlElement(const std::string& resourceName, boost::property_tree::ptree& tree);

		protected:
	boost::optional<std::shared_ptr<ResourceHandle>> load(Resource* resource);
	boost::optional<std::shared_ptr<IResourceLoader>> findResourceLoader(
			const Resource& resource);



			std::shared_ptr<ResourceHandle> tempLoad(Resource * r);
	boost::optional<std::shared_ptr<ResourceHandle>> find(Resource * r);
	void update(std::shared_ptr<ResourceHandle> handle);
		void freeOneResource();
		
		

		private:
			std::list< std::shared_ptr <ResourceHandle > > m_resourceHandles;							// lru list
			std::map<std::string, std::shared_ptr < ResourceHandle  > > m_resources;
			std::list< std::shared_ptr < IResourceLoader > > m_resourceLoaders;

	std::shared_ptr<IResourceFile> m_resourceFile; //m_file

			unsigned int cacheSize;			// total memory size
			unsigned int allocated;			// total memory allocated
			std::string assetsFolder;
	};
}
#endif // RESOURCECACHE_H

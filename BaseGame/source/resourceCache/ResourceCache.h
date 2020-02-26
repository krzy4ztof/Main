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
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {
class ResourceCache {
public:
	ResourceCache(const std::string& assetsFolder, const unsigned int sizeInMb,
			std::shared_ptr<IResourceFile> shPtrFile);
	virtual ~ResourceCache();

	bool init();
	void registerLoader(std::shared_ptr<IResourceLoader> loader);

	boost::optional<std::shared_ptr<ResourceHandle>> getHandle(
			Resource* resource);

	int preLoad(const std::string& pattern,
			void (*progressCallback)(int, bool&));
	int preLoad(const std::string& pattern);
	std::string getAssetsFolder();

//	void freeResource(Resource *resource);
	void free(std::shared_ptr<ResourceHandle> gonner);

	void debugPrint();
protected:
	boost::optional<std::shared_ptr<ResourceHandle>> load(Resource* resource);
	boost::optional<std::shared_ptr<IResourceLoader>> findResourceLoader(
			const Resource& resource);
	boost::optional<std::shared_ptr<ResourceHandle>> find(Resource * r);
	void update(std::shared_ptr<ResourceHandle> handle);
	void freeOneResource();


	bool makeRoom(boost::uintmax_t size);
	char* allocate(boost::uintmax_t size);
	void debugSaveAsFile(char* pRawBuffer, uintmax_t allocSize);

	bool wildcardMatch(const std::string& pattern,
			const std::string& resourceName);

private:
	std::list<std::shared_ptr<ResourceHandle> > m_resourceHandles;	// lru list
	std::map<std::string, std::shared_ptr<ResourceHandle> > m_resources;
	std::list<std::shared_ptr<IResourceLoader> > m_resourceLoaders;

	std::shared_ptr<IResourceFile> m_resourceFile; //m_file

	unsigned int m_cacheSize;			// total memory size
	unsigned int m_allocated;			// total memory allocated
	std::string assetsFolder;
};

namespace resource_cache {
void showPreLoadProgress(int progress, bool& cancel);

}
}
#endif // RESOURCECACHE_H

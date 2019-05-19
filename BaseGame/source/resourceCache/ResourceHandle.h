#ifndef RESOURCEHANDLE_H
#define RESOURCEHANDLE_H

#include "Resource.h"
//#include "ResourceCache.h"
#include "IResourceExtraData.h"

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <memory> // shared_ptr
#include <string> // string

namespace base_game {
class ResourceCache;

class ResourceHandle {
public:
	ResourceHandle(Resource& resource, char *buffer, boost::uintmax_t size,
			ResourceCache *pResourceCache);

	virtual ~ResourceHandle();
	Resource getResource();

	const std::string getName();
	boost::uintmax_t getSize() const;
	char* getBuffer() const;

	std::shared_ptr<IResourceExtraData> getExtraData();
	void setExtraData(std::shared_ptr<IResourceExtraData> extraData);

	/*
	 * 	const std::string GetName() { return m_resource.m_name; }
	 unsigned int Size() const { return m_size; }
	 char *Buffer() const { return m_buffer; }
	 char *WritableBuffer() { return m_buffer; }

	 shared_ptr<IResourceExtraData> GetExtra() { return m_extra; }
	 void SetExtra(shared_ptr<IResourceExtraData> extra) { m_extra = extra; }
	 */

protected:
	Resource m_resource;
	char* m_buffer;
	boost::uintmax_t m_size;
	std::shared_ptr<IResourceExtraData> m_extraData;
	ResourceCache *m_pResourceCache;

private:
};
}

#endif // RESOURCEHANDLE_H

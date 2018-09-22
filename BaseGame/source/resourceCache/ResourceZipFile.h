#ifndef RESOURCEZIPFILE_H
#define RESOURCEZIPFILE_H

#include "IResourceFile.h"
#include "ZipFile.h"
//#include "Resource.h"

#include <string> //string
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {
class ResourceZipFile: public IResourceFile {
public:
	ResourceZipFile(const std::string folderName, const std::string fileName);

	virtual ~ResourceZipFile();
	virtual bool vOpen();
	//		virtual bool vSave(const std::string saveMode);
	//virtual void vTempReadResource(const Resource& resource);
	virtual boost::uintmax_t vGetRawResourceSize(const Resource& resource);
	virtual boost::uintmax_t vGetRawResource(const Resource& resource,
			char *buffer);

protected:
	virtual bool vSaveFolderMode(const std::string outputFolderName);
	virtual bool vSaveUnzipMode(const std::string outputUnzipFileName);
	virtual bool vSaveZipMode(const std::string outputZipFileName);

private:
	ZipFile *m_pZipFile;
	std::string m_resFileName;
	//	std::string m_readMode;
};
}
#endif // RESOURCEZIPFILE_H

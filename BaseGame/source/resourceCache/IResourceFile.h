#ifndef IRESOURCEFILE_H
#define IRESOURCEFILE_H

#include "Resource.h"

#include <string>
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {
class IResourceFile {
public:
	IResourceFile(const std::string rootFolder);

	const static std::string ASSETS_READ_MODE_FOLDER;
	const static std::string ASSETS_READ_MODE_ZIPFILE;
	const static std::string ASSETS_READ_MODE_UNZIPFILE;

	const static std::string ASSETS_SAVE_MODE_NONE;
	const static std::string ASSETS_SAVE_MODE_FOLDER;
	const static std::string ASSETS_SAVE_MODE_ZIPFILE;
	const static std::string ASSETS_SAVE_MODE_UNZIPFILE;

	const static std::string ASSETS_FOLDER_TO_FOLDER;

	const static std::string ASSETS_FOLDER;
	const static std::string ASSETS_UNZIP_FILE;
	const static std::string ASSETS_ZIP_FILE;

	const static std::string ASSETS_UNZIP_TO_FOLDER;
	const static std::string ASSETS_UNZIP_TO_UNZIP;
	const static std::string ASSETS_UNZIP_TO_ZIP;

	const static std::string ASSETS_ZIP_TO_FOLDER;
	const static std::string ASSETS_ZIP_TO_UNZIP;
	const static std::string ASSETS_ZIP_TO_ZIP;

	virtual ~IResourceFile();
	virtual bool vOpen()=0;

//	virtual void vTempReadResource(const Resource& resource)=0;
	virtual boost::uintmax_t vGetRawResourceSize(const Resource& resource)=0;
	virtual boost::uintmax_t vGetRawResource(const Resource& resource,
			char *buffer)=0;
	
	//virtual int VGetNumResources() const = 0;
	//virtual std::string VGetResourceName(int num) const = 0;
	//virtual bool VIsUsingDevelopmentDirectories(void) const = 0;


	virtual bool vSave(const std::string saveMode,
			const std::string outputName);

protected:
	std::string m_rootFolder;

	virtual bool vSaveFolderMode(const std::string outputFolderName)=0;
	virtual bool vSaveUnzipMode(const std::string outputUnzipFileName)=0;
	virtual bool vSaveZipMode(const std::string outputZipFileName)=0;

private:
};
}
#endif // IRESOURCEFILE_H

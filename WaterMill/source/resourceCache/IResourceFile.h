#ifndef IRESOURCEFILE_H
#define IRESOURCEFILE_H

#include <string>

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
//	const static std::string ASSETS_DEV_UNZIP_FOLDER;
//	const static std::string ASSETS_DEV_ZIP_FOLDER;

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

//			virtual bool vSave(const std::string saveMode)=0;
	virtual bool vSave(const std::string saveMode);

protected:
	std::string m_rootFolder;

	virtual bool vSaveFolderMode()=0;
	virtual bool vSaveUnzipMode()=0;
	virtual bool vSaveZipMode()=0;
//	virtual bool vCreateFolder(boost::filesystem::path newFolder);

private:
};
}
#endif // IRESOURCEFILE_H

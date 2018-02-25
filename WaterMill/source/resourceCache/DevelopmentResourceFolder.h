/*
 * DevelopmentResourceFolder.h
 *
 *  Created on: 25.06.2017
 *      Author: Krzysztof
 */

#ifndef SOURCE_RESOURCECACHE_DEVELOPMENTRESOURCEFOLDER_H_
#define SOURCE_RESOURCECACHE_DEVELOPMENTRESOURCEFOLDER_H_

//#include "ResourceZipFile.h"
#include "IResourceFile.h"
#include "TZipDirFileHeader.h"
#include "TZipDirHeader.h"
#include "TZipLocalHeader.h"

#include <string> //string
#include <vector> //vector

#include <boost/filesystem.hpp> // boost::filesystem::path;

namespace base_game {

class DevelopmentResourceFolder: public IResourceFile {
public:

	DevelopmentResourceFolder(const std::string rootFolder,
			const std::string assetsFolder);

//	DevelopmentResourceZipFile(const std::string fileName, const std::string readMode, const std::string assetsFolder);
	//DevelopmentResourceFolder();
	virtual ~DevelopmentResourceFolder();

	virtual bool vOpen();
//	virtual bool vSave(const std::string saveMode);

protected:
	bool readAssetsDirectory(); //const std::string assetsFolder);

	virtual bool vSaveFolderMode();
	bool prepareOutputDir(const std::string folderName);
	bool createFilesAndFolders(const std::string folderName);

	bool createFolder(boost::filesystem::path newFolder);

	bool copyFile(boost::filesystem::path inPath,
			boost::filesystem::path outFolder);
	std::string getOutputFolderName(const std::string folderName);
	bool fileToIgnore(boost::filesystem::path filePath);

	virtual bool vSaveUnzipMode();
	bool createUnzipFile_222(const std::string folderName,
			const std::string assetsUnzipFile);

	bool saveUnzipAsset_222(boost::filesystem::ofstream& ofs,
			const boost::filesystem::path resourceFilePath,
			const std::string shortFileName,
			std::list<TZipDirFileHeader*>& dirFileHeadersList,
			const TZipDirHeader& dh);

	virtual bool vSaveZipMode();
	bool createZipFile_222(const std::string folderName,
			const std::string assetsUnzipFile);

	bool saveZipAsset_222(boost::filesystem::ofstream& ofs,
			const boost::filesystem::path resourceFilePath,
			const std::string shortFileName,
			std::list<TZipDirFileHeader*>& dirFileHeadersList,
			const TZipDirHeader& dh);

	bool createAssetFile(const std::string folderName,
			const std::string assetsUnzipFile, const std::string saveMode);

	bool saveAsset(boost::filesystem::ofstream& ofs,
			const boost::filesystem::path resourceFilePath,
			const std::string shortFileName,
			std::list<TZipDirFileHeader*>& dirFileHeadersList,
			const TZipDirHeader& dh, const std::string saveMode);

	bool saveAssetFileName(TZipLocalHeader& lh,
			boost::filesystem::ofstream& ofs, const std::string shortFileName,
			const std::string saveMode);

	bool saveAssetFileContents(boost::filesystem::ofstream& ofs,
			const boost::filesystem::path resourceFilePath,
			const std::string saveMode, std::vector<char>& vecFileContents);

private:
	std::string m_assetsFolder;

	std::vector<boost::filesystem::path> m_paths;

};

} /* namespace base_game */

#endif /* SOURCE_RESOURCECACHE_DEVELOPMENTRESOURCEFOLDER_H_ */

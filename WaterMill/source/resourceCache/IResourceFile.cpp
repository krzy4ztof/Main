#include "IResourceFile.h"
#include "../debugging/Logger.h"
#include <string>
//#include <sstream>      // std::stringstream
//#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;

using std::string;

/*
 using std::stringstream;

 using boost::filesystem::path;
 using boost::filesystem::filesystem_error;
 using boost::filesystem::create_directory;
 */

namespace base_game {

const string IResourceFile::ASSETS_READ_MODE_FOLDER = "folder";
const string IResourceFile::ASSETS_READ_MODE_ZIPFILE = "zipFile";
const string IResourceFile::ASSETS_READ_MODE_UNZIPFILE = "unzipFile";

const string IResourceFile::ASSETS_SAVE_MODE_NONE = "none";
const string IResourceFile::ASSETS_SAVE_MODE_FOLDER = "folder";
const string IResourceFile::ASSETS_SAVE_MODE_ZIPFILE = "zipFile";
const string IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE = "unzipFile";

const string IResourceFile::ASSETS_FOLDER_TO_FOLDER = "assetsFolderToFolder";
//const string IResourceFile::ASSETS_DEV_UNZIP_FOLDER = "assetsDevUnzip";
//const string IResourceFile::ASSETS_DEV_ZIP_FOLDER = "assetsDevZip";

const string IResourceFile::ASSETS_FOLDER = "assets";
const string IResourceFile::ASSETS_UNZIP_FILE = "assetsUnzip.zip";
const string IResourceFile::ASSETS_ZIP_FILE = "assets.zip";

const string IResourceFile::ASSETS_UNZIP_TO_FOLDER = "assetsUnzipToFolder";
const string IResourceFile::ASSETS_UNZIP_TO_UNZIP = "assetsUnzipToUnzip.zip";
const string IResourceFile::ASSETS_UNZIP_TO_ZIP = "assetsUnzipToZip.zip";

const string IResourceFile::ASSETS_ZIP_TO_FOLDER = "assetsZipToFolder";
const string IResourceFile::ASSETS_ZIP_TO_UNZIP = "assetsZipToUnzip.zip";
const string IResourceFile::ASSETS_ZIP_TO_ZIP = "assetsZipToZip.zip";

IResourceFile::IResourceFile(const string rootFolder) :
		m_rootFolder(rootFolder) {
	logger::info("Create IResourceFile(rootFolder)");
//	m_assetsFolder = assetsFolder;

}

IResourceFile::~IResourceFile() {
	logger::info("Destroy IResourceFile");
}

bool IResourceFile::vSave(const string saveMode) {

	if (IResourceFile::ASSETS_SAVE_MODE_FOLDER.compare(saveMode) == 0) {
		vSaveFolderMode();
	} else if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode)
			== 0) {
		vSaveUnzipMode();
	} else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
		vSaveZipMode();
	}

	return true;
}
/*
 bool IResourceFile::vCreateFolder(path newFolder) {
 stringstream ss;

 if (exists(newFolder)) {
 //	ss << "ALREADY EXISTS: " << newFolder.string();
 //	logger::info(ss);

 } else {
 //	ss << "CREATING NEW: " << newFolder.string();
 //	logger::info(ss);

 path newSubFolder { };
 for (path element : newFolder) {
 newSubFolder /= element;

 try {

 create_directory(newSubFolder);
 } catch (filesystem_error &ex) {
 logger::error(ex.what());
 }
 }
 }

 return true;
 }
 */
}

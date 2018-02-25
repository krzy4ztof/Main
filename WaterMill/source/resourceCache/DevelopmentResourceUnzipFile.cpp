/*
 * DevelopmentResourceUnzipFile.cpp
 *
 *  Created on: 29.10.2017
 *      Author: Krzysztof
 */

#include "DevelopmentResourceUnzipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"
//#include "TZipDirFileHeader.h"
//#include "TZipDirHeader.h"
//#include "TZipLocalHeader.h"

#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;  boost::filesystem::ifstream;

//#include <boost/iostreams/filtering_streambuf.hpp> // filtering_istreambuf
//#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
//#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device

#include <string>
#include <sstream>      // std::stringstream
//#include <vector> // vector

using std::string;
using std::stringstream;
//using std::vector;

using boost::filesystem::path;
using boost::filesystem::ifstream;

//using boost::iostreams::filtering_istreambuf;
//using boost::iostreams::back_inserter;

namespace base_game {

//DevelopmentResourceUnzipFile::DevelopmentResourceUnzipFile() {
// TODO Auto-generated constructor stub

//}

DevelopmentResourceUnzipFile::DevelopmentResourceUnzipFile(
		const string folderName, const string fileName) :
		IResourceFile(folderName), m_resFileName(fileName) {
	logger::info("Create DevelopmentResourceUnzipFile(folderName, fileName)");

	m_pZipFile = nullptr;

//	m_readMode = "zipFile";
//	m_pZipFile = nullptr;
//	m_resFileName = fileName;
}

DevelopmentResourceUnzipFile::~DevelopmentResourceUnzipFile() {
	logger::info("Destroy DevelopmentResourceUnzipFile");
	templates::safe_delete<ZipFile>(m_pZipFile);
}

bool DevelopmentResourceUnzipFile::vOpen() {

	templates::safe_delete<ZipFile>(m_pZipFile);
	m_pZipFile = new ZipFile();

	/*	m_pZipFile = new ZipFile();
	 if (m_pZipFile) {
	 return m_pZipFile->init(m_resFileName);
	 }
	 */
	//return readUnzipAssets();
	//return false;
	stringstream ss;
	string fileName = this->m_rootFolder + "/" + this->m_resFileName;

//	if (m_pZipFile) {
	//bool result = m_pZipFile->initNotCompressed(fileName);
	bool result = m_pZipFile->init(fileName, ZipFile::NOT_COMPRESSED);

	m_pZipFile->describeYourself();
	return result;
//	}

	return false;
}

/*
 bool DevelopmentResourceUnzipFile::readUnzipAssets() {

 stringstream ss;
 string fileName = this->m_rootFolder + "/" + this->m_resFileName;

 bool result = m_pZipFile->initNotCompressed(fileName);
 return result;
 }
 */

/*
 bool DevelopmentResourceUnzipFile::vSave(const string saveMode) {
 return true;
 }*/

bool DevelopmentResourceUnzipFile::vSaveFolderMode() {
	stringstream ss;
	ss << "VSAVE: " << m_rootFolder;
	logger::info(ss);

	// assetsOutFolder = m_assetsFolder;
	//string assetFolder = m_rootFolder + "/"
	//		+ IResourceFile::ASSETS_UNZIP_TO_FOLDER;

	//string folderFullName = getOutputFolderName(assetsFolder);

	string folderFullName = m_rootFolder + "/"
			+ IResourceFile::ASSETS_UNZIP_TO_FOLDER;

	m_pZipFile->saveAsFolder(folderFullName);

	//prepareOutputDir(folderFullName);
	//createFilesAndFolders(folderFullName);

	return true;
}

bool DevelopmentResourceUnzipFile::vSaveUnzipMode() {

	string fileName = m_rootFolder + "/" + IResourceFile::ASSETS_UNZIP_TO_UNZIP;

	//m_pZipFile->saveNotCompressed(fileName);
	m_pZipFile->save(fileName, ZipFile::NOT_COMPRESSED);

//	stringstream ss;
//	ss << "VSAVE: " << m_assetsFolder;
//	logger::info(ss);

	//string assetsDevUnzip = IResourceFile::ASSETS_DEV_UNZIP_FOLDER;
	//string assetsUnzipFile = IResourceFile::ASSETS_UNZIP_FILE;
	//string folderFullName = getOutputFolderName(assetsDevUnzip);

	//prepareOutputDir(this->m_rootFolder);
//	createUnzipFile_222(this->m_rootFolder, assetsUnzipFile);

	return true;
}

bool DevelopmentResourceUnzipFile::vSaveZipMode() {

	string fileName = m_rootFolder + "/" + IResourceFile::ASSETS_UNZIP_TO_ZIP;

	//m_pZipFile->saveNotCompressed(fileName);

	m_pZipFile->save(fileName, ZipFile::COMPRESSED);

	return true;
}

} /* namespace base_game */

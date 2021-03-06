/*
 * DevelopmentResourceUnzipFile.cpp
 *
 *  Created on: 29.10.2017
 *      Author: Krzysztof
 */

#include "DevelopmentResourceUnzipFile.h"
#include "ZipFileAsset.h"
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

#include <boost/cstdint.hpp> // boost::uintmax_t

using std::string;
using std::stringstream;
//using std::vector;

using boost::filesystem::path;
using boost::filesystem::ifstream;

using boost::uintmax_t;

//using boost::iostreams::filtering_istreambuf;
//using boost::iostreams::back_inserter;

namespace base_game {

DevelopmentResourceUnzipFile::DevelopmentResourceUnzipFile(
		const string folderName, const string fileName) :
		IResourceFile(folderName), m_resFileName(fileName) {
	logger::info("Create DevelopmentResourceUnzipFile(folderName, fileName)");

	m_pZipFile = nullptr;
}

DevelopmentResourceUnzipFile::~DevelopmentResourceUnzipFile() {
	logger::info("Destroy DevelopmentResourceUnzipFile");
	templates::safe_delete<ZipFile>(m_pZipFile);
}

bool DevelopmentResourceUnzipFile::vOpen() {

	templates::safe_delete<ZipFile>(m_pZipFile);
	m_pZipFile = new ZipFile();

	stringstream ss;
	string fileName = this->m_rootFolder + "/" + this->m_resFileName;

	bool result = m_pZipFile->init(fileName, ZipFile::NOT_COMPRESSED);

	m_pZipFile->describeYourself();
	return result;

	return false;
}

/*
 void DevelopmentResourceUnzipFile::vTempReadResource(const Resource& resource) {
 stringstream ss;
 ss << "DevelopmentResourceUnzipFile::vTempReadResource: ";
 //		<< resource.getName();

 logger::info(ss);
 }
 */

uintmax_t DevelopmentResourceUnzipFile::vGetRawResource(
		const Resource& resource, char *buffer) {
	ZipFileAsset* pZipFileAsset = m_pZipFile->find(resource.getName());

	uintmax_t size = 0;
	if (pZipFileAsset) {
		size = pZipFileAsset->getFileDataSize();

		pZipFileAsset->readFile(buffer);

	}

	return size;
}

uintmax_t DevelopmentResourceUnzipFile::vGetRawResourceSize(
		const Resource &resource) {

	ZipFileAsset* pZipFileAsset = m_pZipFile->find(resource.getName());

	uintmax_t size = 0;
	if (pZipFileAsset) {
		size = pZipFileAsset->getFileDataSize();
	}

	/*
	 * 	int resourceNum = m_pZipFile->Find(r.m_name.c_str());
	 if (resourceNum == -1)
	 return -1;

	 return m_pZipFile->GetFileLen(resourceNum);
	 */

	return size;
}

bool DevelopmentResourceUnzipFile::vSaveFolderMode(
		const string outputFolderName) {
	stringstream ss;
	ss << "VSAVE: " << m_rootFolder;
	logger::info(ss);

	string folderFullName = m_rootFolder + "/" + outputFolderName;
	// + IResourceFile::ASSETS_UNZIP_TO_FOLDER;

	m_pZipFile->saveAsFolder(folderFullName);

	return true;
}

bool DevelopmentResourceUnzipFile::vSaveUnzipMode(
		const string outputUnzipFileName) {
	string fileName = m_rootFolder + "/" + outputUnzipFileName;
	// IResourceFile::ASSETS_UNZIP_TO_UNZIP;
	m_pZipFile->save(fileName, ZipFile::NOT_COMPRESSED);

	return true;
}

bool DevelopmentResourceUnzipFile::vSaveZipMode(
		const string outputZipFileName) {
	string fileName = m_rootFolder + "/" + outputZipFileName;
	// IResourceFile::ASSETS_UNZIP_TO_ZIP;
	m_pZipFile->save(fileName, ZipFile::COMPRESSED);

	return true;
}

int DevelopmentResourceUnzipFile::vGetNumResources() const {

	if (m_pZipFile == nullptr) {
		return 0;
	} else {
		unsigned short numFiles = m_pZipFile->getNumberOfEntries();
		return numFiles;
	}
}

string DevelopmentResourceUnzipFile::vGetResourceName(int num) const {
	std::string resName = "";
	if (m_pZipFile == nullptr) {
		return resName;
	}

	unsigned short numFiles = m_pZipFile->getNumberOfEntries();
	if (num >= 0 && num < numFiles) {
		resName = m_pZipFile->getFilename(num);
	}

	return resName;
}

} /* namespace base_game */

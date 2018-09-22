#include "ResourceZipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"

#include <string>
#include <sstream>      // std::stringstream
#include <boost/cstdint.hpp> // boost::uintmax_t

using std::string;
using std::stringstream;

using boost::uintmax_t;

namespace base_game {
//	ResourceZipFile::ResourceZipFile(const string fileName):ResourceZipFile(fileName,"zipFile"){

ResourceZipFile::ResourceZipFile(const string folderName, const string fileName) :
		IResourceFile(folderName) {

	logger::info("Create ResourceZipFile(folderName, fileName)");
	m_resFileName = folderName + fileName;
	m_pZipFile = nullptr;

	//	m_readMode = "zipFile";
	//	m_pZipFile = nullptr;
	//	m_resFileName = fileName;
}

ResourceZipFile::~ResourceZipFile() {
	logger::info("Destroy ResourceZipFile");
	templates::safe_delete<ZipFile>(m_pZipFile);

}

bool ResourceZipFile::vOpen() {
	m_pZipFile = new ZipFile();
	bool result = m_pZipFile->init(m_resFileName, ZipFile::COMPRESSED);

	m_pZipFile->describeYourself();
	return result;
}

/*
void ResourceZipFile::vTempReadResource(const Resource& resource) {
	stringstream ss;
	ss << "ResourceZipFile::vTempReadResource: ";
	//		<< resource.getName();

	logger::info(ss);
}
 */

uintmax_t ResourceZipFile::vGetRawResource(const Resource& resource,
		char *buffer) {
	ZipFileAsset* pZipFileAsset = m_pZipFile->find(resource.getName());

	uintmax_t size = 0;
	if (pZipFileAsset) {
//		size = pZipFileAsset->getFileDataSize();
		size = pZipFileAsset->getUnzipFileDataSize();

		// Unzip !!!
		// pZipFileAsset->readFile(buffer);

		//pZipFileAsset->readAndUnzipFile(buffer);
		pZipFileAsset->readAndUnzipFile(buffer);
	}

	return size;
}

uintmax_t ResourceZipFile::vGetRawResourceSize(const Resource &resource) {
	ZipFileAsset* pZipFileAsset = m_pZipFile->find(resource.getName());

	uintmax_t size = 0;
	if (pZipFileAsset) {
		// size = pZipFileAsset->getFileDataSize();
		size = pZipFileAsset->getUnzipFileDataSize();
	}

	/*
	 * 	int resourceNum = m_pZipFile->Find(r.m_name.c_str());
	 if (resourceNum == -1)
	 return -1;

	 return m_pZipFile->GetFileLen(resourceNum);
	 */

	return size;
}

bool ResourceZipFile::vSaveFolderMode(const string outputFolderName) {
	stringstream ss;
	ss << "VSAVE: " << m_rootFolder;
	logger::info(ss);

	string folderFullName = m_rootFolder + "/" + outputFolderName;
	//		+ IResourceFile::ASSETS_ZIP_TO_FOLDER;

	m_pZipFile->saveAsFolder(folderFullName);
	return true;
}

bool ResourceZipFile::vSaveUnzipMode(const string outputUnzipFileName) {
	string fileName = m_rootFolder + "/" + outputUnzipFileName;
	// IResourceFile::ASSETS_ZIP_TO_UNZIP;
	m_pZipFile->save(fileName, ZipFile::NOT_COMPRESSED);

	return true;
}

bool ResourceZipFile::vSaveZipMode(const string outputZipFileName) {
	string fileName = m_rootFolder + "/" + outputZipFileName;
	//IResourceFile::ASSETS_ZIP_TO_ZIP;
	m_pZipFile->save(fileName, ZipFile::COMPRESSED);

	return true;
}
}

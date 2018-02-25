#include "ResourceZipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"

#include <string>
#include <sstream>      // std::stringstream

using std::string;
using std::stringstream;

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

bool ResourceZipFile::vSaveFolderMode() {
	stringstream ss;
	ss << "VSAVE: " << m_rootFolder;
	logger::info(ss);

	string folderFullName = m_rootFolder + "/"
			+ IResourceFile::ASSETS_ZIP_TO_FOLDER;

	m_pZipFile->saveAsFolder(folderFullName);
	return true;
}

bool ResourceZipFile::vSaveUnzipMode() {
	string fileName = m_rootFolder + "/" + IResourceFile::ASSETS_ZIP_TO_UNZIP;
	m_pZipFile->save(fileName, ZipFile::NOT_COMPRESSED);

	return true;
}

bool ResourceZipFile::vSaveZipMode() {
	string fileName = m_rootFolder + "/" + IResourceFile::ASSETS_ZIP_TO_ZIP;
	m_pZipFile->save(fileName, ZipFile::COMPRESSED);

	return true;
}
}

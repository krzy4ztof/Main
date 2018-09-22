/*
 * DevelopmentResourceZipFile.cpp
 *
 *  Created on: 25.06.2017
 *      Author: Krzysztof
 */

#include "../debugging/Logger.h"
#include "DevelopmentResourceFolder.h"
#include "TZipDirFileHeader.h"
#include "TZipDirHeader.h"
#include "TZipLocalHeader.h"


#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;
#include <boost/filesystem/operations.hpp> // boost::filesystem::file_size

#include <boost/iostreams/device/file.hpp> //  boost::iostreams::file_source; boost::iostreams::file_sink
#include <boost/iostreams/stream.hpp> // boost::iostreams::stream; boost::iostreams::stream_buffer

#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/filter/zlib.hpp> //zlib_compressor
#include <boost/iostreams/device/array.hpp> // boost::iostreams::array_source;
#include <boost/optional.hpp> // boost::optional
#include <boost/cstdint.hpp> // boost::uintmax_t

#include <string>
#include <sstream>      // std::stringstream
#include <regex> // std::regex, std::regex_replace
#include <vector> //std::vector
#include <list> // std::list

//using std::ios::binary;

using std::ios;
using std::string;
using std::stringstream;
using std::vector;
using std::list;

using std::regex;
using std::regex_replace;

using boost::filesystem::path;
using boost::filesystem::recursive_directory_iterator;
using boost::filesystem::filesystem_error;
using boost::filesystem::directory_entry;
using boost::filesystem::exists;
using boost::filesystem::is_directory;
using boost::filesystem::is_regular_file;
using boost::filesystem::create_directory;
using boost::filesystem::remove_all;
using boost::filesystem::copy_file;
using boost::filesystem::file_size;

using boost::filesystem::ofstream;
using boost::filesystem::ifstream;

using boost::iostreams::zlib_compressor;
using boost::iostreams::file_source;
using boost::iostreams::file_sink;
using boost::iostreams::stream;
using boost::iostreams::stream_buffer;
using boost::iostreams::filtering_istreambuf;
using boost::iostreams::array_source;

using boost::optional;

using boost::uintmax_t;

namespace base_game {

DevelopmentResourceFolder::DevelopmentResourceFolder(const string rootFolder,
		const string assetsFolder) :
		IResourceFile(rootFolder), m_assetsFolder(assetsFolder) {
	logger::info("Create DevelopmentResourceFolder(rootFolder, assetsFolder)");

}

DevelopmentResourceFolder::~DevelopmentResourceFolder() {
	logger::info("Destroy DevelopmentResourceZipFile");

	m_paths.clear();
	m_assetsFolder.clear();
}

bool DevelopmentResourceFolder::vOpen() {

	return readAssetsDirectory();
}

optional<path> DevelopmentResourceFolder::getPath(const Resource &resource) {
	stringstream ss;

	path thisResPath { this->m_assetsFolder };
	thisResPath /= resource.getName();
	thisResPath = thisResPath.make_preferred();
	string thisResourceName = thisResPath.string();

	ss << "thisResPath: " << thisResourceName;
	logger::info(ss);

	for (path resourcePath : m_paths) {

		resourcePath = resourcePath.make_preferred();
		string resourceName = resourcePath.string();




		ss << "makePreferred: " << resourcePath.make_preferred()
				<< " filename: " << resourcePath.filename();

		logger::info(ss);
// makePreferred: "..\..\..\assets\actors\player_character.xml" filename: "player_character.xml"
// makePreferred: "..\..\..\assets\graphics\polskieĄęĆznaki.txt" filename: "polskieĄęĆznaki.txt"

		int compRes = thisResourceName.compare(resourceName);
		if (compRes == 0) {
			ss << "THIS IS THIS: " << resourceName;
			logger::info(ss);
			int i;
			i++;

			return resourcePath;

		}
	}

	return optional<path> { };

}

/*
void DevelopmentResourceFolder::vTempReadResource(const Resource& resource) {
	stringstream ss;
	ss << "DevelopmentResourceUnzipFile::vTempReadResource: ";
	//		<< resource.getName();

	logger::info(ss);

}
 */

uintmax_t DevelopmentResourceFolder::vGetRawResource(const Resource& resource,
		char *buffer) {

	stringstream ss;

	optional<path> optPath = this->getPath(resource);
	if (!optPath.is_initialized()) {
		ss << "RESOURCE NOT  FOUND " << resource.getName();
		logger::info (ss);
		return -1;
	}

	//} else {

		// __MINGW_EXTENSION typedef unsigned long long   uintmax_t;
	filtering_istreambuf inBuf;
	ifstream ifs { optPath.get(), ios::binary };
	inBuf.push(ifs);


	vector<char> vecChar;
	boost::iostreams::copy(inBuf, boost::iostreams::back_inserter(vecChar));

	ss << "CONTENTS OF: " << resource.getName();
	logger::info(ss);

	vector<char>::iterator it;
	for (it = vecChar.begin(); it != vecChar.end(); ++it) {
		ss << *it;
	}

	logger::info(ss);

	ss << "vecChar size: " << vecChar.size();
	logger::info(ss);


	std::copy(vecChar.begin(), vecChar.end(), buffer);

	//boost::iostreams::copy(inBuf, buffer);

	// TODO: upewnic sie ze vecCharDec ma taki sam rozmiar co *buffer i skopiowac vecCharDec do *buffer



		uintmax_t fileSize = file_size(optPath.get());

		return fileSize;


	//}

//	return -1;
}

/*
 * int DevelopmentResourceZipFile::VGetRawResource(const Resource &r, char *buffer)
 {
 if (m_mode == Editor)
 {
 int num = Find(r.m_name.c_str());
 if (num == -1)
 return -1;

 std::string fullFileSpec = ws2s(m_AssetsDir) + r.m_name.c_str();
 FILE *f = fopen(fullFileSpec.c_str(), "rb");
 size_t bytes = fread(buffer, 1, m_AssetFileInfo[num].nFileSizeLow, f);
 fclose(f);
 return bytes;
 }

 return ResourceZipFile::VGetRawResource(r, buffer);
 */


uintmax_t DevelopmentResourceFolder::vGetRawResourceSize(
		const Resource &resource) {
	stringstream ss;
	ss << "DevelopmentResourceFolder::vGetRawResourceSize: "
	<< resource.getName();
// DevelopmentResourceFolder::vTempReadResource: actors/player_character.xml

	logger::info(ss);

	ss << "Root Folder: " << this->m_rootFolder;
	logger::info(ss);

	ss << "Asset Folder: " << this->m_assetsFolder;
	logger::info(ss);

	optional<path> optPath = this->getPath(resource);

	if (!optPath.is_initialized()) {
		ss << "RESOURCE NOT  FOUND " << resource.getName();
		logger::info(ss);
		return 0;

		// return static_cast<uintmax_t>(-1);
	} else {

		// __MINGW_EXTENSION typedef unsigned long long   uintmax_t;
		uintmax_t fileSize = file_size(optPath.get());

		ss << "PATH FOUND " << optPath->string() << " File Size " << fileSize;
		logger::info(ss);

		return fileSize;

	}


	
	return 0;
}

bool DevelopmentResourceFolder::readAssetsDirectory() {

	stringstream ss;
	path assetsPath { m_assetsFolder };

	try {
		if (exists(assetsPath) && is_directory(assetsPath)) {

			ss << "assetsPath: " << assetsPath.string();
			logger::info(ss);

			recursive_directory_iterator dirIterator { assetsPath };
			while (dirIterator != recursive_directory_iterator { }) {
				directory_entry& dirEntry = *dirIterator;

				path dirPath = dirEntry.path();

				if (is_regular_file(dirPath)) {

					if (!fileToIgnore(dirPath)) {
						m_paths.push_back(dirPath);
					}
				}

				*dirIterator++;
			}
		}
		return true;
	} catch (const filesystem_error& ex) {
		logger::error(ex.what());
		return false;

	}

}

bool DevelopmentResourceFolder::fileToIgnore(path filePath) {
	if (filePath.filename().string().compare(".gitignore") == 0) {
		return true;
	}
	return false;

}

string DevelopmentResourceFolder::getOutputFolderName(const string folderName) {
	regex expr(IResourceFile::ASSETS_FOLDER);
	string assetsOutFolder = regex_replace(m_assetsFolder, expr, folderName);

	return assetsOutFolder;

}

bool DevelopmentResourceFolder::prepareOutputDir(const string assetsOutFolder) {

	stringstream ss;

	//string assetsOutFolder = getOutputFolderName(folderName);

	ss << "VSAVE DEV: " << assetsOutFolder;
	logger::info(ss);

	path pathAssetsDev { assetsOutFolder };

	try {
		remove_all(pathAssetsDev);
	} catch (filesystem_error &ex) {
		logger::error(ex.what());
	}

	try {

		create_directory(pathAssetsDev);
	} catch (filesystem_error &ex) {
		logger::error(ex.what());
	}

	return true;
}

bool DevelopmentResourceFolder::createFolder(path newFolder) {
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

bool DevelopmentResourceFolder::copyFile(path inPath, path outFolder) {

	stringstream ss;

	ifstream ifs(inPath, std::ios::binary);

	path newFilePath { };
	newFilePath /= outFolder;
	newFilePath /= inPath.filename();

	if (ifs.is_open()) {

		filtering_istreambuf inDec;
		inDec.push(ifs);

		vector<char> vecCharDec;
		boost::iostreams::copy(inDec,
				boost::iostreams::back_inserter(vecCharDec));

		ofstream ofs(newFilePath, std::ios::binary);
		ofs.write(reinterpret_cast<char *>(vecCharDec.data()),
				vecCharDec.size());
		ofs.close();
		ifs.close();
	}

	return true;
}

bool DevelopmentResourceFolder::createFilesAndFolders(const string folderName) {
	stringstream ss;

	//TODO: zmienic sciezke na zapis w watermill.ini

	string assetsRegex = this->m_rootFolder + "assets[/\\\\]";

	regex exprAssetsFolder(assetsRegex);

	for (path resourcePath : m_paths) {

		path parentPath = resourcePath.parent_path();

		path newFolder { folderName };
		newFolder /= regex_replace(parentPath.string(), exprAssetsFolder, "");

		createFolder(newFolder);

		copyFile(resourcePath, newFolder);
	}

	return true;
}

bool DevelopmentResourceFolder::vSaveFolderMode(const string outputFolderName) {
	stringstream ss;
	ss << "VSAVE: " << m_assetsFolder;
	logger::info(ss);

	//string assetsDevFolder = IResourceFile::ASSETS_FOLDER_TO_FOLDER;
	//string folderFullName = getOutputFolderName(assetsDevFolder);
	string folderFullName = getOutputFolderName(outputFolderName);

	prepareOutputDir(folderFullName);
	createFilesAndFolders(folderFullName);

	return true;
}

bool DevelopmentResourceFolder::vSaveUnzipMode(
		const string outputUnzipFileName) {
	stringstream ss;
	ss << "VSAVE: " << m_assetsFolder;
	logger::info(ss);

	//string assetsUnzipFile = IResourceFile::ASSETS_UNZIP_FILE;

	//createAssetFile(this->m_rootFolder, assetsUnzipFile,
	//		IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE);
	createAssetFile(this->m_rootFolder, outputUnzipFileName,
			IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE);

	return true;
}

bool DevelopmentResourceFolder::saveAssetFileName(TZipLocalHeader& lh,
		ofstream& ofs, const string shortFileName, const string saveMode) {
	if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
		lh.fnameLen = shortFileName.length();
		lh.isCompression = TZipLocalHeader::Z_NO_COMPRESSION;

		//local header
		ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

		//file name
		ofs.write(shortFileName.c_str(), shortFileName.length());
	} else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
		filtering_istreambuf filterFileName;
		filterFileName.push(zlib_compressor());

		stringstream fileNameStream;
		fileNameStream << shortFileName;
		filterFileName.push(fileNameStream);

		vector<char> vecFileName;
		boost::iostreams::copy(filterFileName,
				boost::iostreams::back_inserter(vecFileName));

		lh.fnameLen = vecFileName.size();
		lh.isCompression = TZipLocalHeader::Z_DEFLATED;

		// Local Header
		ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

		//file name
		ofs.write(reinterpret_cast<char *>(vecFileName.data()),
				vecFileName.size());

	}

}

bool DevelopmentResourceFolder::saveAssetFileContents(ofstream& ofs,
		const path resourceFilePath, const string saveMode,
		vector<char>& vecFileContents) {
	stringstream ss;

	filtering_istreambuf filterAssetFile;

	if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
		// Do not push zlib_compressor()
	} else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
		filterAssetFile.push(zlib_compressor());
	}

	ifstream assetFile(resourceFilePath, std::ios::binary);
	int fileSize = file_size(resourceFilePath);

	filterAssetFile.push(assetFile);

	//vector<char> vecFileContents;
	boost::iostreams::copy(filterAssetFile,
			boost::iostreams::back_inserter(vecFileContents));
	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());

	ss << "fileSize: " << fileSize << " compressedSize: "
			<< vecFileContents.size();
	logger::info(ss);

}

bool DevelopmentResourceFolder::saveAsset(ofstream& ofs,
		const path resourceFilePath, const string shortFileName,
		list<TZipDirFileHeader*>& dirFileHeadersList, const TZipDirHeader& dh,
		const string saveMode) {

	stringstream ss;

	ss << "PATH sAF -> " << resourceFilePath.string();
	logger::info(ss);

	ss << "REPLACED PATH sAF -> " << shortFileName << " size: "
			<< sizeof(shortFileName) << " length: " << shortFileName.length();
	logger::info(ss);

	TZipLocalHeader lh;

	this->saveAssetFileName(lh, ofs, shortFileName, saveMode);

	vector<char> vecFileContents;
	this->saveAssetFileContents(ofs, resourceFilePath, saveMode,
			vecFileContents);

	ss << "Outside fileSize: compressedSize: " << vecFileContents.size();
	logger::info(ss);

	TZipDirFileHeader* dfh = new TZipDirFileHeader();

	if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
		dfh->isCompression = TZipDirFileHeader::Z_NO_COMPRESSION;
	} else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
		dfh->isCompression = TZipDirFileHeader::Z_DEFLATED;
	}

	int fileSizeNotCompressed = file_size(resourceFilePath);

	dfh->ucSize = fileSizeNotCompressed;
	dfh->cSize = vecFileContents.size();
	dfh->fnameLen = lh.fnameLen;
	dirFileHeadersList.push_back(dfh);

	return true;

}

bool DevelopmentResourceFolder::createAssetFile(const string folderName,
		const string assetsUnzipFile, const string saveMode) {
	//string assetsOutFolder = getOutputFolderName(folderName);

	stringstream ss;
	ss << "VSAVE DEV: " << folderName;
	logger::info(ss);

	path filePath { folderName + "/" + assetsUnzipFile };

	ofstream ofs(filePath, std::ios::binary);

	if (ofs.is_open()) {
		ss << "OPEN OPEN OPEN " << filePath.string();
		logger::info(ss);

		TZipDirHeader dh;
		list<TZipDirFileHeader*> dirFileHeadersList;

		string assetsRegex = this->m_rootFolder + "assets[/\\\\]";
		regex exprAssetsFolder(assetsRegex);

		for (path resourcePath : m_paths) {

			string replacedPath = regex_replace(resourcePath.string(),
					exprAssetsFolder, "");

			this->saveAsset(ofs, resourcePath, replacedPath, dirFileHeadersList,
					dh, saveMode);

			// TODO: zapisywanie plikow do unzip file
			// File 0 = TZipLocalHeader, File Data
			// File 1 = TZipLocalHeader, File Data
			// File 2 = TZipLocalHeader, File Data
			// File 3 = TZipLocalHeader, File Data
			// TZipDirFileHeader[0]
			// TZipDirFileHeader[1]
			// TZipDirFileHeader[2]
			// TZipDirFileHeader[3]
			// TZipDirHeader
		}

		// Save TZipDirFileHeader-s
		for (list<TZipDirFileHeader*>::iterator it = dirFileHeadersList.begin();
				it != dirFileHeadersList.end(); ++it) {

			ofs.write(reinterpret_cast<char *>(*it), sizeof(TZipDirFileHeader)); // OK wynik plik: ABCD; dla kompresji: x.strv...
		};

		// Save TZipDirHeader
		dh.nDirEntries = dirFileHeadersList.size();

		if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
			dh.isCompression = TZipDirHeader::Z_NO_COMPRESSION;
		} else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode)
				== 0) {
			dh.isCompression = TZipDirHeader::Z_DEFLATED;
		}

		ofs.write(reinterpret_cast<char *>(&dh), sizeof(dh));

		ofs.close();
		return true;

	} else {
		ss << "CLOSED " << filePath.string();
		logger::warning(ss);
		return false;
	}

	//return true;
}

bool DevelopmentResourceFolder::vSaveZipMode(const string outputZipFileName) {
	stringstream ss;
	ss << "VSAVE: " << m_assetsFolder;
	logger::info(ss);

	//string assetsZipFile = IResourceFile::ASSETS_ZIP_FILE;

	//createAssetFile(this->m_rootFolder, assetsZipFile,
	//		IResourceFile::ASSETS_SAVE_MODE_ZIPFILE);
	createAssetFile(this->m_rootFolder, outputZipFileName,
			IResourceFile::ASSETS_SAVE_MODE_ZIPFILE);

	return true;
}

} /* namespace base_game */

/*
 * DevelopmentResourceZipFile.cpp
 *
 *  Created on: 25.06.2017
 *      Author: Krzysztof
 */

#include "../debugging/Logger.h"

#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;

#include <boost/iostreams/device/file.hpp> //  boost::iostreams::file_source; boost::iostreams::file_sink
#include <boost/iostreams/stream.hpp> // boost::iostreams::stream; boost::iostreams::stream_buffer

#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/filter/zlib.hpp> //zlib_compressor
#include <boost/iostreams/device/array.hpp> // boost::iostreams::array_source;

#include <string>
#include <sstream>      // std::stringstream
#include <regex> // std::regex, std::regex_replace
#include <vector> //std::vector
#include "DevelopmentResourceFolder.h"
#include "TZipDirFileHeader.h"
#include "TZipDirHeader.h"
#include "TZipLocalHeader.h"

#include <list> // std::list

//using std::ios::binary;

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
using boost::filesystem::ofstream;
using boost::filesystem::ifstream;

using boost::iostreams::zlib_compressor;
using boost::iostreams::file_source;
using boost::iostreams::file_sink;

using boost::iostreams::stream;
using boost::iostreams::stream_buffer;

using boost::iostreams::filtering_istreambuf;

using boost::iostreams::array_source;

namespace base_game {

DevelopmentResourceFolder::DevelopmentResourceFolder(const string rootFolder,
		const string assetsFolder) :
		IResourceFile(rootFolder), m_assetsFolder(assetsFolder) {
	logger::info("Create DevelopmentResourceFolder(rootFolder, assetsFolder)");
//	m_assetsFolder = assetsFolder;

}

/*
 DevelopmentResourceZipFile::DevelopmentResourceZipFile(const string fileName, const string readMode, const string assetsFolder):ResourceZipFile(fileName, readMode ){
 logger::info("Create DevelopmentResourceZipFile(fileName, readMode, assetsFolder)");
 m_assetsFolder = assetsFolder;

 }
 */

/*
 DevelopmentResourceFolder::DevelopmentResourceFolder() {
 logger::info("Create DevelopmentResourceFolder");
 }*/

DevelopmentResourceFolder::~DevelopmentResourceFolder() {
	logger::info("Destroy DevelopmentResourceZipFile");

	m_paths.clear();
	m_assetsFolder.clear();
}

bool DevelopmentResourceFolder::vOpen() {

	return readAssetsDirectory(); //(assetsFolder);
	/*
	 m_pZipFile = new ZipFile();
	 if (m_pZipFile) {
	 return m_pZipFile->init(m_resFileName);
	 }
	 */

	//return true;
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
					//	ss << "FILE: ";

					if (!fileToIgnore(dirPath)) {
						m_paths.push_back(dirPath);
					}
				}

				//ss << dirPath;
				//logger::info(ss);

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

//bool DevelopmentResourceFolder::prepareOutputDir(const string folderName) {
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

	/*
	 vector<string> subFolders;
	 subFolders.push_back("sub1");
	 subFolders.push_back("sub2");
	 subFolders.push_back("sub3");

	 path subPath = pathAssetsDev;

	 for (string element : subFolders) {
	 subPath /= element;
	 try {
	 create_directory(subPath);
	 } catch (filesystem_error &ex) {
	 logger::error(ex.what());
	 }

	 }
	 */

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
		//	ss << "OTWARTY " << inPath.filename();
		//	logger::info(ss);

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

	//regex exprAssetsFolder(m_assetsFolder);
	// [/\\\\] - backslash or slash, slash

	//TODO: zmienic sciezke na zapis w watermill.ini

	string assetsRegex = this->m_rootFolder + "assets[/\\\\]";

	regex exprAssetsFolder(assetsRegex);

	//regex exprAssetsFolder("../../../assets[/\\\\]");

	for (path resourcePath : m_paths) {

		path parentPath = resourcePath.parent_path();

		// path newFolder { getOutputFolderName(folderName) };
		path newFolder { folderName };
		newFolder /= regex_replace(parentPath.string(), exprAssetsFolder, "");

//		ss << "New PATH: " << newFolder.string();
//		logger::info(ss);

		createFolder(newFolder);

		copyFile(resourcePath, newFolder);
	}

	return true;
}

/*
 bool DevelopmentResourceFolder::vSave(const string saveMode) {

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
 */

bool DevelopmentResourceFolder::vSaveFolderMode() {
	stringstream ss;
	ss << "VSAVE: " << m_assetsFolder;
	logger::info(ss);

	// assetsOutFolder = m_assetsFolder;
	string assetsDevFolder = IResourceFile::ASSETS_FOLDER_TO_FOLDER;
	string folderFullName = getOutputFolderName(assetsDevFolder);

	prepareOutputDir(folderFullName);
	createFilesAndFolders(folderFullName);

	return true;
}

bool DevelopmentResourceFolder::saveUnzipAsset_222(ofstream& ofs,
		const path resourceFilePath, const string shortFileName,
		list<TZipDirFileHeader*>& dirFileHeadersList, const TZipDirHeader& dh) {

	//TODO:
	// dopisac zapis dirFileHeadersList, dh

	stringstream ss;

	ss << "PATH sAF -> " << resourceFilePath.string();
	logger::info(ss);

	ss << "REPLACED PATH sAF -> " << shortFileName << " size: "
			<< sizeof(shortFileName) << " length: " << shortFileName.length();
	logger::info(ss);

	TZipLocalHeader lh;
	lh.fnameLen = shortFileName.length();

	//local header
	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	//file name
	//ofs.write(reinterpret_cast<char *>(&shortFileName), shortFileName.length());
//	ofs.write(shortFileName.c_str(), sizeof(shortFileName));
	ofs.write(shortFileName.c_str(), shortFileName.length());

//	string filename = assetsFolder + "graphics/tempTestZipFile.txt";
//	test_saveSingleNotCompressedTxtFile(filename, ofs);

	filtering_istreambuf inDec;
	ifstream myfile(resourceFilePath, std::ios::binary);

	inDec.push(myfile);

	string line;
	char c;

	//int fileSize = 0;
	int fileSize = file_size(resourceFilePath);

	vector<char> vecCharDec;
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size());

	//if (myfile.is_open()) {
	/*
	 while (getline(myfile, line)) {
	 //ofs.write(reinterpret_cast<char *>(&line), sizeof(line));
	 //			ofs.write(line.c_str(), sizeof(line));
	 ofs.write(line.c_str(), line.length());
	 logger::info(line);
	 }
	 */

	/*
	 while (myfile.get(c)) {
	 ofs.put(c);
	 fileSize++;
	 };
	 */

	//	ofs << myfile;
	/*
	 myfile.close();

	 } else {
	 ss << "File '" << resourceFilePath.string() << "' not found";
	 logger::warning(ss);
	 return false;
	 }
	 */

	TZipDirFileHeader* dfh = new TZipDirFileHeader();
	//dfh->testInitiation();
	dfh->cSize = fileSize;
	dfh->fnameLen = lh.fnameLen;

	//TZipDirFileHeader dfh2;
	dirFileHeadersList.push_back(dfh);

	return true;

}

bool DevelopmentResourceFolder::createUnzipFile_222(const string folderName,
		const string assetsUnzipFile) {
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

//	regex exprAssetsFolder("../../../assets[/\\\\]");

		for (path resourcePath : m_paths) {

			//path parentPath = resourcePath.parent_path();
			//ss << "PARENT PATH -> " << parentPath;

			string replacedPath = regex_replace(resourcePath.string(),
					exprAssetsFolder, "");

			this->saveUnzipAsset_222(ofs, resourcePath, replacedPath,
					dirFileHeadersList, dh);

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

			/*
			 ss << "it1 -> " << (*it); // 0x99b94b0
			 ss << "it2 -> " << (&(*it)); // 0x99b94b0

			 logger::info(ss);
			 */

			//(*it)->describeYourself();
			/*
			 filtering_istreambuf inDec;
			 std::stringstream original;
			 //std::string fhstr = "ABCD";

			 //
			 // http://www.cplusplus.com/reference/ostream/ostream/write/
			 //
			 //original << it; //(*it); // Dla plików ABCD
			 original << (*it); //(*it); // Dla plików ABCD

			 inDec.push(original);

			 vector<char> vecCharDec;
			 // copy inDec to vecCharDec
			 boost::iostreams::copy(inDec,
			 boost::iostreams::back_inserter(vecCharDec));

			 ofs.write(reinterpret_cast<char *>(vecCharDec.data()),
			 vecCharDec.size()); // OK wynik plik: ABCD; dla kompresji: x.strv...
			 */

			//ofs.write(reinterpret_cast<char *>(*it), sizeof(*it)); // OK wynik plik: ABCD; dla kompresji: x.strv...
			//	ofs.write(reinterpret_cast<char *>(&(*it)), sizeof(*it)); // OK wynik plik: ABCD; dla kompresji: x.strv...
//		ofs.write(reinterpret_cast<char *>(&(*it)), sizeof(TZipDirFileHeader)); // OK wynik plik: ABCD; dla kompresji: x.strv...
			ofs.write(reinterpret_cast<char *>(*it), sizeof(TZipDirFileHeader)); // OK wynik plik: ABCD; dla kompresji: x.strv...

			//TZipDirFileHeader zdfh;
			//ofs.write(reinterpret_cast<char *>(&zdfh), sizeof(zdfh)); // OK wynik plik: ABCD; dla kompresji: x.strv...
			//ofs.write(reinterpret_cast<char *>(&zdfh), sizeof(TZipDirFileHeader)); // OK wynik plik: ABCD; dla kompresji: x.strv...

			/*
			 ss << "size of it " << sizeof(*it) << "; size TZipLocalHeader "
			 << sizeof(TZipLocalHeader) << "; size TZipDirFileHeader "
			 << sizeof(TZipDirFileHeader) << "; size TZipDirHeader "
			 << sizeof(TZipDirHeader);

			 logger::info(ss);
			 */

			//ofs.write(reinterpret_cast<char *>(*it), sizeof(TZipDirFileHeader));
			//ofs.write(*it, sizeof(TZipDirFileHeader));
			// TODO zapis iteratora TZipDirFileHeader
			// ofs.write(reinterpret_cast<char *>(&(*it)), sizeof(TZipDirFileHeader));
			//ofs.write(static_cast<char *>(static_cast<void*>(it)),
			//		sizeof(TZipDirFileHeader));
		};

		// Save TZipDirHeader
		ofs.write(reinterpret_cast<char *>(&dh), sizeof(dh));

		ofs.close();
		return true;

	} else {
		ss << "CLOSED " << filePath.string();
		logger::warning(ss);
		return false;
	}
}

bool DevelopmentResourceFolder::vSaveUnzipMode() {
	stringstream ss;
	ss << "VSAVE: " << m_assetsFolder;
	logger::info(ss);

	//string assetsDevUnzip = IResourceFile::ASSETS_DEV_UNZIP_FOLDER;
	string assetsUnzipFile = IResourceFile::ASSETS_UNZIP_FILE;
	//string folderFullName = getOutputFolderName(assetsDevUnzip);

	//prepareOutputDir(this->m_rootFolder);
//	createUnzipFile_222(this->m_rootFolder, assetsUnzipFile);

	createAssetFile(this->m_rootFolder, assetsUnzipFile,
			IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE);

	return true;
}

bool DevelopmentResourceFolder::saveAssetFileName(TZipLocalHeader& lh,
		ofstream& ofs, const string shortFileName, const string saveMode) {
	if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
		lh.fnameLen = shortFileName.length();

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

	/*
	 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
	 lh.fnameLen = shortFileName.length();

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

	 // Local Header
	 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	 //file name
	 ofs.write(reinterpret_cast<char *>(vecFileName.data()),
	 vecFileName.size());

	 }
	 */

	vector<char> vecFileContents;
	this->saveAssetFileContents(ofs, resourceFilePath, saveMode,
			vecFileContents);

	/*
	 filtering_istreambuf filterAssetFile;

	 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
	 // Do not push zlib_compressor()
	 } else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
	 filterAssetFile.push(zlib_compressor());
	 }

	 ifstream assetFile(resourceFilePath, std::ios::binary);
	 int fileSize = file_size(resourceFilePath);

	 filterAssetFile.push(assetFile);

	 vector<char> vecFileContents;
	 boost::iostreams::copy(filterAssetFile,
	 boost::iostreams::back_inserter(vecFileContents));
	 ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
	 vecFileContents.size());

	 ss << "fileSize: " << fileSize << " compressedSize: "
	 << vecFileContents.size();
	 logger::info(ss);

	 */
	ss << "Outside fileSize: compressedSize: " << vecFileContents.size();
	logger::info(ss);

	TZipDirFileHeader* dfh = new TZipDirFileHeader();
	dfh->cSize = vecFileContents.size();
	dfh->fnameLen = lh.fnameLen;
	dirFileHeadersList.push_back(dfh);

	return true;

}

bool DevelopmentResourceFolder::saveZipAsset_222(ofstream& ofs,
		const path resourceFilePath, const string shortFileName,
		list<TZipDirFileHeader*>& dirFileHeadersList, const TZipDirHeader& dh) {

	//TODO:
	// dopisac zapis dirFileHeadersList, dh

	stringstream ss;

	ss << "PATH sAF -> " << resourceFilePath.string();
	logger::info(ss);

	ss << "REPLACED PATH sAF -> " << shortFileName << " size: "
			<< sizeof(shortFileName) << " length: " << shortFileName.length();
	logger::info(ss);

	//filtering_istreambuf inDec;
	//inDec.push(zlib_compressor());

	/*
	 char data[sizeof(lh)];
	 memcpy(data, &lh, sizeof(lh));

	 array_source source(data, sizeof(lh));
	 inDec.push(source);

	 vector<char> vecCharDec;
	 // copy inDec to vecCharDec
	 boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));
	 */
	//local header
	//ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size()); // OK wynik plik: ABCD; dla kompresji: x.strv...
	filtering_istreambuf filterFileName;
	filterFileName.push(zlib_compressor());

	stringstream fileNameStream;
	//std::string fhstr = "ABCD";

	/*
	 * http://www.cplusplus.com/reference/ostream/ostream/write/
	 */
	fileNameStream << shortFileName; // Dla plików ABCD
	filterFileName.push(fileNameStream);

	//filterFileName.push(shortFileName);
	vector<char> vecFileName;
	boost::iostreams::copy(filterFileName,
			boost::iostreams::back_inserter(vecFileName));

	TZipLocalHeader lh;
	lh.fnameLen = vecFileName.size();
	// Local Header
	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	//file name
//	ofs.write(shortFileName.c_str(), shortFileName.length());
	ofs.write(reinterpret_cast<char *>(vecFileName.data()), vecFileName.size());

	filtering_istreambuf filterAssetFile;
	filterAssetFile.push(zlib_compressor());

	ifstream assetFile(resourceFilePath, std::ios::binary);
	//string line;
	//char c;
	int fileSize = file_size(resourceFilePath);

	filterAssetFile.push(assetFile);

	vector<char> vecFileContents;
	boost::iostreams::copy(filterAssetFile,
			boost::iostreams::back_inserter(vecFileContents));
	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());

	ss << "fileSize: " << fileSize << " compressedSize: "
			<< vecFileContents.size();
	logger::info(ss);

	/*
	 if (myfile.is_open()) {
	 while (myfile.get(c)) {
	 ofs.put(c);
	 fileSize++;
	 };

	 int fileSize2 = file_size(resourceFilePath);

	 ss << "fileSize: " << fileSize << " fileSizeBoost: " << fileSize2;
	 logger::info(ss);

	 myfile.close();

	 } else {
	 ss << "File '" << resourceFilePath.string() << "' not found";
	 logger::warning(ss);
	 return false;
	 }
	 */

	TZipDirFileHeader* dfh = new TZipDirFileHeader();
	//dfh->testInitiation();
	//dfh->cSize = fileSize;
	dfh->cSize = vecFileContents.size();
	dfh->fnameLen = lh.fnameLen;

	// vecFileName.size();

	//TZipDirFileHeader dfh2;
	dirFileHeadersList.push_back(dfh);

	return true;

}

bool DevelopmentResourceFolder::createZipFile_222(const string folderName,
		const string assetsUnzipFile) {
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

			this->saveZipAsset_222(ofs, resourcePath, replacedPath,
					dirFileHeadersList, dh);

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

			/*
			 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode)
			 == 0) {
			 this->saveUnzipAsset_222(ofs, resourcePath, replacedPath,
			 dirFileHeadersList, dh);
			 } else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode)
			 == 0) {
			 this->saveZipAsset_222(ofs, resourcePath, replacedPath,
			 dirFileHeadersList, dh);

			 }
			 
			 */

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

bool DevelopmentResourceFolder::vSaveZipMode() {
	stringstream ss;
	ss << "VSAVE: " << m_assetsFolder;
	logger::info(ss);

	//string assetsZipFile = GameCodeApp::ASSETS_ZIP;
	string assetsZipFile = IResourceFile::ASSETS_ZIP_FILE;

//	createZipFile_222(this->m_rootFolder, assetsZipFile);
	createAssetFile(this->m_rootFolder, assetsZipFile,
			IResourceFile::ASSETS_SAVE_MODE_ZIPFILE);

//	string assetsDevFolder = IResourceFile::ASSETS_DEV_ZIP_FOLDER;
//	prepareOutputDir(assetsDevFolder);

	return true;
}

} /* namespace base_game */

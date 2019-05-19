#include "ZipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"
#include "TZipDirFileHeader.h"
#include "TZipDirHeader.h"
#include "TZipLocalHeader.h"
#include "ZipFileAsset.h"
#include "../utilities/StringUtils.h"

#include <boost/iostreams/filter/zlib.hpp> // zlib_decompressor
//#include <boost/iostreams/filter/gzip.hpp> // gzip_decompressor
#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/device/file.hpp> // boost::iostreams::file_source
#include <boost/iostreams/stream.hpp> // boost::iostreams::stream
#include <boost/iostreams/filtering_stream.hpp> // boost::iostreams::filtering_istream;
#include <boost/iostreams/device/array.hpp> // boost::iostreams::array_source, boost::iostreams::array_sink
#include <boost/filesystem/fstream.hpp>
#include <boost/cstdint.hpp> // boost::uintmax_t

#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;  boost::filesystem::ifstream;

#include <sstream>      // std::stringstream
#include <string>
#include <fstream> // ifstream
#include <vector> // vector
#include <map> //map
#include <list> // std::list

#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;

#include <cstring>// strcpy, stlen

//#include <minizip/zip.h> //
/*
 * 	zipFile zf = zipOpen(outFileName, APPEND_STATUS_ADDINZIP);

 int ret = zipOpenNewFileInZip(zf, "myfile.txt", &zfi,
 NULL, 0,
 NULL, 0, "my comment for this interior file", Z_DEFLATED, Z_NO_COMPRESSION);
 zipCloseFileInZip(zf);
 zipClose(zf, "my comment for exterior file");
 */

using std::strcpy;
using std::strlen;

using std::string;
using std::stringstream;
using std::ifstream;
using std::endl;
using std::ios;
using std::vector;
using std::map;
using std::list;

using boost::iostreams::filtering_ostreambuf;

using boost::iostreams::filtering_istreambuf;
using boost::iostreams::filtering_streambuf;
using boost::iostreams::filtering_istream;
using boost::iostreams::input;
using boost::iostreams::zlib_compressor;
using boost::iostreams::zlib_decompressor;
using boost::iostreams::file_source;
using boost::iostreams::stream;

using boost::iostreams::back_insert_device;
using boost::iostreams::back_inserter;
using boost::iostreams::array_source;
using boost::filesystem::ofstream;
using boost::filesystem::path;
using boost::filesystem::filesystem_error;
using boost::iostreams::array_sink;

using boost::uintmax_t;

namespace base_game {
ZipFile::ZipFile() {
	logger::info("Create ZipFile");
	//	m_pDirData = nullptr;
//	m_pZipDirHeader = nullptr;
	m_fileData = {};
	m_pZipDirHeader = nullptr;
//	m_zipFileAssetVec = {};
	m_zipContentsMap = map<std::string, ZipFileAsset*>();

}

ZipFile::~ZipFile() {
	logger::info("Destroy ZipFile");
	stringstream ss;
	ss << "PRE CLEAR: file Data size " << m_fileData.size();

	logger::info(ss);
	reset();

	ss << "POST CLEAR: file Data size " << m_fileData.size();

	logger::info(ss);

	m_zipContentsMap.clear();

}

void ZipFile::describeYourself() {
	stringstream ss;

	ss << "ZipFile DescribeYourself";
	logger::trace(ss);

	unsigned short nEntries = this->getNumberOfEntries();

	ss << "Number of Entries: " << nEntries;
	logger::trace(ss);

	TZipDirHeader* pZipDirHeader = getZipDirHeader();
	if (pZipDirHeader) {
		pZipDirHeader->describeYourself();
	}

	for (map<string, ZipFileAsset*>::iterator it = m_zipContentsMap.begin();
			it != m_zipContentsMap.end(); ++it) {
		ss << "m_zipContentsMap key: |" << it->first << "|";
		logger::trace(ss);

		it->second->describeYourself();
	}
}

void ZipFile::reset() {
	//TODO: FINAL CANDIDATE?
	m_fileData.clear();

	m_pZipDirHeader = nullptr;

}

bool ZipFile::isZipLocalHeaderCorrect(TZipLocalHeader* pZipLocalHeader) {
	stringstream ss;
	if (pZipLocalHeader->sig != TZipLocalHeader::SIGNATURE) {
		ss << "Wrong TZipLocalHeader signature: " << std::hex
				<< pZipLocalHeader->sig;

		logger::warning(ss);

		return false;
	} else {
		ss << "Correct TZipLocalHeader signature " << std::hex
				<< pZipLocalHeader->sig;
		logger::info(ss);
		return true;
	}
}

bool ZipFile::initZipFileAsset(ZipFileAsset* pZipFileAsset, char* pAsset) {
	stringstream ss;

	ss << "PRE pASSET address: " << (void *) pAsset;
	logger::info(ss);

	pZipFileAsset->setZipLocalHeader(
			reinterpret_cast<TZipLocalHeader*>(pAsset));

	if (!isZipLocalHeaderCorrect(pZipFileAsset->getZipLocalHeader())) {
		return false;
	}

	pAsset += sizeof(TZipLocalHeader);

	char* pFileName = pAsset;
	std::string assetFileName;

	for (int i = 0; i < pZipFileAsset->getFileNameLength(); i++) {
		assetFileName.push_back(*pFileName);
		pFileName++;
	}

	pZipFileAsset->setFileName(assetFileName);

	string unizpFilename;

	unizpFilename = getUnzipFilename(pZipFileAsset);

	ss << "FILE NAME: " << unizpFilename;
	logger::info(ss);

	// unizpFilename = this->getUnzipFilename(pZipFileAsset);
	/*
	 if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
	 unizpFilename = pZipFileAsset->getFileName();
	 ss << "VEC FILE NAME: " << unizpFilename;
	 logger::info(ss);

	 } else {
	 unizpFilename = this->zipToUnzip(pZipFileAsset->getFileName());
	 ss << "UNZIP FILE NAME: " << unizpFilename;
	 logger::info(ss);

	 }
	 */

	pAsset += pZipFileAsset->getFileNameLength();

	pZipFileAsset->setDirData(pAsset);

	pAsset += pZipFileAsset->getFileDataSize();

	ss << "POST pASSET address: " << (void *) pAsset;
	logger::info(ss);

	this->m_zipContentsMap[unizpFilename] = pZipFileAsset;
	//this->m_zipContentsMap[pZipFileAsset->getFileName()] = pZipFileAsset;

	return true;
}

bool ZipFile::isZipFileHeaderCorrect(TZipDirFileHeader* pZipDirFileHeader,
		int i) {
	stringstream ss;

	if (pZipDirFileHeader->sig != TZipDirFileHeader::SIGNATURE) {
		ss << "Wrong TZipDirFileHeader[" << i << "] signature: " << std::hex
				<< pZipDirFileHeader->sig;
		; //<< std::dec;
		logger::warning(ss);

		return false;
	} else {
		ss << "Correct TZipDirFileHeader[" << i << "] signature " << std::hex
				<< pZipDirFileHeader->sig;
		logger::info(ss);
		return true;
	}
}

bool ZipFile::initDirFileHeaders(unsigned short nDirEntries) {
	stringstream ss;

	char* pDirFileHeaderData = m_fileData.data();

	int offsetDirHeaders = sizeof(TZipDirHeader)
			+ nDirEntries * sizeof(TZipDirFileHeader);

	pDirFileHeaderData += m_fileData.size() - offsetDirHeaders;

	char* pLocalHeaderData = m_fileData.data();

	int totalOffset = 0;

	for (int i = 0; i < nDirEntries; i++) {

		ZipFileAsset* zipFileAsset = new ZipFileAsset();

		ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
				<< (void *) pLocalHeaderData;
		logger::info(ss);

		zipFileAsset->setZipDirFileHeader(
				reinterpret_cast<TZipDirFileHeader*>(pDirFileHeaderData));

		if (!isZipFileHeaderCorrect(zipFileAsset->getZipDirFileHeader(), i)) {
			return false;
		};

		int offsetFile = sizeof(TZipLocalHeader)
				+ zipFileAsset->getZipDirFileHeader()->fnameLen
				+ zipFileAsset->getZipDirFileHeader()->cSize;

		bool result = initZipFileAsset(zipFileAsset, pLocalHeaderData);

		ss << "POST INIT LOCAL HEADER pLocalHeaderData address: "
				<< (void *) pLocalHeaderData;
		logger::info(ss);

		if (result == false) {
			return false;
		}

		totalOffset += offsetFile;

		pLocalHeaderData += offsetFile;

		pDirFileHeaderData += sizeof(TZipDirFileHeader);

	}
	return true;
}

bool ZipFile::initZipDirHeader() {
	stringstream ss;

	char* pDirData = m_fileData.data();
	pDirData += m_fileData.size() - sizeof(TZipDirHeader);
	m_pZipDirHeader = reinterpret_cast<TZipDirHeader*>(pDirData);

	bool result = true;
	if (m_pZipDirHeader->sig != TZipDirHeader::SIGNATURE) {
		ss << "Wrong TZipDirHeader signature: " << std::hex
				<< m_pZipDirHeader->sig;
		; //<< std::dec;
		logger::warning(ss);

		result = false;
	} else {
		ss << "Correct TZipDirHeader signature " << std::hex
				<< m_pZipDirHeader->sig;
		logger::info(ss);
	}
	return result;
}

bool ZipFile::init(const std::string& resFileName,
		unsigned short inputSaveMode) {

	reset();
	//isCompressed = ZipFile::NOT_COMPRESSED;
	isCompressed = inputSaveMode;

	stringstream ss;

	path filePath { resFileName };

	boost::filesystem::ifstream assetFile(filePath, std::ios::binary);

	if (assetFile.is_open()) {
		ss << "OPEN OPEN OPEN " << filePath.string();
		logger::info(ss);

		filtering_istreambuf filterIn;
		filterIn.push(assetFile);

		boost::iostreams::copy(filterIn,
				boost::iostreams::back_inserter(m_fileData));

		bool result = initZipDirHeader();
		if (result == true) {
			TZipDirHeader* pZipDirHeader = getZipDirHeader();

			result = initDirFileHeaders(pZipDirHeader->nDirEntries);

		}

		assetFile.close();
		if (result == false) {
			reset();

			return false;
		} else {
			return true;

		}

	} else {
		ss << "CLOSED " << filePath.string();
		logger::warning(ss);
		return false;
	}

}

TZipDirHeader* ZipFile::getZipDirHeader() {
	if (m_pZipDirHeader) {
		return m_pZipDirHeader;
	}

	if (m_fileData.empty()) {
		return nullptr;
	}

	if (m_fileData.size() < sizeof(TZipDirHeader)) {
		return nullptr;
	}

	char* pDirData = m_fileData.data();
	pDirData += m_fileData.size() - sizeof(TZipDirHeader);

	m_pZipDirHeader = reinterpret_cast<TZipDirHeader*>(pDirData);

	return m_pZipDirHeader;
}

unsigned short ZipFile::getNumberOfEntries() {
	TZipDirHeader* pZipDirHeader = this->getZipDirHeader();

	unsigned short result = 0;
	if (pZipDirHeader) {
		result = pZipDirHeader->nDirEntries;
	}

	return result;
}

void ZipFile::saveFileNameNoCompression(TZipLocalHeader& lh, ofstream& ofs,
		ZipFileAsset* pZipFileAsset) {
	const string fileName = pZipFileAsset->getFileName();

	//local header
	lh.fnameLen = pZipFileAsset->getFileNameLength();
	//TODO: compression
	//lh.compression = TZipLocalHeader::Z_DEFLATED; //??
	//lh.compression = TZipLocalHeader::Z_NO_COMPRESSION; //??
	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));
	lh.describeYourself();

	//file name
	filtering_istreambuf filterFileName;

	array_source source(fileName.c_str(), pZipFileAsset->getFileNameLength());
	filterFileName.push(source);

	vector<char> vecFileName;
	boost::iostreams::copy(filterFileName,
			boost::iostreams::back_inserter(vecFileName));

	ofs.write(reinterpret_cast<char *>(vecFileName.data()), vecFileName.size());

}

void ZipFile::saveFileNameCompression(TZipLocalHeader& lh, ofstream& ofs,
		ZipFileAsset* pZipFileAsset) {

	const string fileName = pZipFileAsset->getFileName();

	// file name
	filtering_istreambuf filterFileName;
	filterFileName.push(zlib_compressor());

	array_source source(fileName.c_str(), pZipFileAsset->getFileNameLength());
	filterFileName.push(source);

	vector<char> vecFileName;
	boost::iostreams::copy(filterFileName,
			boost::iostreams::back_inserter(vecFileName));

	//local header
	lh.fnameLen = vecFileName.size();
	//TODO: compression
	//lh.compression = TZipLocalHeader::Z_DEFLATED; //??
	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	lh.describeYourself();

	//file name
	ofs.write(reinterpret_cast<char *>(vecFileName.data()), vecFileName.size());
}

void ZipFile::saveFileNameDecompression(TZipLocalHeader& lh, ofstream& ofs,
		ZipFileAsset* pZipFileAsset) {

	const string fileName = pZipFileAsset->getFileName();

	// file name
	filtering_istreambuf filterFileName;
	filterFileName.push(zlib_decompressor());

	array_source source(fileName.c_str(), pZipFileAsset->getFileNameLength());
	filterFileName.push(source);

	vector<char> vecFileName;
	boost::iostreams::copy(filterFileName,
			boost::iostreams::back_inserter(vecFileName));

	//lh.fnameLen = zipFileAsset->getFileNameLength();
	lh.fnameLen = vecFileName.size();
	//TODO: compression
	//lh.compression = TZipLocalHeader::Z_NO_COMPRESSION; //??
	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	lh.describeYourself();

	//file name
	ofs.write(reinterpret_cast<char *>(vecFileName.data()), vecFileName.size());
}

void ZipFile::saveAssetFileName(TZipLocalHeader& lh, ofstream& ofs,
		ZipFileAsset* pZipFileAsset, unsigned short outputSaveMode) {

	const string fileName = pZipFileAsset->getFileName();

	lh.compression = outputSaveMode;

	stringstream ss;

	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves not compressed file name: " << fileName
					<< " as not compressed";
			logger::info(ss);

			this->saveFileNameNoCompression(lh, ofs, pZipFileAsset);
		} else {
			ss << "Saves not compressed file name: " << fileName
					<< " as compressed";
			logger::info(ss);
			this->saveFileNameCompression(lh, ofs, pZipFileAsset);

		}
	} else {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves compressed file name: " << fileName
					<< " as not compressed";
			logger::info(ss);
			this->saveFileNameDecompression(lh, ofs, pZipFileAsset);

		} else {
			ss << "Saves compressed file name: " << fileName
					<< " as compressed";
			logger::info(ss);

			this->saveFileNameNoCompression(lh, ofs, pZipFileAsset);
		}
	}

}

void ZipFile::saveAssetFileNoCompression(ofstream& ofs,
		ZipFileAsset* pZipFileAsset, vector<char>& vecFileContents) {

	stringstream ss;
	// Do not push zlib_compressor()

	filtering_istreambuf filterAssetFile;

	array_source source(pZipFileAsset->getDirData(),
			pZipFileAsset->getFileDataSize());
	filterAssetFile.push(source);
	boost::iostreams::copy(filterAssetFile,
			boost::iostreams::back_inserter(vecFileContents));

	ss << "vecFileContents1.size: " << vecFileContents.size();
	logger::info(ss);

	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());
	ss << "vecFileContents2.size: " << vecFileContents.size();
	logger::info(ss);
	ss << "XX";
	logger::info(ss);

}

void ZipFile::saveAssetFileCompression(ofstream& ofs,
		ZipFileAsset* pZipFileAsset, vector<char>& vecFileContents) {

	filtering_istreambuf filterAssetFile;

	filterAssetFile.push(zlib_compressor());

	array_source source(pZipFileAsset->getDirData(),
			pZipFileAsset->getFileDataSize());

	filterAssetFile.push(source);

	boost::iostreams::copy(filterAssetFile,
			boost::iostreams::back_inserter(vecFileContents));

	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());

}

void ZipFile::saveAssetFileDecompression(ofstream& ofs,
		ZipFileAsset* pZipFileAsset, vector<char>& vecFileContents) {
	filtering_istreambuf filterAssetFile;

	filterAssetFile.push(zlib_decompressor());

	array_source source(pZipFileAsset->getDirData(),
			pZipFileAsset->getFileDataSize());

	filterAssetFile.push(source);

	boost::iostreams::copy(filterAssetFile,
			boost::iostreams::back_inserter(vecFileContents));

	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());
}

bool ZipFile::saveAssetFileContents(ofstream& ofs, ZipFileAsset* pZipFileAsset,
		unsigned short outputSaveMode, vector<char>& vecFileContents) {

	stringstream ss;

	filtering_istreambuf filterAssetFile;

	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->getFileName() << " as not compressed";
			logger::info(ss);

			this->saveAssetFileNoCompression(ofs, pZipFileAsset,
					vecFileContents);

		} else {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->getFileName() << " as compressed";
			logger::info(ss);
			this->saveAssetFileCompression(ofs, pZipFileAsset, vecFileContents);

		}
	} else {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves compressed file contents: "
					<< pZipFileAsset->getFileName() << " as not compressed";
			logger::info(ss);
			this->saveAssetFileDecompression(ofs, pZipFileAsset,
					vecFileContents);

		} else {
			ss << "Saves compressed file contents: "
					<< pZipFileAsset->getFileName() << " as compressed";
			logger::info(ss);

			this->saveAssetFileNoCompression(ofs, pZipFileAsset,
					vecFileContents);

		}
	}

	return true;
}

bool ZipFile::saveAsset(ofstream& ofs, ZipFileAsset* pZipFileAsset,
		list<TZipDirFileHeader*>& dirFileHeadersList, const TZipDirHeader& dh,
		unsigned short outputSaveMode) {

	stringstream ss;

	ss << "SAVE_ASSET_ZIP_FILE ";
	logger::info(ss);

	TZipLocalHeader lh;

	lh.describeYourself();

	this->saveAssetFileName(lh, ofs, pZipFileAsset, outputSaveMode);

	vector<char> vecFileContents;
	this->saveAssetFileContents(ofs, pZipFileAsset, outputSaveMode,
			vecFileContents);

	lh.describeYourself();

	ss << "vecFileContents3.size()" << vecFileContents.size();
	logger::info(ss);

	TZipDirFileHeader* dfh = new TZipDirFileHeader();
	dfh->ucSize = pZipFileAsset->getUnzipFileDataSize();
	dfh->cSize = vecFileContents.size();
	dfh->fnameLen = lh.fnameLen;
	dfh->compression = outputSaveMode;
	dirFileHeadersList.push_back(dfh);

	return true;

}

// Saves data as compressed file
//bool ZipFile::saveNotCompressed(const std::string& outFileName) {
bool ZipFile::save(const std::string& outFileName,
		unsigned short outputSaveMode) {

	stringstream ss;
	path filePath { outFileName };

	ss << "save->fileName: " << outFileName;
	logger::info(ss);

	ofstream ofs(filePath, std::ios::binary);

	bool isOpen = ofs.is_open();

	if (!isOpen) {
		ss << "CLOSED " << filePath.string();
		logger::warning(ss);
		return false;
	};

	TZipDirHeader dh;
	list<TZipDirFileHeader*> dirFileHeadersList;

	for (map<string, ZipFileAsset*>::iterator it = m_zipContentsMap.begin();
			it != m_zipContentsMap.end(); ++it) {

		ss << "fileName: " << it->second->getFileName();
		logger::info(ss);

		//this->saveAsset(ofs, resourcePath, replacedPath, dirFileHeadersList, dh,
		//		ZipFile::NOT_COMPRESSED);

		this->saveAsset(ofs, it->second, dirFileHeadersList, dh,
				outputSaveMode);

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

		(*it)->describeYourself();

		ofs.write(reinterpret_cast<char *>(*it), sizeof(TZipDirFileHeader)); // OK wynik plik: ABCD; dla kompresji: x.strv...
	};

	// Save TZipDirHeader
	dh.nDirEntries = dirFileHeadersList.size();
	dh.isCompression = outputSaveMode;
	ofs.write(reinterpret_cast<char *>(&dh), sizeof(dh));

	ofs.close();
	return true;
}

bool ZipFile::prepareOutputDir(const string assetsOutFolder) {

	stringstream ss;

	ss << "ZipFile prepareOutputDir: " << assetsOutFolder;
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

string ZipFile::zipToUnzip(string zipString) const {

	stringstream ss;

	filtering_istreambuf filter;
	filter.push(zlib_decompressor());
	array_source source(zipString.c_str(), zipString.length());

	ss << "zipStgring: " << zipString;
	logger::info(ss);

	ss << "zipString.length(): " << zipString.length();
	logger::info(ss);

	filter.push(source);

	vector<char> vecString;
	boost::iostreams::copy(filter, boost::iostreams::back_inserter(vecString));

	string unzipString;
	ss << "";
	for (vector<char>::iterator it = vecString.begin(); it != vecString.end();
			++it) {
		unzipString.push_back(*it);

		ss << *it;
	}
	logger::info(ss);
	ss << "";
	logger::info(ss);

	//string unzipString(vecString.data());

	ss << "zipString: " << zipString << "unzipString: " << unzipString;
	logger::info(ss);

	return unzipString;

}

bool ZipFile::createFilesAndFolders(const string folderName) {
	stringstream ss;

	logger::info("START createFilesAndFolders");

	for (map<string, ZipFileAsset*>::iterator it = m_zipContentsMap.begin();
			it != m_zipContentsMap.end(); ++it) {

		ss << "fileName: " << it->second->getFileName();
		logger::info(ss);

		path pathAsset { folderName };

		if (ZipFile::COMPRESSED == this->isCompressed) {

			// m_zipContentsMap should contain unzipped filenames
			string unzipFileName = this->zipToUnzip(it->second->getFileName());
			//string unzipFileName = it->second->getFileName();

			pathAsset /= unzipFileName;
		} else {

			// No need to unzip
			pathAsset /= it->second->getFileName();
		}
		path fullAssetPath { pathAsset };

		ss << "full preferred Path: " << pathAsset.make_preferred();
		logger::info(ss);

		path assetFileName { pathAsset.filename() };
		ss << "only filename " << assetFileName;
		logger::info(ss);

		pathAsset.remove_filename();
		ss << "no filename preferred Path: " << pathAsset.make_preferred();
		logger::info(ss);

		createFolder(pathAsset);

		copyFile(fullAssetPath, it->second);

	}

	logger::info("END createFilesAndFolders");

	return true;
}

bool ZipFile::createFolder(path newFolder) {
	stringstream ss;

	if (exists(newFolder)) {
		ss << "ALREADY EXISTS: " << newFolder.string();
		logger::info(ss);

	} else {
		ss << "CREATING NEW: " << newFolder.string();
		logger::info(ss);

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

void ZipFile::copyFile(path inPath, ZipFileAsset* pZipFileAsset) {
	stringstream ss;

	if (ZipFile::NOT_COMPRESSED == isCompressed) {
		ss << "Saving not compressed files to folder";
		logger::info(ss);

		// Nothing needs any changes

		copyUnzipFile(inPath, pZipFileAsset);
	} else {
		ss << "Saving compressed files to folder";
		logger::info(ss);

		// unzipping must be performed !!!
		// use zlib_decompressor
		copyZipFile(inPath, pZipFileAsset);
	}

}

void ZipFile::copyZipFile(path inPath, ZipFileAsset* pZipFileAsset) {
	stringstream ss;
	ss << "copy file into: " << inPath.make_preferred();
	logger::info(ss);

	filtering_istreambuf filter;
	filter.push(zlib_decompressor());

	/*
	 ss << "Length: " << pZipFileAsset->getFileDataSize();
	 logger::info(ss);

	 ss << "--------- START ZIP-FILE---------";
	 logger::info(ss);

	 char* pDirData = pZipFileAsset->getDirData();

	 for (int i = 0; i << pZipFileAsset->getFileDataSize(); i++) {
	 ss << *(pDirData + i);
	 }
	 logger::info(ss);

	 ss << "---------  END ZIP-FILE  ---------";
	 logger::info(ss);
	 */

	array_source source(pZipFileAsset->getDirData(),
			pZipFileAsset->getFileDataSize());
	filter.push(source);

	vector<char> vecFileContents;
	// copy filterAssetFile to vecFileContents
	boost::iostreams::copy(filter,
			boost::iostreams::back_inserter(vecFileContents));
	ofstream ofs(inPath, std::ios::binary);
	ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
			vecFileContents.size());
	ofs.close();
}

void ZipFile::copyUnzipFile(path inPath, ZipFileAsset* pZipFileAsset) {
	stringstream ss;
	ss << "copy file into: " << inPath.make_preferred();
	logger::info(ss);

	char* filePointer = pZipFileAsset->getDirData();

	vector<char> vecCharDec;
	for (uintmax_t i = 0; i < pZipFileAsset->getFileDataSize(); i++) {
		vecCharDec.push_back(*filePointer);
		filePointer++;
	}

	ofstream ofs(inPath, std::ios::binary);
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size());
	ofs.close();
}

// Saves data as compressed file
void ZipFile::saveAsFolder(const string& outFolderName) {
	prepareOutputDir(outFolderName);
	createFilesAndFolders(outFolderName);
}

// --------------------------------------------------------------------------
// Function:      ReadFile
// Purpose:       Uncompress a complete file
// Parameters:    The file index and the pre-allocated buffer
// --------------------------------------------------------------------------
/*
 bool ZipFile::readFile(int i, void *pBuf) {
 // TODO: decompress file
 // implememted as ZipFileAsset::readFile(*pBuf)

 return true;
 }
 */

ZipFileAsset* ZipFile::find(const string &name) const {

	map<string, ZipFileAsset*>::const_iterator it;
	it = m_zipContentsMap.find(name);

	if (it != m_zipContentsMap.end()) {
		return it->second;
	}

	return nullptr;
}

string ZipFile::getUnzipFilename(ZipFileAsset* pZipFileAsset) const {
	stringstream ss;
	string unzipFilename = "";
	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		unzipFilename = pZipFileAsset->getFileName();
		ss << "VEC FILE NAME: " << unzipFilename;
		logger::info(ss);

	} else {
		unzipFilename = this->zipToUnzip(pZipFileAsset->getFileName());
		ss << "UNZIP FILE NAME: " << unzipFilename;
		logger::info(ss);

	}
	return unzipFilename;
}

//string ZipFile::getFilename(int i) {
string ZipFile::getFilename(int i) const {
	string fileName = "";

	map<string, ZipFileAsset*>::const_iterator it;

	for (it = m_zipContentsMap.begin(); it != m_zipContentsMap.end(); ++it) {
		if (i <= 0) {
			break;
		}
		i--;
	}

	/*
	 for (int index = 1; index <= i; index++) {
	 ++it;
	 }*/
	ZipFileAsset* zipFileAsset = it->second;

	fileName = getUnzipFilename(zipFileAsset);
	/*
	 if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
	 fileName = zipFileAsset->getFileName();
	 } else {
	 fileName = this->zipToUnzip(zipFileAsset->getFileName());
	 }
	 */

	return fileName;
	/*
	 std::string fileName = "";
	 if (i >= 0 && i < m_nEntries) {
	 char pszDest[_MAX_PATH];
	 memcpy(pszDest, m_papDir[i]->GetName(), m_papDir[i]->fnameLen);
	 pszDest[m_papDir[i]->fnameLen] = '\0';
	 fileName = pszDest;
	 }
	 return fileName;
	 */

}

}

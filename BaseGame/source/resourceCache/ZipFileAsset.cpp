/*
 * ZipFileAsset.cpp
 *
 *  Created on: 10.11.2017
 *      Author: Krzysztof
 */

#include "ZipFileAsset.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"
#include "../utilities/StringUtils.h"

#include <string>
#include <sstream>      // std::stringstream
#include <vector> // vector
#include <cstring>// strcpy
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <boost/iostreams/filter/zlib.hpp> // zlib_decompressor
#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/device/array.hpp> // boost::iostreams::array_source, boost::iostreams::array_sink
#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;  boost::filesystem::ifstream;

using std::string;
using std::stringstream;
using boost::uintmax_t;
using std::vector;
using std::strcpy;

using boost::iostreams::filtering_istreambuf;
using boost::iostreams::zlib_decompressor;
using boost::iostreams::array_source;
using boost::filesystem::ofstream;
using boost::filesystem::path;


namespace base_game {

ZipFileAsset::ZipFileAsset() {
	logger::info("Create ZipFileAsset");
	m_pZipDirFileHeader = nullptr;
	m_pZipLocalHeader = nullptr;
	m_pDirData = nullptr;
	fileName = "";

}

ZipFileAsset::~ZipFileAsset() {
	logger::info("Destroy ZipFileAsset");

	fileName.clear();

	//templates::safe_delete<char> (m_pDirData);
	//templates::safe_delete<TZipLocalHeader> (m_pZipLocalHeader);
	//templates::safe_delete<TZipDirFileHeader> (m_pZipDirFileHeader);
}

unsigned short ZipFileAsset::getFileNameLength() {
	if (m_pZipDirFileHeader) {
		return m_pZipDirFileHeader->fnameLen;
	}
	return 0;

}

uintmax_t ZipFileAsset::getFileDataSize() {
	if (m_pZipDirFileHeader) {
		return m_pZipDirFileHeader->cSize;
	}
	return 0;
}

uintmax_t ZipFileAsset::getUnzipFileDataSize() {
	if (m_pZipDirFileHeader) {
		return m_pZipDirFileHeader->ucSize;
	}
	return 0;
}


TZipDirFileHeader* ZipFileAsset::getZipDirFileHeader() {
	return this->m_pZipDirFileHeader;
}

void ZipFileAsset::setZipDirFileHeader(TZipDirFileHeader* header) {
	m_pZipDirFileHeader = header;
}

TZipLocalHeader* ZipFileAsset::getZipLocalHeader() {
	return this->m_pZipLocalHeader;
}

void ZipFileAsset::setZipLocalHeader(TZipLocalHeader* header) {
	m_pZipLocalHeader = header;
}

char* ZipFileAsset::getDirData() {
	return this->m_pDirData;
}

void ZipFileAsset::setDirData(char* data) {
	m_pDirData = data;
}

std::string ZipFileAsset::getFileName() {
	return this->fileName;
}

void ZipFileAsset::setFileName(std::string name) {
	fileName = name;
}


bool ZipFileAsset::readFile(char* buffer) {
	// TODO: decompress file
	// implememted as ZipFileAsset::readFile(*pBuf)

	for (int i = 0; i < this->getFileDataSize(); i++) {
		*(buffer + i) = *(m_pDirData + i);
	}
	
	return true;
}

bool ZipFileAsset::readAndUnzipFile(char* buffer) {

	/*
	for (int i = 0; i < this->getFileDataSize(); i++) {
		*(buffer + i) = *(m_pDirData + i);
	}
	 */

	stringstream ss;

	filtering_istreambuf filter;
	filter.push(zlib_decompressor());

	/*
	string dirDataStr = string_utils::charToString(m_pDirData);

	ss << "Length: " << dirDataStr.length();
	logger::info(ss);

	ss << "Length FileData: " << getFileDataSize();
	logger::info(ss);

	ss << "--------- START ASSET---------";
	logger::info(ss);

	const char* pDirData = dirDataStr.c_str();

	for (int i = 0; i << dirDataStr.length(); i++) {
		ss << *(pDirData + i);
	}
	logger::info(ss);

	ss << "---------  END ASSET ---------";
	logger::info(ss);
	 */

	//array_source source(pZipFileAsset->getDirData(),
	//		pZipFileAsset->getFileDataSize());

	//array_source source(zipString.c_str(), zipString.length());


	string dirDataStr = string_utils::charToString(m_pDirData);

	ss << "ZipFileAssset-Length: " << dirDataStr.length();
	logger::info(ss);

	ss << "ZipFileAssset-Length FileData: " << getFileDataSize();
	logger::info(ss);


	char* pStart = m_pDirData;
	int i = 0;
	while (*(pStart + i)) {
		i++;
	};

	ss << "ZipFileAssset-dlugosc: " << i;
	logger::info(ss);

	int sizeAll = sizeof(m_pDirData);
	int sizeOne = sizeof(m_pDirData[0]);
	int sizeRes = sizeAll / sizeOne;




	// array_source source(dirDataStr.c_str(), dirDataStr.length() + 1);
	array_source source(getDirData(), getFileDataSize()); // OK

	// array_source source(*m_pDirData,
	//		*(m_pDirData + this->getFileDataSize() - 1));


	filter.push(source);

	vector<char> vecString;
	boost::iostreams::copy(filter, boost::iostreams::back_inserter(vecString));

	this->debugSaveAsFile(vecString);

	int position = 0;
	for (vector<char>::iterator it = vecString.begin(); it != vecString.end();
			++it) {
		*(buffer + position) = *it;
		position++;
	}

	return true;
}

void ZipFileAsset::debugSaveAsFile(vector<char> vecString) {
	stringstream ss;
	string fileName = "debug_zip_file_asset";	// + getFileName();
	ss << "Debug-Save-As-File: " << fileName;
	logger::info(ss);

	path inPath { fileName };

	ofstream ofs(inPath, std::ios::binary);
	ofs.write(reinterpret_cast<char *>(vecString.data()), vecString.size());
	ofs.close();
}


void ZipFileAsset::describeYourself() {
	stringstream ss;

	ss << "ZipFileAsset DescribeYourself";
	logger::trace(ss);

	ss << "FileName: " << fileName;
	logger::trace(ss);

	m_pZipDirFileHeader->describeYourself();

	m_pZipLocalHeader->describeYourself();

	ss << "FILE CONTENTS: ";
	logger::trace(ss);

	ss << "ZipFileAsset DescribeYourself END";
	logger::trace(ss);
}

} /* namespace base_game */

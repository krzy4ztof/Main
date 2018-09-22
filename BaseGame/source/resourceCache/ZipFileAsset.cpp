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


using std::string;
using std::stringstream;
using boost::uintmax_t;
using std::vector;
using std::strcpy;

using boost::iostreams::filtering_istreambuf;
using boost::iostreams::zlib_decompressor;
using boost::iostreams::array_source;


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

	string dirDataStr = string_utils::charToString(m_pDirData);

	//array_source source(zipString.c_str(), zipString.length());
	array_source source(dirDataStr.c_str(), dirDataStr.length());

	// array_source source(*m_pDirData,
	//		*(m_pDirData + this->getFileDataSize() - 1));


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

	strcpy(buffer, unzipString.c_str());



	//string unzipString(vecString.data());

//	return unzipString;
	return true;
}


void ZipFileAsset::describeYourself() {
	stringstream ss;

	ss << "ZipFileAsset DescribeYourself";
	logger::info(ss);

	ss << "FileName: " << fileName;
	logger::info(ss);

	m_pZipDirFileHeader->describeYourself();

	m_pZipLocalHeader->describeYourself();

	ss << "FILE CONTENTS: ";
	logger::info(ss);

	ss << "ZipFileAsset DescribeYourself END";
	logger::info(ss);
}

} /* namespace base_game */

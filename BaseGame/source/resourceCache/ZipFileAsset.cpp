/*
 * ZipFileAsset.cpp
 *
 *  Created on: 10.11.2017
 *      Author: Krzysztof
 */

#include "ZipFileAsset.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"

#include <string>
#include <sstream>      // std::stringstream

using std::string;
using std::stringstream;

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

unsigned long ZipFileAsset::getFileDataSize() {
	if (m_pZipDirFileHeader) {
		return m_pZipDirFileHeader->cSize;
	}
	return 0;
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

/*
 * ZipFileAsset.h
 *
 *  Created on: 10.11.2017
 *      Author: Krzysztof
 */

#ifndef SOURCE_RESOURCECACHE_ZIPFILEASSET_H_
#define SOURCE_RESOURCECACHE_ZIPFILEASSET_H_

#include "TZipDirFileHeader.h"
#include "TZipLocalHeader.h"

#include <string>

namespace base_game {

class ZipFileAsset {
public:
	ZipFileAsset();
	virtual ~ZipFileAsset();

	TZipDirFileHeader *m_pZipDirFileHeader;
	TZipLocalHeader *m_pZipLocalHeader;
	char *m_pDirData;	// Raw data buffer.
	std::string fileName;

	unsigned short getFileNameLength();
	unsigned long getFileDataSize();

	void describeYourself();

};

} /* namespace base_game */

#endif /* SOURCE_RESOURCECACHE_ZIPFILEASSET_H_ */

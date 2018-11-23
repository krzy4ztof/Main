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
#include <vector> //vector
#include <boost/cstdint.hpp> // boost::uintmax_t

namespace base_game {

class ZipFileAsset {
public:
	ZipFileAsset();
	virtual ~ZipFileAsset();

	TZipDirFileHeader* getZipDirFileHeader();
	void setZipDirFileHeader(TZipDirFileHeader* header);

	TZipLocalHeader* getZipLocalHeader();
	void setZipLocalHeader(TZipLocalHeader* header);

	char* getDirData();

	void setDirData(char* data);

	std::string getFileName();
	void setFileName(std::string name);


	unsigned short getFileNameLength();
	boost::uintmax_t getFileDataSize();
	boost::uintmax_t getUnzipFileDataSize();

	bool readFile(char* buffer);
	bool readAndUnzipFile(char* buffer);
	void describeYourself();

protected:
	void debugSaveAsFile(std::vector<char> vecString);


private:
	TZipDirFileHeader *m_pZipDirFileHeader;
	TZipLocalHeader *m_pZipLocalHeader;
	char *m_pDirData;	// Raw data buffer.
	std::string fileName;


};

} /* namespace base_game */

#endif /* SOURCE_RESOURCECACHE_ZIPFILEASSET_H_ */

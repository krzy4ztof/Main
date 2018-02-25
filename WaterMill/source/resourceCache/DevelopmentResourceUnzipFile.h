/*
 * DevelopmentResourceUnzipFile.h
 *
 *  Created on: 29.10.2017
 *      Author: Krzysztof
 */

#ifndef SOURCE_RESOURCECACHE_DEVELOPMENTRESOURCEUNZIPFILE_H_
#define SOURCE_RESOURCECACHE_DEVELOPMENTRESOURCEUNZIPFILE_H_

#include "IResourceFile.h"
#include "ZipFile.h"

#include <string> //string

namespace base_game {

class DevelopmentResourceUnzipFile: public IResourceFile {
public:
	DevelopmentResourceUnzipFile(const std::string folderName,
			const std::string fileName);

	virtual ~DevelopmentResourceUnzipFile();

	virtual bool vOpen();

protected:
	virtual bool vSaveFolderMode();
	virtual bool vSaveUnzipMode();
	virtual bool vSaveZipMode();

private:
	ZipFile *m_pZipFile;
	std::string m_resFileName;

};

} /* namespace base_game */

#endif /* SOURCE_RESOURCECACHE_DEVELOPMENTRESOURCEUNZIPFILE_H_ */

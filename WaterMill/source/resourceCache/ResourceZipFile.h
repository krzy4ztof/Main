#ifndef RESOURCEZIPFILE_H
#define RESOURCEZIPFILE_H

#include "IResourceFile.h"
#include "ZipFile.h"

#include <string> //string

namespace base_game {
class ResourceZipFile: public IResourceFile {
public:
	ResourceZipFile(const std::string folderName, const std::string fileName);

	virtual ~ResourceZipFile();
	virtual bool vOpen();
	//		virtual bool vSave(const std::string saveMode);

protected:
	virtual bool vSaveFolderMode();
	virtual bool vSaveUnzipMode();
	virtual bool vSaveZipMode();

private:
	ZipFile *m_pZipFile;
	std::string m_resFileName;
	//	std::string m_readMode;
};
}
#endif // RESOURCEZIPFILE_H

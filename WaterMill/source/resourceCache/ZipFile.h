#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <string> //string
#include <vector> //vector
#include <map> //map
#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream;
#include "TZipDirHeader.h"
#include "TZipDirFileHeader.h"
#include "TZipLocalHeader.h"
#include "ZipFileAsset.h"

namespace base_game {
class ZipFile {
public:
	enum {
		NOT_COMPRESSED = 0, COMPRESSED = 1
	};

	ZipFile();
	virtual ~ZipFile();

	bool readFile(int i, void *pBuf);

	bool init(const std::string& resFileName, unsigned short inputSaveMode);
	bool save(const std::string& outFileName, unsigned short outputSaveMode);
	void saveAsFolder(const std::string& outFolderName); 


	void describeYourself();

protected:
	TZipDirHeader* getZipDirHeader();
	void reset();
	unsigned short getNumberOfEntries();
	bool initZipDirHeader();
	bool initDirFileHeaders(unsigned short nDirEntries); 

	bool initZipFileAsset(ZipFileAsset* pZipFileAsset, char* pLocalHeader); 

	bool isZipFileHeaderCorrect(TZipDirFileHeader* pZipDirFileHeader, int i);
	bool isZipLocalHeaderCorrect(TZipLocalHeader* pZipLocalHeader);

	bool prepareOutputDir(const std::string folderName);
	bool createFilesAndFolders(const std::string folderName);
	bool createFolder(boost::filesystem::path newFolder);
	bool copyFile(boost::filesystem::path inPath, ZipFileAsset* pZipFileAsset); 
	bool copyUnzipFile(boost::filesystem::path inPath,
			ZipFileAsset* pZipFileAsset);
	bool copyZipFile(boost::filesystem::path inPath,
			ZipFileAsset* pZipFileAsset);

	bool saveAsset(boost::filesystem::ofstream& ofs,
			ZipFileAsset* pZipFileAsset,
			std::list<TZipDirFileHeader*>& dirFileHeadersList,
			const TZipDirHeader& dh, unsigned short outputSaveMode);

	bool saveAssetFileName(TZipLocalHeader& lh,
			boost::filesystem::ofstream& ofs, ZipFileAsset* zipFileAsset,
			unsigned short outputSaveMode);

	bool saveAssetFileContents(boost::filesystem::ofstream& ofs,
			ZipFileAsset* pZipFileAsset, unsigned short outputSaveMode,
			std::vector<char>& vecFileContents);


	std::string zipToUnzip(std::string zipString); 

private:

	std::vector<char> m_fileData; //FINAL VERSION
	TZipDirHeader* m_pZipDirHeader; //FINAL VERSION

	std::map<std::string, ZipFileAsset*> m_zipContentsMap; //FINAL VERSION

	unsigned short isCompressed = 0;
};
}
#endif // ZIPFILE_H

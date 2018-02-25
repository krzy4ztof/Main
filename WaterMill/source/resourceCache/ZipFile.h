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

	bool init_333(const std::string& resFileName);
	bool temp_init_1(const std::string& resFileName);
	bool temp_init_2(const std::string& resFileName);

	bool readFile(int i, void *pBuf);

//	bool initCompressed(const std::string& resFileName); // replaced by init
	bool initNotCompressed_ok_old(const std::string& resFileName); //FINAL VERSION, replaced by init

	bool init(const std::string& resFileName, unsigned short inputSaveMode); // FINAL VERSION

	bool initNotCompressed_222(const std::string& resFileName);
	bool initCompressed_fails(const std::string& resFileName);

	// bool saveNotCompressed(const std::string& outFileName); // replaced by save
	// bool saveCompressed(const std::string& outFileName); // replaced by save
	bool save(const std::string& outFileName, unsigned short outputSaveMode); // FINAL VERSION

	void saveCompressed_111(const std::string& outFileName);
	void saveNotCompressed_111(const std::string& outFileName);

	void saveAsFolder(const std::string& outFolderName); // FINAL VERSION

	void test_saveCompressedDirFileHeader(const std::string& outFileName); // todo
	bool test_initCompressedDirFileHeader(const std::string& resFileName); // todo
	bool test_initCompressedDirFileHeaderIntoVectorChar(
			const std::string& resFileName); // ok

	void test_saveCompressedAbcd(const std::string& outFileName); // ok
	void test_saveNotCompressedAbcd(const std::string& outFileName); // ok

	void test_saveNotCompressedDirFileHeader(const std::string& outFileName); // ok
	void test_saveNotCompressedDirFileHeaderArraySource(
			const std::string& outFileName); // ok
	bool test_initNotCompressedDirFileHeader(const std::string& resFileName); // ok

	void test_saveNotCompressedAll(const std::string& outFileName,
			const std::string& assetsFolder); // ok

	int test_saveMiniZipCompressedAll(std::vector<std::wstring> paths,
			const std::string& outFileName, const std::string& assetsFolder); // in progress
	void test_saveMiniZipCompressedAll_111(const std::string& outFileName,
			const std::string& assetsFolder); // to_delete

	void test_saveSingleNotCompressedTxtFile(const std::string& inFilePath,
			boost::filesystem::ofstream& ofs); //
	bool test_initNotCompressedAll(const std::string& resFileName); // in progress
	void test_saveCompressedAll(const std::string& outFileName); // in progress
	bool test_initCompressedAll(const std::string& resFileName); // in progress

	void saveCompressedAll(const std::string& outFileName);
	void saveNotCompressedAll(const std::string& outFileName);
	void saveNotCompressedAll_111(const std::string& outFileName);

	void describeYourself();

protected:
	TZipDirHeader* getZipDirHeader(); // FINAL VERSION
	void reset(); // FINAL CANDIDATE
	unsigned short getNumberOfEntries(); //FINAL VERSION
	bool initZipDirHeader(); // FINAL VERSION
	bool initDirFileHeaders(unsigned short nDirEntries); //FINAL VERSION
	bool initDirFileHeaders_ver1(unsigned short nDirEntries); //FINAL VERSION

	bool initZipFileAsset(ZipFileAsset* pZipFileAsset, char* pLocalHeader); //FINAL VERSION previous initLocalHeader

	bool initDirFileHeaders_1version(unsigned short nDirEntries); //FIRST VERSION
	bool initLocalHeader_1version(char* pLocalHeader, unsigned short fnameLen,
			unsigned long cSize); //FIRST VERSION

	bool isZipFileHeaderCorrect(TZipDirFileHeader* pZipDirFileHeader, int i); //FINAL VERSION
	bool isZipLocalHeaderCorrect(TZipLocalHeader* pZipLocalHeader); //FINAL VERSION

	bool prepareOutputDir(const std::string folderName); //FINAL VERSION
	bool createFilesAndFolders(const std::string folderName); // FINAL VERSION
	bool createFolder(boost::filesystem::path newFolder); // FINAL VERSION
	bool copyFile(boost::filesystem::path inPath, ZipFileAsset* pZipFileAsset); // FINAL VERSION
	bool copyUnzipFile(boost::filesystem::path inPath,
			ZipFileAsset* pZipFileAsset); // FINAL VERSION
	bool copyZipFile(boost::filesystem::path inPath,
			ZipFileAsset* pZipFileAsset); // CANDIDATE FOR FINAL VERSION

//	bool saveAsset(boost::filesystem::ofstream& ofs,
//			const boost::filesystem::path resourceFilePath,
//			const std::string shortFileName,
//			std::list<TZipDirFileHeader*>& dirFileHeadersList,
//			const TZipDirHeader& dh, const std::string saveMode);

	bool saveAsset(boost::filesystem::ofstream& ofs,
			ZipFileAsset* pZipFileAsset,
			std::list<TZipDirFileHeader*>& dirFileHeadersList,
			const TZipDirHeader& dh, unsigned short outputSaveMode);

	bool saveAssetFileName(TZipLocalHeader& lh,
			boost::filesystem::ofstream& ofs, ZipFileAsset* zipFileAsset,
			unsigned short outputSaveMode);

	bool saveAssetFileName_ok(TZipLocalHeader& lh,
			boost::filesystem::ofstream& ofs, ZipFileAsset* zipFileAsset,
			unsigned short outputSaveMode);

	bool saveAssetFileContents(boost::filesystem::ofstream& ofs,
			ZipFileAsset* pZipFileAsset, unsigned short outputSaveMode,
			std::vector<char>& vecFileContents);

	bool saveAssetFileContents_old_ok(boost::filesystem::ofstream& ofs,
			ZipFileAsset* pZipFileAsset, unsigned short outputSaveMode,
			std::vector<char>& vecFileContents);

	std::string zipToUnzip(std::string zipString); // FINAL

private:

	//TZipDirHeader* m_pZipDirHeader_debug;
	//    TZipDirFileHeader;
	//   TZipLocalHeader;

	//      char *m_pDirData;	// Raw data buffer.

	std::vector<char> m_fileData; //FINAL VERSION
	TZipDirHeader* m_pZipDirHeader; //FINAL VERSION

	std::map<std::string, ZipFileAsset*> m_zipContentsMap; //FINAL VERSION
	//std::vector<ZipFileAsset> m_zipFileAssetVec;

	unsigned short isCompressed = 0;
};
}
#endif // ZIPFILE_H

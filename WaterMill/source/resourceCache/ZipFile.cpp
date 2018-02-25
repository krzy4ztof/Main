#include "ZipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"
#include "TZipDirFileHeader.h"
#include "TZipDirHeader.h"
#include "TZipLocalHeader.h"
#include "ZipFileAsset.h"
//#include "IResourceFile.h"
#include "../utilities/StringUtils.h"

#include <boost/iostreams/filter/zlib.hpp> // zlib_decompressor
#include <boost/iostreams/filter/gzip.hpp> // gzip_decompressor
#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/device/file.hpp> // boost::iostreams::file_source
#include <boost/iostreams/stream.hpp> // boost::iostreams::stream
#include <boost/iostreams/filtering_stream.hpp> // boost::iostreams::filtering_istream;
#include <boost/iostreams/device/array.hpp> // boost::iostreams::array_source, boost::iostreams::array_sink
#include <boost/filesystem/fstream.hpp>

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

#include <minizip/zip.h> //
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

//using namespace boost::iostreams;

using std::string;
using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;
//using std::ios::end;
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

//typedef unsigned long dword;
//typedef unsigned short word;
//typedef unsigned char byte;

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

	//m_fileData.clear();
	reset();

	ss << "POST CLEAR: file Data size " << m_fileData.size();

	logger::info(ss);

	m_zipContentsMap.clear();

	//m_fileData = nullptr;

	/*
	 logger::info("start zipdDirHeader");
	 m_pZipDirHeader->describeYourself();
	 m_fileData.clear();

	 vector<char> newVector;
	 m_fileData.swap(newVector);

	 logger::info("after clear and swap");
	 m_pZipDirHeader->describeYourself();
	 m_fileData.erase(m_fileData.begin(),
	 m_fileData.begin() + m_fileData.size());

	 logger::info("after erase");
	 m_pZipDirHeader->describeYourself();
	 */

	//delete (m_fileData);
	//templates::safe_delete_array<vector<char>>(m_fileData); // ok
	//logger::info("after sDeleteafe");
	//m_pZipDirHeader->describeYourself();
	/*
	 logger::info("debugger");
	 m_pZipDirHeader_debug->describeYourself();
	 templates::safe_delete<TZipDirHeader>(m_pZipDirHeader_debug); // ok
	 logger::info("after debug");
	 */

	//m_pZipDirHeader_debug->describeYourself();
	//m_pZipDirHeader_debug = nullptr;
	//logger::info("after nullptr");
	//m_pZipDirHeader_debug->describeYourself();
//	m_zipFileAssetVec.clear();
//templates::safe_delete_debug<TZipDirHeader>(m_pZipDirHeader); // error
	//templates::safe_delete_array<char>(m_pDirData); // error
	//#define SAFE_DELETE_ARRAY(x) if (x) delete [] x; x=NULL;
	/*
	 if (m_pDirData) {
	 delete[] m_pDirData;
	 m_pDirData = NULL;
	 };
	 */

}

void ZipFile::describeYourself() {
	stringstream ss;

	ss << "ZipFile DescribeYourself";
	logger::info(ss);

	unsigned short nEntries = this->getNumberOfEntries();

	ss << "Number of Entries: " << nEntries;
	logger::info(ss);

	TZipDirHeader* pZipDirHeader = getZipDirHeader();
	if (pZipDirHeader) {
		pZipDirHeader->describeYourself();
	}

	for (map<string, ZipFileAsset*>::iterator it = m_zipContentsMap.begin();
			it != m_zipContentsMap.end(); ++it) {
		it->second->describeYourself();
	}
}

bool ZipFile::temp_init_1(const string& resFileName) {

	stringstream memory_stream;

	stringstream ss;

	ss << "ZipFile::init: " << resFileName;
	logger::info(ss);

	//file_source myFile{resFileName};
	file_source myFile(resFileName); // typedef basic_file_source<char> file_source

	if (myFile.is_open()) {
		//			stream<file_source> fileSourceStream {myFile};
		stream<file_source> fileSourceStream(myFile);

		// size of fileSourceStream
		int fileSourceStreamSize = boost::iostreams::seek(fileSourceStream, 0,
				std::ios_base::end);
		boost::iostreams::seek(fileSourceStream, 0, std::ios_base::beg); // return to the beginning before invoking any other actions

		ss << "file size: " << fileSourceStreamSize;
		logger::info(ss);

		filtering_istreambuf in; //filtering_streambuf<input>
		//filtering_streambuf<file_source> in;

		//filtering_istream in;
		in.push(zlib_compressor());
		in.push(fileSourceStream);

		boost::iostreams::copy(in, memory_stream);

		cout << memory_stream.str();
		cout << " -- 0 -- memory_stream.str() cout" << endl;

		ss << memory_stream.str();
		//boost::iostreams::copy(memory_stream, ss);
		logger::info(ss);

		logger::info("--0--");
		cout << memory_stream.str();
		cout << " -- 1 -- memory_stream.str() cout" << endl;
		//boost::iostreams::copy(memory_stream, ss);

		ss << memory_stream.str();
		logger::info(ss);

		logger::info("--1--");

		// size of memory_stream
		memory_stream.seekg(0, ios::end);
		int size_memory_stream = memory_stream.tellg();

		ss << "size of memory_stream: " << size_memory_stream;
		logger::info(ss);

		//boost::iostreams::copy(memory_stream, ss);

		ss << memory_stream.str();
		logger::info(ss);

		logger::info("--2--");

		memory_stream.seekg(0, ios::beg); // we must return to the beginning of memory_stream before osbuf.push(memory_stream);

		filtering_istreambuf osbuf; //filtering_streambuf<output>
		osbuf.push(zlib_decompressor());
		osbuf.push(memory_stream);

		stringstream decompressed_memory;

		boost::iostreams::copy(osbuf, decompressed_memory);

		ss << decompressed_memory.str();
		logger::info(ss);

		// size of decompressed_memory
		decompressed_memory.seekg(0, ios::end);
		int size_decompressed_memory = decompressed_memory.tellg();
		decompressed_memory.seekg(0, ios::beg); // we must return to the beginning of decompressed_memory

		ss << "size of decompressed_memory: " << size_decompressed_memory;
		logger::info(ss);

		logger::info("--decompressed 3--");

		ss << decompressed_memory.str();
		logger::info(ss);

		logger::info("--decompressed 4--");
		ss << memory_stream.str();
		logger::info(ss);

		logger::info("--compressed 5--");

		myFile.close();
	}
	return true;
}

bool ZipFile::temp_init_2(const string& resFileName) {

	//char *m_pDirData;	// Raw data buffer.
	stringstream memory_stream;

	stringstream ss;

	ss << "ZipFile::init: " << resFileName;
	logger::info(ss);

	//file_source myFile{resFileName};
	file_source myFile(resFileName); // typedef basic_file_source<char> file_source

	if (myFile.is_open()) {
		//			stream<file_source> fileSourceStream {myFile};
		stream<file_source> fileSourceStream(myFile);

		int fileSourceStreamSize = boost::iostreams::seek(fileSourceStream, 0,
				std::ios_base::end);

		boost::iostreams::seek(fileSourceStream, 0, std::ios_base::beg); // return to the beginning before invoking any other actions

		ss << "file size: " << fileSourceStreamSize;
		logger::info(ss);

		filtering_istreambuf in; //filtering_streambuf<input>
		//filtering_streambuf<file_source> in;

		//filtering_istream in;
		in.push(zlib_compressor());
		in.push(fileSourceStream);

		boost::iostreams::copy(in, memory_stream);

		cout << memory_stream.str() << endl;
		cout << " -- 0 --  cout" << endl;

		ss << memory_stream.str();
		//boost::iostreams::copy(memory_stream, ss);
		logger::info(ss);

		logger::info("--0--");

		//boost::iostreams::copy(memory_stream, ss);

		ss << memory_stream.str();
		logger::info(ss);

		logger::info("--1--");

		cout << memory_stream.str() << endl;
		cout << "---cout---1---" << endl;

		// size of memory_stream
		memory_stream.seekg(0, ios::end);
		int size_memory_stream = memory_stream.tellg();

		ss << "size of memory_stream: " << size_memory_stream;
		logger::info(ss);

		ss << "size of memory_stream.str().length: "
				<< memory_stream.str().length();
		logger::info(ss);

		char* m_pDirData2 = new char[size_memory_stream + 1]; // 3+1

		ss << "size of m_pDirData: "
				<< sizeof(m_pDirData2) / sizeof(m_pDirData2[0]);

		logger::info(ss);

		ss << "strlen of m_pDirData: " << strlen(m_pDirData2);

		logger::info(ss);

		//			std::fill(m_pDirData, m_pDirData+sizeof(m_pDirData));

		for (int i = 0; i < size_memory_stream; i++) { // <3 [0,1,2]
			m_pDirData2[i] = '0' + i % 10;
		}
		m_pDirData2[size_memory_stream] = '\0'; //[3]

		string dirDataIntoStr(m_pDirData2);

		ss << "dirDataIntoStr init: " << dirDataIntoStr;
		logger::info(ss);

		strcpy(m_pDirData2, memory_stream.str().c_str());
		m_pDirData2[size_memory_stream] = '\0'; //[3] add the proper ending

		ss << "dirDataIntoStr length: " << dirDataIntoStr.length();
		logger::info(ss);

		string dirDataIntoStr2(m_pDirData2);

		ss << "dirDataIntoStr2 compressed: " << dirDataIntoStr2;
		logger::info(ss);

		ss << "dirDataIntoStr2 length: " << dirDataIntoStr2.length();
		logger::info(ss);

		//boost::iostreams::copy(memory_stream, ss);

		ss << memory_stream.str();
		logger::info(ss);

		logger::info("--2--");

		cout << memory_stream.str() << endl;
		cout << "---cout---2---" << endl;

		memory_stream.seekg(0, ios::beg); // we must return to the beginning of memory_stream before osbuf.push(memory_stream);

		filtering_istreambuf osbuf; //filtering_streambuf<output>
		osbuf.push(zlib_decompressor());
		osbuf.push(memory_stream);

		stringstream decompressed_memory;

		boost::iostreams::copy(osbuf, decompressed_memory);

		ss << decompressed_memory.str();
		logger::info(ss);

		logger::info("--decompressed 3--");

		// size of decompressed_memory
		decompressed_memory.seekg(0, ios::end);
		int size_decompressed_memory = decompressed_memory.tellg();
		decompressed_memory.seekg(0, ios::beg); // we must return to the beginning of decompressed_memory

		ss << "size of decompressed_memory: " << size_decompressed_memory;
		logger::info(ss);

		ss << "size of decompressed_memory.str().length: "
				<< decompressed_memory.str().length();
		logger::info(ss);

		// //

		char *m_pDirDataDec = new char[size_decompressed_memory + 1]; // 3+1

		ss << "size of m_pDirDataDec: "
				<< sizeof(m_pDirDataDec) / sizeof(m_pDirDataDec[0]);
		logger::info(ss);

		ss << "strlen of m_pDirDataDec: " << strlen(m_pDirDataDec);

		logger::info(ss);

		for (int i = 0; i < size_decompressed_memory; i++) { // <3  [0,1,2]
			m_pDirDataDec[i] = '0' + i % 10;
		}
		m_pDirDataDec[size_decompressed_memory] = '\0'; //[3]

		string dirDataIntoStrDec(m_pDirDataDec);

		ss << "dirDataIntoStrDec init: " << dirDataIntoStrDec;
		logger::info(ss);

		strcpy(m_pDirDataDec, decompressed_memory.str().c_str());
		m_pDirDataDec[size_decompressed_memory] = '\0'; //[3] add the proper ending

		ss << "dirDataIntoStrDec length: " << dirDataIntoStrDec.length();
		logger::info(ss);

		string dirDataIntoStrDec2(m_pDirDataDec);

		ss << "dirDataIntoStrDec2 decompressed: " << dirDataIntoStrDec2;
		logger::info(ss);

		// //
		ss << "dirDataIntoStrDec2 length: " << dirDataIntoStrDec2.length();
		logger::info(ss);

		ss << decompressed_memory.str();
		logger::info(ss);

		logger::info("--decompressed 4--");

		cout << decompressed_memory.str() << endl;
		cout << "---dec---cout---4---" << endl;

		ss << memory_stream.str();
		logger::info(ss);

		logger::info("--compressed 5--");

		cout << memory_stream.str() << endl;
		cout << "---cout---5---" << endl;

		templates::safe_delete_array<char>(m_pDirDataDec);

		myFile.close();
	}

	//templates::safe_delete_array<char> (m_pDirData);

	return true;
}

bool ZipFile::init_333(const string& resFileName) {

	//stringstream memory_stream;

	stringstream ss;

	ss << "ZipFile::init: " << resFileName;
	logger::info(ss);

	//file_source myFile{resFileName};
	file_source myFile(resFileName); // typedef basic_file_source<char> file_source

	if (myFile.is_open()) {
		//			stream<file_source> fileSourceStream {myFile};
		stream<file_source> fileSourceStream(myFile);

		vector<char> vecChar;
		//back_insert_device<vector<char>> snk{vecChar};

		filtering_istreambuf in; //filtering_streambuf<input>

		in.push(zlib_compressor());
		in.push(fileSourceStream);

		boost::iostreams::copy(in, boost::iostreams::back_inserter(vecChar));

		ss << "Start compressed: ";

		for (vector<char>::iterator it = vecChar.begin(); it != vecChar.end();
				++it) {
			//cout << *it;
			ss << *it;
		}
		cout << endl;

		logger::info(ss);

		logger::info("-------------");

		array_source src { vecChar.data(), vecChar.size() };
		filtering_istreambuf inDec; //filtering_streambuf<input>

		inDec.push(zlib_decompressor());
		inDec.push(src);

		vector<char> vecCharDec;

		boost::iostreams::copy(inDec,
				boost::iostreams::back_inserter(vecCharDec));

		ss << "Start decompressed: ";

		for (vector<char>::iterator it = vecCharDec.begin();
				it != vecCharDec.end(); ++it) {
			//cout << *it;
			ss << *it;
		}
		cout << endl;

		logger::info(ss);
		//boost::iostreams::copy(in, vecChar);

		myFile.close();
	}

	//templates::safe_delete_array<char>(m_pDirData);

	return true;
}

// --------------------------------------------------------------------------
// Function:      initCompressed
// Purpose:       loads file that has compression saves data into vector<char> data
// Parameters:
// --------------------------------------------------------------------------

/*
 bool ZipFile::initCompressed(const std::string& resFileName) {

 return false;
 }
 */

bool ZipFile::initCompressed_fails(const std::string& resFileName) {
	stringstream ss;

	ss << "ZipFile::initCompressed: " << resFileName;
	logger::info(ss);

	TZipDirHeader dh;

	TZipDirFileHeader dfh;

	TZipLocalHeader lh;

	filtering_istreambuf inDec;
	//inDec.push(zlib_decompressor());
	inDec.push(boost::iostreams::gzip_decompressor());

	ifstream ifs(resFileName, ios::binary);
	if (ifs.is_open()) {

		inDec.push(ifs);

		vector<char> vecCharDec;
		boost::iostreams::copy(inDec,
				boost::iostreams::back_inserter(vecCharDec));

		ss << "sizeof::TZipDirFileHeader: " << sizeof(TZipDirFileHeader);
		logger::info(ss);

		TZipDirFileHeader* pfh =
				reinterpret_cast<TZipDirFileHeader*>(vecCharDec.data());

		pfh->describeYourself();

		/*
		 ifstream ifs(resFileName, ios::binary);

		 ifs.read(reinterpret_cast<char *>(&dfh), sizeof(dh));

		 ifs.read(reinterpret_cast<char *>(&dfh), sizeof(dfh));

		 ss << "CHECK FH: ";
		 logger::info(ss);
		 ss << dfh;
		 logger::info(ss);

		 ss << "END CHECK FH";
		 logger::info(ss);
		 */
		ifs.close();
	} else {
		logger::info("NIE otwarte!!!!");
	}
	return true;
}
;

void ZipFile::reset() {
	m_fileData.clear();

	m_pZipDirHeader = nullptr;

}

bool ZipFile::initLocalHeader_1version(char* pAsset, unsigned short fNameLen,
		unsigned long cSize) {
	stringstream ss;

	ss << "PRE pASSET address: " << (void *) pAsset;
	logger::info(ss);

	TZipLocalHeader* pZipLocalHeader =
			reinterpret_cast<TZipLocalHeader*>(pAsset);

	if (pZipLocalHeader->sig != TZipLocalHeader::SIGNATURE) {
		ss << "Wrong TZipLocalHeader signature: " << std::hex
				<< pZipLocalHeader->sig;
		; //<< std::dec;
		logger::warning(ss);

		return false;
	} else {
		ss << "Correct TZipLocalHeader signature " << std::hex
				<< pZipLocalHeader->sig;
		logger::info(ss);
	}

	pAsset += sizeof(TZipLocalHeader);

	/*
	 char* pFileName = new char[fNameLen];
	 memcpy(pFileName, pAsset, fNameLen);
	 ss << "FILE NAME: ";
	 for (int i = 0; i < fNameLen; i++) {
	 ss << pFileName[i];
	 }
	 logger::info(ss);
	 pAsset += fNameLen;
	 */

	string vecFileName = "";
	char* pFileName = pAsset;
	for (int i = 0; i < fNameLen; i++) {
		vecFileName.push_back(*pFileName);
		pFileName++;
	}

	ss << "VEC FILE NAME: " << vecFileName;
	logger::info(ss);

	pAsset += fNameLen;

	/*
	 char* pFileContents = new char[cSize];
	 memcpy(pFileContents, pAsset, cSize);
	 */

	char* m_pFileContents = pAsset;

	char* pFileContents = m_pFileContents;

	ss << "START FILE CONTENTS: ";
	logger::info(ss);
	for (int i = 0; i < cSize; i++) {
		ss << pFileContents[i];
	}

	logger::info(ss);
	ss << "END FILE CONTENTS: ";
	logger::info(ss);

	/*
	 ss << "FILE CONTENTS: ";
	 logger::info(ss);
	 for (int i = 0; i < cSize; i++) {
	 ss << pFileContents[i];
	 }
	 logger::info(ss);
	 */

	pAsset += cSize;

	ss << "POST pASSET address: " << (void *) pAsset;
	logger::info(ss);

	return true;
}

bool ZipFile::isZipLocalHeaderCorrect(TZipLocalHeader* pZipLocalHeader) {
	stringstream ss;
	if (pZipLocalHeader->sig != TZipLocalHeader::SIGNATURE) {
		ss << "Wrong TZipLocalHeader signature: " << std::hex
				<< pZipLocalHeader->sig;
		; //<< std::dec;
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

	pZipFileAsset->m_pZipLocalHeader =
			reinterpret_cast<TZipLocalHeader*>(pAsset);

	if (!isZipLocalHeaderCorrect(pZipFileAsset->m_pZipLocalHeader)) {
		return false;
	}

	pAsset += sizeof(TZipLocalHeader);

	/*
	 char* pFileName = new char[fNameLen];
	 memcpy(pFileName, pAsset, fNameLen);
	 ss << "FILE NAME: ";
	 for (int i = 0; i < fNameLen; i++) {
	 ss << pFileName[i];
	 }
	 logger::info(ss);
	 pAsset += fNameLen;
	 */

	//string vecFileName = "";
	char* pFileName = pAsset;
	for (int i = 0; i < pZipFileAsset->getFileNameLength(); i++) {
		pZipFileAsset->fileName.push_back(*pFileName);
		pFileName++;
	}

	ss << "VEC FILE NAME: " << pZipFileAsset->fileName;
	logger::info(ss);

	pAsset += pZipFileAsset->getFileNameLength();

	/*
	 char* pFileContents = new char[cSize];
	 memcpy(pFileContents, pAsset, cSize);
	 */

	char* m_pFileContents = pAsset;

	char* pFileContents = m_pFileContents;
	pZipFileAsset->m_pDirData = pAsset;

	/*
	 ss << "START FILE CONTENTS: ";
	 logger::info(ss);
	 for (int i = 0; i < pZipFileAsset->getFileDataSize(); i++) {
	 ss << pFileContents[i];
	 }

	 logger::info(ss);
	 ss << "END FILE CONTENTS: ";
	 logger::info(ss);
	 */

	/*
	 ss << "FILE CONTENTS: ";
	 logger::info(ss);
	 for (int i = 0; i < cSize; i++) {
	 ss << pFileContents[i];
	 }
	 logger::info(ss);
	 */

	pAsset += pZipFileAsset->getFileDataSize();

	ss << "POST pASSET address: " << (void *) pAsset;
	logger::info(ss);

	this->m_zipContentsMap[pZipFileAsset->fileName] = pZipFileAsset;

	return true;
}

bool ZipFile::initDirFileHeaders_1version(unsigned short nDirEntries) {
	stringstream ss;

	char* pDirFileHeaderData = m_fileData.data();

	int offsetDirHeaders = sizeof(TZipDirHeader)
			+ nDirEntries * sizeof(TZipDirFileHeader);

	pDirFileHeaderData += m_fileData.size() - offsetDirHeaders;

	//int offsetLocalHeader = 0;
	char* pLocalHeaderData = m_fileData.data();
	//pLocalHeaderData -= m_fileData.size();

	int totalOffset = 0;

	for (int i = 0; i < nDirEntries; i++) {

		ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
				<< (void *) pLocalHeaderData;
		logger::info(ss);

		TZipDirFileHeader* pZipDirFileHeader =
				reinterpret_cast<TZipDirFileHeader*>(pDirFileHeaderData);

		//pZipDirFileHeader->describeYourself();

		if (pZipDirFileHeader->sig != TZipDirFileHeader::SIGNATURE) {
			ss << "Wrong TZipDirFileHeader[" << i << "] signature: " << std::hex
					<< pZipDirFileHeader->sig;
			; //<< std::dec;
			logger::warning(ss);

			return false;
		} else {
			ss << "Correct TZipDirFileHeader[" << i << "] signature "
					<< std::hex << pZipDirFileHeader->sig;
			logger::info(ss);

			int offsetFile = sizeof(TZipLocalHeader)
					+ pZipDirFileHeader->fnameLen + pZipDirFileHeader->cSize;

			ss << "LOCAL HEADER Start: " << std::hex << totalOffset;
			logger::info(ss);
			ss << "LOCAL HEADER length: " << std::dec
					<< sizeof(TZipLocalHeader);
			logger::info(ss);

			logger::info(ss);
			ss << "FNAME Start: " << std::hex
					<< totalOffset + sizeof(TZipLocalHeader);
			logger::info(ss);

			ss << "FNAME fnameLen: " << std::dec << pZipDirFileHeader->fnameLen;
			logger::info(ss);
			ss << "FILE CONTENTS Start: " << std::hex
					<< totalOffset + sizeof(TZipLocalHeader)
							+ pZipDirFileHeader->fnameLen;
			logger::info(ss);
			ss << "CSIZE cSize: " << std::dec << pZipDirFileHeader->cSize;
			logger::info(ss);
			ss << "FILE CONTENTS End: " << std::hex
					<< totalOffset + offsetFile - 1;
			logger::info(ss);

/////////////////
			/*
			 TZipLocalHeader* pZipLocalHeader =
			 reinterpret_cast<TZipLocalHeader*>(pLocalHeaderData);


			 if (pZipLocalHeader->sig != TZipLocalHeader::SIGNATURE) {
			 ss << "Wrong TZipLocalHeader!!! signature: " << std::hex
			 << pZipLocalHeader->sig;
			 ; //<< std::dec;
			 logger::warning(ss);

			 } else {
			 ss << "Correct TZipLocalHeader!!! signature " << std::hex
			 << pZipLocalHeader->sig;
			 logger::info(ss);
			 }
			 */

			////////////////////
			//pDirFileHeaderData -= offsetLocalHeader;
			ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
					<< (void *) pLocalHeaderData;
			logger::info(ss);
			bool result = initLocalHeader_1version(pLocalHeaderData,
					pZipDirFileHeader->fnameLen, pZipDirFileHeader->cSize);

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

	}
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

	//int offsetLocalHeader = 0;
	char* pLocalHeaderData = m_fileData.data();
	//pLocalHeaderData -= m_fileData.size();

	int totalOffset = 0;

	for (int i = 0; i < nDirEntries; i++) {

		ZipFileAsset* zipFileAsset = new ZipFileAsset();

		ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
				<< (void *) pLocalHeaderData;
		logger::info(ss);

		//TZipDirFileHeader* pZipDirFileHeader =
		//		reinterpret_cast<TZipDirFileHeader*>(pDirFileHeaderData);

		zipFileAsset->m_pZipDirFileHeader =
				reinterpret_cast<TZipDirFileHeader*>(pDirFileHeaderData);

		//pZipDirFileHeader->describeYourself();

		if (!isZipFileHeaderCorrect(zipFileAsset->m_pZipDirFileHeader, i)) {
			return false;
		};

		int offsetFile = sizeof(TZipLocalHeader)
				+ zipFileAsset->m_pZipDirFileHeader->fnameLen
				+ zipFileAsset->m_pZipDirFileHeader->cSize;

		/*
		 ss << "LOCAL HEADER Start: " << std::hex << totalOffset;
		 logger::info(ss);
		 ss << "LOCAL HEADER length: " << std::dec
		 << sizeof(TZipLocalHeader);
		 logger::info(ss);

		 logger::info(ss);
		 ss << "FNAME Start: " << std::hex
		 << totalOffset + sizeof(TZipLocalHeader);
		 logger::info(ss);

		 ss << "FNAME fnameLen: " << std::dec
		 << zipFileAsset->m_pZipDirFileHeader->fnameLen;
		 logger::info(ss);
		 ss << "FILE CONTENTS Start: " << std::hex
		 << totalOffset + sizeof(TZipLocalHeader)
		 + zipFileAsset->m_pZipDirFileHeader->fnameLen;
		 logger::info(ss);
		 ss << "CSIZE cSize: " << std::dec
		 << zipFileAsset->m_pZipDirFileHeader->cSize;
		 logger::info(ss);
		 ss << "FILE CONTENTS End: " << std::hex << totalOffset + offsetFile - 1;
		 logger::info(ss);

		 ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
		 << (void *) pLocalHeaderData;
		 logger::info(ss);
		 */

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

bool ZipFile::initDirFileHeaders_ver1(unsigned short nDirEntries) {
	stringstream ss;

	char* pDirFileHeaderData = m_fileData.data();

	int offsetDirHeaders = sizeof(TZipDirHeader)
			+ nDirEntries * sizeof(TZipDirFileHeader);

	pDirFileHeaderData += m_fileData.size() - offsetDirHeaders;

	//int offsetLocalHeader = 0;
	char* pLocalHeaderData = m_fileData.data();
	//pLocalHeaderData -= m_fileData.size();

	int totalOffset = 0;

	for (int i = 0; i < nDirEntries; i++) {

		ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
				<< (void *) pLocalHeaderData;
		logger::info(ss);

		TZipDirFileHeader* pZipDirFileHeader =
				reinterpret_cast<TZipDirFileHeader*>(pDirFileHeaderData);

		//pZipDirFileHeader->describeYourself();

		if (pZipDirFileHeader->sig != TZipDirFileHeader::SIGNATURE) {
			ss << "Wrong TZipDirFileHeader[" << i << "] signature: " << std::hex
					<< pZipDirFileHeader->sig;
			; //<< std::dec;
			logger::warning(ss);

			return false;
		} else {
			ss << "Correct TZipDirFileHeader[" << i << "] signature "
					<< std::hex << pZipDirFileHeader->sig;
			logger::info(ss);

			int offsetFile = sizeof(TZipLocalHeader)
					+ pZipDirFileHeader->fnameLen + pZipDirFileHeader->cSize;

			ss << "LOCAL HEADER Start: " << std::hex << totalOffset;
			logger::info(ss);
			ss << "LOCAL HEADER length: " << std::dec
					<< sizeof(TZipLocalHeader);
			logger::info(ss);

			logger::info(ss);
			ss << "FNAME Start: " << std::hex
					<< totalOffset + sizeof(TZipLocalHeader);
			logger::info(ss);

			ss << "FNAME fnameLen: " << std::dec << pZipDirFileHeader->fnameLen;
			logger::info(ss);
			ss << "FILE CONTENTS Start: " << std::hex
					<< totalOffset + sizeof(TZipLocalHeader)
							+ pZipDirFileHeader->fnameLen;
			logger::info(ss);
			ss << "CSIZE cSize: " << std::dec << pZipDirFileHeader->cSize;
			logger::info(ss);
			ss << "FILE CONTENTS End: " << std::hex
					<< totalOffset + offsetFile - 1;
			logger::info(ss);

			ss << "PRE INIT LOCAL HEADER pLocalHeaderData address: "
					<< (void *) pLocalHeaderData;
			logger::info(ss);
			bool result = initLocalHeader_1version(pLocalHeaderData,
					pZipDirFileHeader->fnameLen, pZipDirFileHeader->cSize);

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

	//m_pZipDirHeader_debug = new TZipDirHeader();
	//m_pZipDirHeader_debug->testInitiation();

	//templates::safe_delete_array<vector<char>>(m_fileData);

	if (assetFile.is_open()) {
		ss << "OPEN OPEN OPEN " << filePath.string();
		logger::info(ss);

		filtering_istreambuf filterIn;
		filterIn.push(assetFile);

		//m_fileData = nullptr; //vector<char>();

		//vector<char> fileDataVec;
		boost::iostreams::copy(filterIn,
				boost::iostreams::back_inserter(m_fileData));

		bool result = initZipDirHeader();
		if (result == true) {
			TZipDirHeader* pZipDirHeader = getZipDirHeader();

			result = initDirFileHeaders(pZipDirHeader->nDirEntries);

		}

		//m_fileData = new vector<char>(fileDataVec.begin(), fileDataVec.end());
//		memcpy(m_fileData, fileDataVec, fileDataVec.size());

		/*
		 * OK
		 m_pDirData = new char[m_fileData.size()];
		 memcpy(m_pDirData, m_fileData.data(), m_fileData.size());
		 */

		//char* pDirData = m_fileData.data();
		//char* pDirData2 = new char[12];
		/*
		 pDirData += m_fileData.size() - sizeof(TZipDirHeader);



		 m_pZipDirHeader = reinterpret_cast<TZipDirHeader*>(pDirData);

		 m_pZipDirHeader->describeYourself();
		 */

		assetFile.close();
		if (result == false) {
			reset();

			return false;
		} else {
			return true;

		}

		//assetFile.close();

		/*
		 logger::info("pre safe delete pDirData2");

		 templates::safe_delete_array<char>(pDirData2);

		 logger::info("post safe delete pDirData2");
		 */

	} else {
		ss << "CLOSED " << filePath.string();
		logger::warning(ss);
		return false;
	}

}

bool ZipFile::initNotCompressed_ok_old(const std::string& resFileName) {

	reset();
	isCompressed = ZipFile::NOT_COMPRESSED;

	stringstream ss;

	path filePath { resFileName };

	boost::filesystem::ifstream assetFile(filePath, std::ios::binary);

	//m_pZipDirHeader_debug = new TZipDirHeader();
	//m_pZipDirHeader_debug->testInitiation();

	//templates::safe_delete_array<vector<char>>(m_fileData);

	if (assetFile.is_open()) {
		ss << "OPEN OPEN OPEN " << filePath.string();
		logger::info(ss);

		filtering_istreambuf filterIn;
		filterIn.push(assetFile);

		//m_fileData = nullptr; //vector<char>();

		//vector<char> fileDataVec;
		boost::iostreams::copy(filterIn,
				boost::iostreams::back_inserter(m_fileData));

		bool result = initZipDirHeader();
		if (result == true) {
			TZipDirHeader* pZipDirHeader = getZipDirHeader();

			result = initDirFileHeaders(pZipDirHeader->nDirEntries);

		}

		//m_fileData = new vector<char>(fileDataVec.begin(), fileDataVec.end());
//		memcpy(m_fileData, fileDataVec, fileDataVec.size());

		/*
		 * OK
		 m_pDirData = new char[m_fileData.size()];
		 memcpy(m_pDirData, m_fileData.data(), m_fileData.size());
		 */

		//char* pDirData = m_fileData.data();
		//char* pDirData2 = new char[12];
		/*
		 pDirData += m_fileData.size() - sizeof(TZipDirHeader);



		 m_pZipDirHeader = reinterpret_cast<TZipDirHeader*>(pDirData);

		 m_pZipDirHeader->describeYourself();
		 */

		assetFile.close();
		if (result == false) {
			reset();

			return false;
		} else {
			return true;

		}

		//assetFile.close();

		/*
		 logger::info("pre safe delete pDirData2");

		 templates::safe_delete_array<char>(pDirData2);

		 logger::info("post safe delete pDirData2");
		 */

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

// --------------------------------------------------------------------------
// Function:      initNotCompressed
// Purpose:       loads file that has no compression and compress its data into vector<char> data
// Parameters:
// --------------------------------------------------------------------------
bool ZipFile::initNotCompressed_222(const std::string& resFileName) {

	//stringstream memory_stream;
	stringstream ss;

	ss << "ZipFile::init: " << resFileName;
	logger::info(ss);

	//file_source myFile{resFileName};
	file_source myFile(resFileName); // typedef basic_file_source<char> file_source

	if (myFile.is_open()) {
		//			stream<file_source> fileSourceStream {myFile};
		stream<file_source> fileSourceStream(myFile);

		//	vector<char> vecChar;
		//back_insert_device<vector<char>> snk{vecChar};

		filtering_istreambuf in; //filtering_streambuf<input>

		in.push(zlib_compressor()); // contains a chain of zero or more Filters
		in.push(fileSourceStream); // with an optional Device at the end.

		// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/functions/copy.html#description
		// copy( [const] Source& src, [const] Sink& sink,
		//          std::streamsize buffer_size = default value );
		// where:
		//  device - specialization source, sink
		// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/classes/device.html#reference
		//
		// http://www.boost.org/doc/libs/1_63_0/boost/iostreams/concepts.hpp
		// typedef device<input>    source;
		// typedef device<output>   sink;
		//
		// Source:
		// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/concepts/source.html
		//  Models
		//      Standard input streams and stream buffers.
		//      array_source, file_source, file_descriptor_source, mapped_file_source.
		//  So: stream<file_source> fileSourceStream - is a Source Device
		//
		// Filtering_istreambuf:
		// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/classes/filtering_streambuf.html
		// Each filtering_streambuf contains a chain of zero or more Filters with an optional Device at the end.
		//
		// http://www.boost.org/doc/libs/1_63_0/boost/iostreams/filtering_streambuf.hpp
		// typedef filtering_streambuf<input>    filtering_istreambuf;
		//
		boost::iostreams::copy(in, boost::iostreams::back_inserter(m_fileData));

		// http://www.boost.org/doc/libs/1_63_0/libs/iostreams/doc/classes/zlib.html
		// Examples
		/*
		 #include <fstream>
		 #include <iostream>
		 #include <boost/iostreams/filtering_streambuf.hpp>
		 #include <boost/iostreams/copy.hpp>
		 #include <boost/iostreams/filter/zlib.hpp>

		 int main()
		 {
		 using namespace std;

		 ifstream file("hello.z", ios_base::in | ios_base::binary);
		 filtering_streambuf<input> in;
		 in.push(zlib_decompressor());
		 in.push(file);
		 boost::iostreams::copy(in, cout);
		 }
		 */

		ss << "Start compressed: ";

		for (vector<char>::iterator it = m_fileData.begin();
				it != m_fileData.end(); ++it) {
			//cout << *it;
			ss << *it;
		}
		cout << endl;

		logger::info(ss);

		logger::info("-------------");

		myFile.close();
	}

	//templates::safe_delete_array<char>(m_pDirData);

	return true;
}

// --------------------------------------------------------------------------
// Function:      test_initNotCompressedDirFileHeader
// Purpose:       read file that contains only uncompressed TZipDirFileHeader fh
//                  display fh at screen
//                File was save using test_saveNotCompressedDirFileHeader
// Parameters:
// --------------------------------------------------------------------------

bool ZipFile::test_initNotCompressedDirFileHeader(
		const std::string& resFileName) {

	//stringstream memory_stream;
	stringstream ss;

	ss << "ZipFile::test_initNotCompressedDirFileHeader: " << resFileName;
	logger::info(ss);

	/////////////////////////

	TZipDirFileHeader fh;

	ifstream ifs(resFileName, ios::binary);
	ifs.read(reinterpret_cast<char *>(&fh), sizeof(fh));

	//ss << "CHECK FH: ";
	//logger::info(ss);
	//ss << fh;
	//logger::info(ss);

	//ss << "END CHECK FH";
	//logger::info(ss);

	return true;
}

// --------------------------------------------------------------------------
// Function:      test_initCompressedDirFileHeader
// Purpose:       read file that contains only uncompressed TZipDirFileHeader fh
//                  display fh at screen
//                File was save using test_saveCompressedDirFileHeader
// Parameters:
// --------------------------------------------------------------------------

bool ZipFile::test_initCompressedDirFileHeader(const std::string& resFileName) {

	//stringstream memory_stream;
	stringstream ss;

	ss << "ZipFile::test_initCompressedDirFileHeader: " << resFileName;
	logger::info(ss);

	/////////////////////////

	TZipDirFileHeader fh;

	filtering_istreambuf inDec;
	inDec.push(zlib_decompressor());

	ifstream ifs(resFileName, ios::binary);

	inDec.push(ifs);

	vector<char> vecCharDec;
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	for (std::vector<char>::iterator it = vecCharDec.begin();
			it != vecCharDec.end(); ++it) {
		ss << ' ' << *it;
		logger::info(ss);
	}

	// ERROR
	//TZipDirFileHeader* pfh =
	//		reinterpret_cast<TZipDirFileHeader*>(vecCharDec.data(), vecCharDec.size());

	TZipDirFileHeader* pfh =
			reinterpret_cast<TZipDirFileHeader*>(vecCharDec.data());

// OK
//	char* pData = vecCharDec.data();
//	TZipDirFileHeader* pfh = reinterpret_cast<TZipDirFileHeader*>(pData);

	pfh->describeYourself();

	/*
	 ss << "myTZipDirFileHeader contains:";
	 logger::info(ss);
	 ss << *pfh;
	 logger::info(ss);
	 */

	/*
	 TZipDirFileHeader pfh =
	 reinterpret_cast<TZipDirFileHeader>(vecCharDec);

	 ss << "myTZipDirFileHeader contains:";
	 logger::info(ss);
	 ss << pfh;
	 logger::info(ss);
	 */

	/*
	 TZipDirFileHeader* pfh =
	 reinterpret_cast<TZipDirFileHeader*>(vecCharDec.data(), vecCharDec.size());

	 fh = *pfh;

	 ss << "myTZipDirFileHeader contains:";
	 logger::info(ss);
	 ss << fh;
	 logger::info(ss);
	 */

	/*
	 * OK
	 vector<char> vecCharDec;
	 boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	 ss << "myvector contains:";
	 logger::info(ss);

	 for (std::vector<char>::iterator it = vecCharDec.begin();
	 it != vecCharDec.end(); ++it) {
	 ss << ' ' << *it;
	 logger::info(ss);
	 }
	 */

	/*
	 ifs.read(reinterpret_cast<char *>(&fh), sizeof(fh));

	 ss << "CHECK FH: ";
	 logger::info(ss);
	 ss << fh;
	 logger::info(ss);

	 ss << "END CHECK FH";
	 logger::info(ss);
	 */

	return true;
}

bool ZipFile::test_initCompressedDirFileHeaderIntoVectorChar(
		const std::string& resFileName) {

	//stringstream memory_stream;
	stringstream ss;

	ss << "ZipFile::test_initCompressedDirFileHeader: " << resFileName;
	logger::info(ss);

	/////////////////////////

	TZipDirFileHeader fh;

	filtering_istreambuf inDec;
	inDec.push(zlib_decompressor());

	ifstream ifs(resFileName, ios::binary);
	inDec.push(ifs);

	vector<char> vecCharDec;
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));
	ss << "myvector contains:";
	logger::info(ss);

	for (std::vector<char>::iterator it = vecCharDec.begin();
			it != vecCharDec.end(); ++it) {
		ss << ' ' << *it;
		logger::info(ss);
	}

	return true;
}

bool ZipFile::saveAssetFileName(TZipLocalHeader& lh, ofstream& ofs,
		ZipFileAsset* zipFileAsset, unsigned short outputSaveMode) {

	const string shortFileName = zipFileAsset->fileName;

	stringstream ss;

	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves not compressed file name: " << shortFileName
					<< " as not compressed";
			logger::info(ss);

			// lh.fnameLen = shortFileName.length();
			lh.fnameLen = zipFileAsset->getFileNameLength();

			ss << "shortFileName.length(): " << shortFileName.length()
					<< " /// zipFileAsset->getFileNameLength(): "
					<< zipFileAsset->getFileNameLength();
			logger::info(ss);

			//local header
			ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

			lh.describeYourself();

/// START

			filtering_istreambuf filterFileName;
			//filterFileName.push(zlib_compressor());

			/*
			 char* fileNameChar = string_utils::stringToChar(shortFileName);
			 array_source source(fileNameChar,
			 zipFileAsset->getFileNameLength());
			 */

			array_source source(shortFileName.c_str(),
					zipFileAsset->getFileNameLength());
			filterFileName.push(source);

			vector<char> vecFileName;
			boost::iostreams::copy(filterFileName,
					boost::iostreams::back_inserter(vecFileName));

			//file name
			ofs.write(reinterpret_cast<char *>(vecFileName.data()),
					vecFileName.size());

			/// END
			/// REPLACED START
			//ofs.write(shortFileName.c_str(), zipFileAsset->getFileNameLength());

/// REPLACED END

		} else {
			ss << "Saves not compressed file name: " << shortFileName
					<< " as compressed";
			logger::info(ss);

			// lh.fnameLen = shortFileName.length();
			//	lh.fnameLen = zipFileAsset->getFileNameLength();

			ss << "shortFileName.length(): " << shortFileName.length()
					<< " /// zipFileAsset->getFileNameLength(): "
					<< zipFileAsset->getFileNameLength();
			logger::info(ss);

			//local header

			//file name
			//	ofs.write(shortFileName.c_str(), shortFileName.length());

			filtering_istreambuf filterFileName;
			filterFileName.push(zlib_compressor());

			//char* fileNameChar = string_utils::stringToChar(shortFileName);
			//array_source source(fileNameChar,
			//		zipFileAsset->getFileNameLength());

			array_source source(shortFileName.c_str(),
					zipFileAsset->getFileNameLength());
			filterFileName.push(source);

			vector<char> vecFileName;
			boost::iostreams::copy(filterFileName,
					boost::iostreams::back_inserter(vecFileName));

			//lh.fnameLen = zipFileAsset->getFileNameLength();
			lh.fnameLen = vecFileName.size();
			ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

			lh.describeYourself();

			//file name
			ofs.write(reinterpret_cast<char *>(vecFileName.data()),
					vecFileName.size());

			/*
			 ofs.write(shortFileName.c_str(), zipFileAsset->getFileNameLength());

			 /////////////////////

			 filtering_istreambuf filterFileName;
			 filterFileName.push(zlib_compressor());

			 stringstream fileNameStream;
			 fileNameStream << shortFileName;
			 filterFileName.push(fileNameStream);

			 vector<char> vecFileName;
			 boost::iostreams::copy(filterFileName,
			 boost::iostreams::back_inserter(vecFileName));

			 lh.fnameLen = vecFileName.size();

			 // Local Header
			 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));
			 */

		}
	} else {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves compressed file name: " << shortFileName
					<< " as not compressed";
			logger::info(ss);

			filtering_istreambuf filterFileName;
			filterFileName.push(zlib_decompressor());

			array_source source(shortFileName.c_str(),
					zipFileAsset->getFileNameLength());
			filterFileName.push(source);

			vector<char> vecFileName;
			boost::iostreams::copy(filterFileName,
					boost::iostreams::back_inserter(vecFileName));

			//lh.fnameLen = zipFileAsset->getFileNameLength();
			lh.fnameLen = vecFileName.size();
			ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

			lh.describeYourself();

			//file name
			ofs.write(reinterpret_cast<char *>(vecFileName.data()),
					vecFileName.size());
		} else {
			ss << "Saves compressed file name: " << shortFileName
					<< " as compressed";
			logger::info(ss);

			// lh.fnameLen = shortFileName.length();
			lh.fnameLen = zipFileAsset->getFileNameLength();
			ss << "shortFileName.length(): " << shortFileName.length()
					<< " /// zipFileAsset->getFileNameLength(): "
					<< zipFileAsset->getFileNameLength();
			logger::info(ss);

			//local header
			ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));
			lh.describeYourself();

			filtering_istreambuf filterFileName;
			array_source source(shortFileName.c_str(),
					zipFileAsset->getFileNameLength());
			filterFileName.push(source);

			vector<char> vecFileName;
			boost::iostreams::copy(filterFileName,
					boost::iostreams::back_inserter(vecFileName));

			//file name
			ofs.write(reinterpret_cast<char *>(vecFileName.data()),
					vecFileName.size());

		}
	}

	/*
	 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
	 lh.fnameLen = shortFileName.length();

	 //local header
	 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	 //file name
	 ofs.write(shortFileName.c_str(), shortFileName.length());
	 } else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
	 filtering_istreambuf filterFileName;
	 filterFileName.push(zlib_compressor());

	 stringstream fileNameStream;
	 fileNameStream << shortFileName;
	 filterFileName.push(fileNameStream);

	 vector<char> vecFileName;
	 boost::iostreams::copy(filterFileName,
	 boost::iostreams::back_inserter(vecFileName));

	 lh.fnameLen = vecFileName.size();

	 // Local Header
	 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	 //file name
	 ofs.write(reinterpret_cast<char *>(vecFileName.data()),
	 vecFileName.size());

	 }
	 */

}

bool ZipFile::saveAssetFileName_ok(TZipLocalHeader& lh, ofstream& ofs,
		ZipFileAsset* zipFileAsset, unsigned short outputSaveMode) {

	const string shortFileName = zipFileAsset->fileName;

	stringstream ss;

	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves not compressed file name: " << shortFileName
					<< " as not compressed";
			logger::info(ss);

			// lh.fnameLen = shortFileName.length();
			lh.fnameLen = zipFileAsset->getFileNameLength();

			ss << "shortFileName.length(): " << shortFileName.length()
					<< " /// zipFileAsset->getFileNameLength(): "
					<< zipFileAsset->getFileNameLength();
			logger::info(ss);

			//local header
			ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

			lh.describeYourself();

/// START
			/*
			 filtering_istreambuf filterFileName;
			 filterFileName.push(zlib_compressor());

			 char* fileNameChar = string_utils::stringToChar(shortFileName);
			 array_source source(fileNameChar,
			 zipFileAsset->getFileNameLength());
			 filterFileName.push(source);

			 //			array_source source(shortFileName.c_str(),
			 //				zipFileAsset->getFileNameLength());

			 vector<char> vecFileName;
			 boost::iostreams::copy(filterFileName,
			 boost::iostreams::back_inserter(vecFileName));

			 //file name
			 ofs.write(reinterpret_cast<char *>(vecFileName.data()),
			 vecFileName.size());
			 */
			/// END
			/// REPLACED START
			ofs.write(shortFileName.c_str(), zipFileAsset->getFileNameLength());

/// REPLACED END

		} else {
			ss << "Saves not compressed file name: " << shortFileName
					<< " as compressed";
			logger::info(ss);
			filtering_istreambuf filterFileName;
			filterFileName.push(zlib_compressor());

			char* fileNameChar = string_utils::stringToChar(shortFileName);
			array_source source(fileNameChar,
					zipFileAsset->getFileNameLength());

//			array_source source(shortFileName.c_str(),
			//				zipFileAsset->getFileNameLength());
			filterFileName.push(source);

			// lh.fnameLen = shortFileName.length();
			lh.fnameLen = zipFileAsset->getFileNameLength();

			ss << "shortFileName.length(): " << shortFileName.length()
					<< " /// zipFileAsset->getFileNameLength(): "
					<< zipFileAsset->getFileNameLength();
			logger::info(ss);

			//local header
			ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

			lh.describeYourself();
			//file name
			//	ofs.write(shortFileName.c_str(), shortFileName.length());

			vector<char> vecFileName;
			boost::iostreams::copy(filterFileName,
					boost::iostreams::back_inserter(vecFileName));

			//file name
			ofs.write(reinterpret_cast<char *>(vecFileName.data()),
					vecFileName.size());

			/*
			 ofs.write(shortFileName.c_str(), zipFileAsset->getFileNameLength());

			 /////////////////////

			 filtering_istreambuf filterFileName;
			 filterFileName.push(zlib_compressor());

			 stringstream fileNameStream;
			 fileNameStream << shortFileName;
			 filterFileName.push(fileNameStream);

			 vector<char> vecFileName;
			 boost::iostreams::copy(filterFileName,
			 boost::iostreams::back_inserter(vecFileName));

			 lh.fnameLen = vecFileName.size();

			 // Local Header
			 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));
			 */

		}
	} else {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves compressed file name: " << shortFileName
					<< " as not compressed";
			logger::info(ss);

		} else {
			ss << "Saves compressed file name: " << shortFileName
					<< " as compressed";
			logger::info(ss);

		}
	}

	/*
	 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
	 lh.fnameLen = shortFileName.length();

	 //local header
	 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	 //file name
	 ofs.write(shortFileName.c_str(), shortFileName.length());
	 } else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
	 filtering_istreambuf filterFileName;
	 filterFileName.push(zlib_compressor());

	 stringstream fileNameStream;
	 fileNameStream << shortFileName;
	 filterFileName.push(fileNameStream);

	 vector<char> vecFileName;
	 boost::iostreams::copy(filterFileName,
	 boost::iostreams::back_inserter(vecFileName));

	 lh.fnameLen = vecFileName.size();

	 // Local Header
	 ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	 //file name
	 ofs.write(reinterpret_cast<char *>(vecFileName.data()),
	 vecFileName.size());

	 }
	 */

}

bool ZipFile::saveAssetFileContents(ofstream& ofs, ZipFileAsset* pZipFileAsset,
		unsigned short outputSaveMode, vector<char>& vecFileContents) {

	stringstream ss;

	filtering_istreambuf filterAssetFile;

	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->fileName << " as not compressed";
			logger::info(ss);
			// Do not push zlib_compressor()

			ss << "file contents size: " << pZipFileAsset->getFileDataSize();
			logger::info(ss);
			ss << "file contents: " << pZipFileAsset->m_pDirData;
			logger::info(ss);

			ss << "file contents address: " << &(pZipFileAsset->m_pDirData);
			logger::info(ss);

// START memcpy

			/*
			 char data[pZipFileAsset->getFileDataSize()];
			 memcpy(data, pZipFileAsset->m_pDirData,
			 pZipFileAsset->getFileDataSize());
			 ss << "sizeof(pZipFileAsset->getFileDataSize())"
			 << sizeof(pZipFileAsset->getFileDataSize());
			 logger::info(ss);

			 array_source source(data, pZipFileAsset->getFileDataSize());
			 */

			//// END memcpy
			array_source source(pZipFileAsset->m_pDirData,
					pZipFileAsset->getFileDataSize());

			//						array_source source(pZipFileAsset->m_pDirData,
			//				sizeof(pZipFileAsset->getFileDataSize()));
			//		array_source source(pZipFileAsset->m_pDirData,
			//			pZipFileAsset->getFileDataSize());

			filterAssetFile.push(source);

			// vector<char> vecFileContents;
			// copy filterAssetFile to vecFileContents
			boost::iostreams::copy(filterAssetFile,
					boost::iostreams::back_inserter(vecFileContents));

			ss << "vecFileContents:";
			logger::info(ss);

			ss << "";

			for (vector<char>::iterator it = vecFileContents.begin();
					it != vecFileContents.end(); ++it) {
				//cout << *it;
				ss << *it;
			}
			ss << "";
			logger::info(ss);
			ss << "vecFileContents1.size: " << vecFileContents.size();
			logger::info(ss);

			ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
					vecFileContents.size());
			//		path outFilePath { outFileName };
			//		ofstream ofs(outFilePath, ios::binary);
			ss << "vecFileContents2.size: " << vecFileContents.size();
			logger::info(ss);
			ss << "XX";
			logger::info(ss);

			int i;
		} else {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->fileName << " as compressed";
			logger::info(ss);

			filterAssetFile.push(zlib_compressor());

			array_source source(pZipFileAsset->m_pDirData,
					pZipFileAsset->getFileDataSize());

			//char data[sizeof(pZipFileAsset->getFileDataSize())];
			//memcpy(data, pZipFileAsset->m_pDirData,
			//		sizeof(pZipFileAsset->getFileDataSize()));
			//memcpy(data, &sReCo, sizeof(pZipFileAsset->getFileDataSize()));

			//array_source source(data, sizeof(char));

			filterAssetFile.push(source);

			//vector<char> vecFileContents;
			// copy filterAssetFile to vecFileContents
			boost::iostreams::copy(filterAssetFile,
					boost::iostreams::back_inserter(vecFileContents));

			ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
					vecFileContents.size());

		}
	} else {
		if (ZipFile::NOT_COMPRESSED == outputSaveMode) {
			ss << "Saves compressed file contents: " << pZipFileAsset->fileName
					<< " as not compressed";
			logger::info(ss);

			filterAssetFile.push(zlib_decompressor());

			array_source source(pZipFileAsset->m_pDirData,
					pZipFileAsset->getFileDataSize());

			filterAssetFile.push(source);

			boost::iostreams::copy(filterAssetFile,
					boost::iostreams::back_inserter(vecFileContents));

			ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
					vecFileContents.size());

		} else {
			ss << "Saves compressed file contents: " << pZipFileAsset->fileName
					<< " as compressed";
			logger::info(ss);

			array_source source(pZipFileAsset->m_pDirData,
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

			int i;

		}
	}

	/*
	 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
	 // Do not push zlib_compressor()
	 } else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
	 filterAssetFile.push(zlib_compressor());
	 }
	 */

	/*
	 ifstream assetFile(resourceFilePath, std::ios::binary);
	 int fileSize = file_size(resourceFilePath);

	 filterAssetFile.push(assetFile);

	 //vector<char> vecFileContents;
	 boost::iostreams::copy(filterAssetFile,
	 boost::iostreams::back_inserter(vecFileContents));
	 ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
	 vecFileContents.size());

	 ss << "fileSize: " << fileSize << " compressedSize: "
	 << vecFileContents.size();
	 logger::info(ss);
	 */
}

bool ZipFile::saveAssetFileContents_old_ok(ofstream& ofs,
		ZipFileAsset* pZipFileAsset, unsigned short saveMode,
		vector<char>& vecFileContents) {

	stringstream ss;

	filtering_istreambuf filterAssetFile;

	if (ZipFile::NOT_COMPRESSED == this->isCompressed) {
		if (ZipFile::NOT_COMPRESSED == saveMode) {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->fileName << " as not compressed";
			logger::info(ss);
			// Do not push zlib_compressor()

			ss << "file contents size: " << pZipFileAsset->getFileDataSize();
			logger::info(ss);
			ss << "file contents: " << pZipFileAsset->m_pDirData;
			logger::info(ss);

			ss << "file contents address: " << &(pZipFileAsset->m_pDirData);
			logger::info(ss);

//			char data[sizeof(pZipFileAsset->getFileDataSize())];
//			memcpy(data, pZipFileAsset->m_pDirData,
//					sizeof(pZipFileAsset->getFileDataSize()));
			char data[pZipFileAsset->getFileDataSize()];
			memcpy(data, pZipFileAsset->m_pDirData,
					pZipFileAsset->getFileDataSize());

			//memcpy(data, &sReCo, sizeof(pZipFileAsset->getFileDataSize()));

			ss << "sizeof(pZipFileAsset->getFileDataSize())"
					<< sizeof(pZipFileAsset->getFileDataSize());
			logger::info(ss);

			//array_source source(data, sizeof(char));
			array_source source(data, pZipFileAsset->getFileDataSize());

			// ?????????
			//		array_source source(pZipFileAsset->m_pDirData,
			//			pZipFileAsset->getFileDataSize());
// ?????

			//						array_source source(pZipFileAsset->m_pDirData,
			//				sizeof(pZipFileAsset->getFileDataSize()));
			//		array_source source(pZipFileAsset->m_pDirData,
			//			pZipFileAsset->getFileDataSize());

			filterAssetFile.push(source);

			// vector<char> vecFileContents;
			// copy filterAssetFile to vecFileContents
			boost::iostreams::copy(filterAssetFile,
					boost::iostreams::back_inserter(vecFileContents));

			ss << "vecFileContents:";
			logger::info(ss);

			ss << "";

			for (vector<char>::iterator it = vecFileContents.begin();
					it != vecFileContents.end(); ++it) {
				//cout << *it;
				ss << *it;
			}
			ss << "";
			logger::info(ss);
			ss << "vecFileContents1.size: " << vecFileContents.size();
			logger::info(ss);

			ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
					vecFileContents.size());
			//		path outFilePath { outFileName };
			//		ofstream ofs(outFilePath, ios::binary);
			ss << "vecFileContents2.size: " << vecFileContents.size();
			logger::info(ss);
			ss << "XX";
			logger::info(ss);

			int i;
		} else {
			ss << "Saves not compressed file contents: "
					<< pZipFileAsset->fileName << " as compressed";
			logger::info(ss);

			filterAssetFile.push(zlib_compressor());

			char data[sizeof(pZipFileAsset->getFileDataSize())];
			memcpy(data, pZipFileAsset->m_pDirData,
					sizeof(pZipFileAsset->getFileDataSize()));
			//memcpy(data, &sReCo, sizeof(pZipFileAsset->getFileDataSize()));

			array_source source(data, sizeof(char));

			filterAssetFile.push(source);

			vector<char> vecFileContents;
			// copy filterAssetFile to vecFileContents
			boost::iostreams::copy(filterAssetFile,
					boost::iostreams::back_inserter(vecFileContents));

			ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
					vecFileContents.size());

		}
	} else {
		if (ZipFile::NOT_COMPRESSED == saveMode) {
			ss << "Saves compressed file contents: " << pZipFileAsset->fileName
					<< " as not compressed";
			logger::info(ss);

		} else {
			ss << "Saves compressed file contents: " << pZipFileAsset->fileName
					<< " as compressed";
			logger::info(ss);

		}
	}

	/*
	 if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode) == 0) {
	 // Do not push zlib_compressor()
	 } else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
	 filterAssetFile.push(zlib_compressor());
	 }
	 */

	/*
	 ifstream assetFile(resourceFilePath, std::ios::binary);
	 int fileSize = file_size(resourceFilePath);

	 filterAssetFile.push(assetFile);

	 //vector<char> vecFileContents;
	 boost::iostreams::copy(filterAssetFile,
	 boost::iostreams::back_inserter(vecFileContents));
	 ofs.write(reinterpret_cast<char *>(vecFileContents.data()),
	 vecFileContents.size());

	 ss << "fileSize: " << fileSize << " compressedSize: "
	 << vecFileContents.size();
	 logger::info(ss);
	 */
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
	dfh->cSize = vecFileContents.size();
	dfh->fnameLen = lh.fnameLen;
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

		ss << "fileName: " << it->second->fileName;
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
	ofs.write(reinterpret_cast<char *>(&dh), sizeof(dh));

	ofs.close();
	return true;

	/*

	 //////////////////////
	 if (ofs.is_open()) {
	 ss << "OPEN OPEN OPEN " << filePath.string();
	 logger::info(ss);

	 TZipDirHeader dh;
	 list<TZipDirFileHeader*> dirFileHeadersList;

	 string assetsRegex = this->m_rootFolder + "assets[/\\\\]";
	 regex exprAssetsFolder(assetsRegex);

	 for (path resourcePath : m_paths) {

	 string replacedPath = regex_replace(resourcePath.string(),
	 exprAssetsFolder, "");

	 this->saveAsset(ofs, resourcePath, replacedPath, dirFileHeadersList,
	 dh, saveMode);

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

	 ofs.write(reinterpret_cast<char *>(*it), sizeof(TZipDirFileHeader)); // OK wynik plik: ABCD; dla kompresji: x.strv...
	 };

	 // Save TZipDirHeader
	 dh.nDirEntries = dirFileHeadersList.size();
	 ofs.write(reinterpret_cast<char *>(&dh), sizeof(dh));

	 ofs.close();
	 return true;

	 } else {
	 ss << "CLOSED " << filePath.string();
	 logger::warning(ss);
	 return false;
	 }

	 ///////////////////////////////////


	 stringstream ss;
	 //			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));


	 path outFilePath{outFileName};
	 ofstream ofs{outFilePath};

	 ss << "Save compressed: ";

	 for (vector<char>::iterator it = m_fileData.begin(); it != m_fileData.end(); ++it) {
	 //cout << *it;
	 ofs << *it;

	 ss << *it;
	 }
	 cout << endl;

	 logger::info(ss);


	 logger::info("-------------");
	 */
}
;

// Saves data as compressed file
void ZipFile::saveCompressed_111(const std::string& outFileName) {

	stringstream ss;
	//			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));

	path outFilePath { outFileName };
	ofstream ofs { outFilePath };

	ss << "Save compressed: ";

	for (vector<char>::iterator it = m_fileData.begin(); it != m_fileData.end();
			++it) {
		//cout << *it;
		ofs << *it;

		ss << *it;
	}
	cout << endl;

	logger::info(ss);

	logger::info("-------------");
}
;

/*
 // Saves data as compressed file
 bool ZipFile::saveCompressed(const std::string& outFileName) {

 stringstream ss;
 //			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));

 path outFilePath { outFileName };
 ofstream ofs { outFilePath };

 ss << "Save compressed: ";

 for (vector<char>::iterator it = m_fileData.begin(); it != m_fileData.end();
 ++it) {
 //cout << *it;
 ofs << *it;

 ss << *it;
 }
 cout << endl;

 logger::info(ss);

 logger::info("-------------");

 return true;
 }
 ;
 */

bool ZipFile::prepareOutputDir(const string assetsOutFolder) {

	stringstream ss;

	//string assetsOutFolder = getOutputFolderName(folderName);

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

string ZipFile::zipToUnzip(string zipString) {

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
		//cout << *it;
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
//	m_pZipDirHeader->describeYourself();
//	logger::info("CONTINUE createFilesAndFolders");
//	this->describeYourself();

	for (map<string, ZipFileAsset*>::iterator it = m_zipContentsMap.begin();
			it != m_zipContentsMap.end(); ++it) {
		// it->second->describeYourself();

		ss << "fileName: " << it->second->fileName;
		logger::info(ss);

		//ss << "unzipFileName: " << it->second->getUnzipFileName();
		//logger::info(ss);

		path pathAsset { folderName };

		if (ZipFile::COMPRESSED == this->isCompressed) {

			string unzipFileName = this->zipToUnzip(it->second->fileName);
			pathAsset /= unzipFileName;
		} else {

			// No need to unzip
			pathAsset /= it->second->fileName;
		}
		//pathAsset /= it->second->getUnzipFileName();

//		path fullAssetPath { pathAsset.string() };
		path fullAssetPath { pathAsset };

		// ss << "full Path: " << pathAsset.string();
		// logger::info(ss);

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

		//	pathAssetsDev.

		//	logger::info(ss);

		// char* pLocalHeader = it->second->m_pZipLocalHeader;

		// ss << "fileNameLength: " << it->second->getFileNameLength();

	}

	logger::info("END createFilesAndFolders");

	/*
	 string assetsRegex = this->m_rootFolder + "assets[/\\\\]";

	 regex exprAssetsFolder(assetsRegex);

	 for (path resourcePath : m_paths) {

	 path parentPath = resourcePath.parent_path();

	 path newFolder { folderName };
	 newFolder /= regex_replace(parentPath.string(), exprAssetsFolder, "");

	 createFolder(newFolder);

	 copyFile(resourcePath, newFolder);
	 }
	 */

	/*
	 string assetsRegex = this->m_rootFolder + "assets[/\\\\]";

	 regex exprAssetsFolder(assetsRegex);

	 for (path resourcePath : m_paths) {

	 path parentPath = resourcePath.parent_path();

	 path newFolder { folderName };
	 newFolder /= regex_replace(parentPath.string(), exprAssetsFolder, "");

	 createFolder(newFolder);

	 copyFile(resourcePath, newFolder);
	 }
	 */

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

bool ZipFile::copyFile(path inPath, ZipFileAsset* pZipFileAsset) {
	stringstream ss;

	if (ZipFile::NOT_COMPRESSED == isCompressed) {
		ss << "Saving not compressed files to folder";
		logger::info(ss);

		// Nothing needs any changes

		copyUnzipFile(inPath, pZipFileAsset);
	} else {
		ss << "Saving compressed files to folder";
		logger::info(ss);

		// TODO unzipping must be performed !!!
		// use zlib_decompressor
		copyZipFile(inPath, pZipFileAsset);
	}

}

bool ZipFile::copyZipFile(path inPath, ZipFileAsset* pZipFileAsset) {
	//TODO: TO IMPLEMENT

	stringstream ss;
	ss << "copy file into: " << inPath.make_preferred();
	logger::info(ss);

	filtering_istreambuf filter;
	filter.push(zlib_decompressor());
	array_source source(pZipFileAsset->m_pDirData,
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

	return true;
}

bool ZipFile::copyUnzipFile(path inPath, ZipFileAsset* pZipFileAsset) {

	stringstream ss;

	ss << "copy file into: " << inPath.make_preferred();
	logger::info(ss);

	//pZipFileAsset->getFileDataSize();
	char* filePointer = pZipFileAsset->m_pDirData;

//	if (ifs.is_open()) {
	//	ss << "OTWARTY " << inPath.filename();
	//	logger::info(ss);

// 	filtering_istreambuf inDec;
//		inDec.push(ifs);

	vector<char> vecCharDec;
	for (unsigned long i = 0; i < pZipFileAsset->getFileDataSize(); i++) {
		vecCharDec.push_back(*filePointer);
		filePointer++;
	}

	// boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	ofstream ofs(inPath, std::ios::binary);
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size());
	ofs.close();

//	ifs.close();
//	}

	/*
	 stringstream ss;

	 ifstream ifs(inPath, std::ios::binary);

	 path newFilePath { };
	 newFilePath /= outFolder;
	 newFilePath /= inPath.filename();

	 if (ifs.is_open()) {
	 //	ss << "OTWARTY " << inPath.filename();
	 //	logger::info(ss);

	 filtering_istreambuf inDec;
	 inDec.push(ifs);

	 vector<char> vecCharDec;
	 boost::iostreams::copy(inDec,
	 boost::iostreams::back_inserter(vecCharDec));

	 ofstream ofs(newFilePath, std::ios::binary);
	 ofs.write(reinterpret_cast<char *>(vecCharDec.data()),
	 vecCharDec.size());
	 ofs.close();
	 ifs.close();
	 }

	 */

	return true;
}

// Saves data as compressed file
void ZipFile::saveAsFolder(const string& outFolderName) {

	stringstream ss;
	//			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));

//	path outFolderPath { outFolderName };
	prepareOutputDir(outFolderName);
	createFilesAndFolders(outFolderName);

	//prepareOutputDir(folderFullName);
	//createFilesAndFolders(folderFullName);

	/*
	 ofstream ofs{outFilePath};

	 ss << "Save compressed: ";

	 for (vector<char>::iterator it = m_fileData.begin(); it != m_fileData.end(); ++it) {
	 //cout << *it;
	 ofs << *it;

	 ss << *it;
	 }
	 cout << endl;

	 logger::info(ss);
	 */

	logger::info("-------------");
}
;

// Saves data as compressed file
void ZipFile::saveCompressedAll(const std::string& outFileName) {

	stringstream ss;
	//			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));

	path outFilePath { outFileName };
	ofstream ofs { outFilePath };

	ss << "Save compressed: ";

	for (vector<char>::iterator it = m_fileData.begin(); it != m_fileData.end();
			++it) {
		//cout << *it;
		ofs << *it;

		ss << *it;
	}
	cout << endl;

	logger::info(ss);

	logger::info("-------------");
}
;

// Decompresses data and saves in decompressed file
void ZipFile::saveNotCompressed_111(const std::string& outFileName) {
	stringstream ss;

	array_source src { m_fileData.data(), m_fileData.size() };
	filtering_istreambuf inDec; //filtering_streambuf<input>

	inDec.push(zlib_decompressor());
	inDec.push(src);

	vector<char> vecCharDec;

	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	path outFilePath { outFileName };
	ofstream ofs { outFilePath };

	ss << "Start decompressed: ";

	for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end();
			++it) {
		//cout << *it;
		ofs << *it;
		ss << *it;
	}

	cout << endl;

	logger::info(ss);
}
;

void ZipFile::saveNotCompressedAll_111(const std::string& outFileName) {

	stringstream ss;

	array_source src { m_fileData.data(), m_fileData.size() };
	filtering_istreambuf inDec; //filtering_streambuf<input>

	inDec.push(zlib_decompressor());
	inDec.push(src);

	vector<char> vecCharDec;

	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	path outFilePath { outFileName };
	//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
	ofstream ofs { outFilePath };

	ss << "Start decompressed: ";

	for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end();
			++it) {
		//cout << *it;

		// ofs.write(*it);
		ofs << *it;
		ss << *it;
	}

	TZipDirFileHeader fh;
	fh.verMade = 55;
	//	fh.isCompression = TZipDirFileHeader::Z_NO_COMPRESSION;
	fh.isCompression = Z_NO_COMPRESSION; // see: zlib.h

	//ofs.write(reinterpret_cast<const char*>(&fh.sig), sizeof fh.sig);

	//ofs << fh;

	ofs << endl;

	TZipDirHeader dh;
	dh.dirSize = 77; //???
	dh.nDirEntries = 1;
	//	dh.isCompression = TZipDirHeader::Z_NO_COMPRESSION;
	dh.isCompression = Z_NO_COMPRESSION; // see: zlib.h

	//ofs << dh;

	ofs << endl;

	cout << endl;

	logger::info(ss);
}
;

void ZipFile::saveNotCompressedAll(const std::string& outFileName) {

	stringstream ss;

	array_source src { m_fileData.data(), m_fileData.size() };
	filtering_istreambuf inDec; //filtering_streambuf<input>

	inDec.push(zlib_decompressor());
	inDec.push(src);

	vector<char> vecCharDec;

	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	path outFilePath { outFileName };
	//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
	//		ofstream ofs{outFilePath};
	ofstream ofs(outFilePath, ios::binary);

	ss << "Start decompressed: ";

	for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end();
			++it) {
		//cout << *it;

		// ofs.write(*it);
		//		ofs << *it;
		ss << *it;
	}

	TZipDirFileHeader fh;
	fh.testInitiation();

	//fh.verMade = 55;
	//fh.isCompression = TZipDirFileHeader::Z_NO_COMPRESSION;

	//ofs.write(reinterpret_cast<const char*>(&fh.sig), sizeof fh.sig);

	//ofs << fh;
	//ofs << endl;

	ofs.write(reinterpret_cast<char *>(&fh), sizeof(fh));

	TZipDirHeader dh;
	dh.dirSize = 77; //???
	dh.nDirEntries = 1;
//		dh.isCompression = TZipDirHeader::Z_NO_COMPRESSION;
	dh.isCompression = Z_NO_COMPRESSION; // zlib.h

	//ofs.write(reinterpret_cast<char *>(&dh),sizeof(dh));

	//		ofs << dh;

	//	ofs << endl;

	cout << endl;

	logger::info(ss);

	ss << "SIZE_OF_FH: " << sizeof(fh);
	logger::info(ss);

}
;

// --------------------------------------------------------------------------
// Function:      test_saveCompressedDirFileHeader
// Purpose:       Initialize TZipDirFileHeader fh with testInitiation(),
//                  compress fh and save to file
//               Read further this file with test_initCompressedDirFileHeader
// Parameters:
// --------------------------------------------------------------------------
void ZipFile::test_saveCompressedDirFileHeader(const std::string& outFileName) {

	stringstream ss;

	TZipDirFileHeader fh;
	fh.testInitiation();

	//array_source src{reinterpret_cast<char *>(&fh),sizeof(fh)};
	filtering_istreambuf inDec;
	/*filtering_streambuf<input>
	 See http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/classes/filtering_streambuf.html#headers
	 */
	/*
	 * zlib_compressor() - Filter
	 * see:
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/classes/zlib.html#basic_zlib_compressor
	 *
	 * zlib_compressor is DualUseFilter which act as an InputFilter or as an OutputFilter
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/concepts/dual_use_filter.html
	 *
	 */

	inDec.push(zlib_compressor());
	/*
	 * see http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/classes/filtering_streambuf.html#headers
	 *
	 * void push( const T& t, ...
	 * where T	-	A CopyConstructible model of one of the Filter or Device concepts
	 * whose character type is Ch and whose mode refines Mode
	 *
	 * zlib_compressor is InputFilter when passed to input stream
	 * see
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/guide/filtering_streams.html
	 */

	/**
	 * We use output device  array_source
	 */
	array_source source { reinterpret_cast<char *>(&fh), sizeof(fh) };

	/**
	 * Input inDec filtering_streambuf<input> accepts output array_source as push parameter.
	 *
	 * If a filtering_streambuf or filtering_stream has mode input,
	 * data flows from the chain's end to its beginning — starting at a Source
	 * and passing through zero or more InputFilters
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/guide/filtering_streams.html
	 *
	 */
	inDec.push(source);

	vector<char> vecCharDec;

	// copy compressed inDec to vecCharDec
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	//ss << vecCharDec;
	//logger::info(ss);

	path outFilePath { outFileName };
	ofstream ofs(outFilePath, ios::binary);

	/**
	 for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
	 //cout << *it;
	 ofs.write(reinterpret_cast<char *>(&it),sizeof(it));
	 }
	 */
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size());// OK wynik plik: ABCD; dla kompresji: x.strv...

	ofs.close();
	//inDec.close();

}
;

// --------------------------------------------------------------------------
// Function:      test_saveNotCompressedDirFileHeaderArraySource
// Purpose:       Initialize TZipDirFileHeader fh with testInitiation(),
//                  and save to file. USes array_source
//               Read further this file with test_initCompressedDirFileHeader
// Parameters:
// --------------------------------------------------------------------------
void ZipFile::test_saveNotCompressedDirFileHeaderArraySource(
		const std::string& outFileName) {

	stringstream ss;

	TZipDirFileHeader fh;
	fh.testInitiation();

	//array_source src{reinterpret_cast<char *>(&fh),sizeof(fh)};
	filtering_istreambuf inDec;
	/*filtering_streambuf<input>
	 See http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/classes/filtering_streambuf.html#headers
	 */
	/*
	 * zlib_compressor() - Filter
	 * see:
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/classes/zlib.html#basic_zlib_compressor
	 *
	 * zlib_compressor is DualUseFilter which act as an InputFilter or as an OutputFilter
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/concepts/dual_use_filter.html
	 *
	 */

	//inDec.push(zlib_compressor());
	/*
	 * see http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/classes/filtering_streambuf.html#headers
	 *
	 * void push( const T& t, ...
	 * where T	-	A CopyConstructible model of one of the Filter or Device concepts
	 * whose character type is Ch and whose mode refines Mode
	 *
	 * zlib_compressor is InputFilter when passed to input stream
	 * see
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/guide/filtering_streams.html
	 */

	/**
	 * We use output device  array_source
	 */
	array_source source { reinterpret_cast<char *>(&fh), sizeof(fh) };

	/**
	 * Input inDec filtering_streambuf<input> accepts output array_source as push parameter.
	 *
	 * If a filtering_streambuf or filtering_stream has mode input,
	 * data flows from the chain's end to its beginning — starting at a Source
	 * and passing through zero or more InputFilters
	 * http://www.boost.org/doc/libs/1_64_0/libs/iostreams/doc/guide/filtering_streams.html
	 *
	 */
	inDec.push(source);

	vector<char> vecCharDec;

	// copy compressed inDec to vecCharDec
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	//ss << vecCharDec;
	//logger::info(ss);

	path outFilePath { outFileName };
	ofstream ofs(outFilePath, ios::binary);

	/**
	 for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
	 //cout << *it;
	 ofs.write(reinterpret_cast<char *>(&it),sizeof(it));
	 }
	 */
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size());// OK wynik plik: ABCD; dla kompresji: x.strv...

	ofs.close();
	//inDec.close();

}
;
// --------------------------------------------------------------------------
// Function:      test_saveNotCompressedDirFileHeader
// Purpose:       Initialize TZipDirFileHeader fh with testInitiation(),
//                  save uncompressed fh to file
//                 Read further this file with test_initNotCompressedDirFileHeader
// Parameters:
// --------------------------------------------------------------------------
void ZipFile::test_saveNotCompressedDirFileHeader(
		const std::string& outFileName) {

	stringstream ss;

	path outFilePath { outFileName };
	//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
	//		ofstream ofs{outFilePath};
	ofstream ofs(outFilePath, ios::binary);

	TZipDirFileHeader fh;
	fh.testInitiation();
	/*
	 * http://en.cppreference.com/w/cpp/io/basic_ostream/write
	 *
	 * basic_ostream& write( const char_type* s, std::streamsize count );
	 */
	ofs.write(reinterpret_cast<char *>(&fh), sizeof(fh));

	logger::info(ss);

	ss << "SIZE_OF_FH: " << sizeof(fh);
	logger::info(ss);

//		ss << fh;
//		logger::info(ss);

	ofs.close();

}
;

void ZipFile::test_saveSingleNotCompressedTxtFile(const string& inFilePath,
		ofstream& ofs) {

	logger::info("+++++++++++START++++++++++");
	string line;
	{

		// typedef basic_ifstream<char> 		ifstream;
		ifstream myfile(inFilePath);

		if (myfile.is_open()) {

			// https://stackoverflow.com/questions/34836268/reading-a-file-line-by-line-with-boost-filesystem-c
			while (getline(myfile, line)) {
				//ofs.write(reinterpret_cast<char *>(&line), sizeof(line));
				ofs.write(line.c_str(), sizeof(line));

				logger::info(line);
			}
//			myfile >> line;
//			myfile.get

			/*
			 while (myfile >> )

			 logger::info("otwarte!!!!");

			 while (getline(myfile, line)) {
			 ss << line << endl;
			 }

			 //ss << myfile;
			 logger::info(ss);*/

			myfile.close();
		}
		{
			//line << endl;
			logger::info("NIE otwarte!!!!");
		}
	} //open tempTestZipFile.txt
	logger::info("+++++++++++END+++++++++++");

}

// --------------------------------------------------------------------------
// Function:      test_saveNotCompressedDirFileHeader
// Purpose:       Initialize TZipDirHeader, TZipDirFileHeader, TZipLocalHeader with testInitiation(),
//                  save uncompressed fh to file
//                 Read further this file with test_initNotCompressedAll
// Parameters:
// --------------------------------------------------------------------------

void ZipFile::test_saveNotCompressedAll(const string& outFileName,
		const string& assetsFolder) {
	stringstream ss;

	path outFilePath { outFileName };
	//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
	//		ofstream ofs{outFilePath};

	// typedef basic_ofstream<char> ofstream;
	ofstream ofs(outFilePath, ios::binary);

	TZipDirHeader dh;
	dh.testInitiation();

	TZipDirFileHeader dfh;
	dfh.testInitiation();

	TZipLocalHeader lh;
	lh.testInitiation();

	//local header
	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	string filename = assetsFolder + "graphics/tempTestZipFile.txt";
	test_saveSingleNotCompressedTxtFile(filename, ofs);

	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	filename = assetsFolder + "graphics/tempSecondZip.txt";
	test_saveSingleNotCompressedTxtFile(filename, ofs);

	ofs.write(reinterpret_cast<char *>(&lh), sizeof(lh));

	filename = assetsFolder + "graphics/tempThirdZip.txt";
	test_saveSingleNotCompressedTxtFile(filename, ofs);

	/*
	 * http://en.cppreference.com/w/cpp/io/basic_ostream/write
	 *
	 * basic_ostream& write( const char_type* s, std::streamsize count );
	 */
	// Dir File Header
	ofs.write(reinterpret_cast<char *>(&dfh), sizeof(dfh));

	///Dir header
	ofs.write(reinterpret_cast<char *>(&dh), sizeof(dh));

	logger::info(ss);

	ss << "SIZE_OF_FH: " << sizeof(dfh);
	logger::info(ss);

	//ss << dfh;
	//logger::info(ss);

	ofs.close();
}

int ZipFile::test_saveMiniZipCompressedAll(std::vector<std::wstring> paths,
		const string& outFileName, const string& assetsFolder) {
	//see https://stackoverflow.com/questions/11370908/how-do-i-use-minizip-on-zlib

	/*
	 std::vector<std::wstring> destinationPath;
	 string pathTemp = assetsFolder + "tempGraphics2";
	 std::wstring wsTmp2(pathTemp.begin(), pathTemp.end());
	 destinationPath.push_back(wsTmp2);
	 */

	/*

	 std::vector<std::string> destinationPath;
	 string pathTemp = assetsFolder + "tempGraphics2";
	 destinationPath.push_back(pathTemp);

	 int my_S_OK = 0x00000000;

	 zipFile zf = zipOpen(
	 std::string(destinationPath.begin(), destinationPath.end()).c_str(),
	 APPEND_STATUS_CREATE);
	 if (zf == NULL)
	 return 1;



	 bool _return = true;
	 for (size_t i = 0; i < paths.size(); i++) {
	 std::fstream file(paths[i].c_str(), std::ios::binary | std::ios::in);
	 if (file.is_open()) {
	 file.seekg(0, std::ios::end);
	 long size = file.tellg();
	 file.seekg(0, std::ios::beg);

	 std::vector<char> buffer(size);
	 if (size == 0 || file.read(&buffer[0], size)) {
	 zip_fileinfo zfi = { 0 };
	 std::string fileName = paths[i].substr(
	 paths[i].rfind('\\') + 1);


	 if (my_S_OK
	 == zipOpenNewFileInZip(zf,
	 std::string(fileName.begin(), fileName.end()).c_str(),
	 &zfi, NULL, 0, NULL, 0, NULL, Z_DEFLATED,
	 Z_DEFAULT_COMPRESSION)) {
	 if (zipWriteInFileInZip(zf, size == 0 ? "" : &buffer[0],
	 size))
	 _return = false;

	 if (zipCloseFileInZip(zf))
	 _return = false;

	 file.close();
	 continue;
	 }
	 }
	 file.close();
	 }
	 _return = false;
	 }

	 if (zipClose(zf, NULL))
	 return 3;

	 if (!_return)
	 return 4;
	 return my_S_OK;
	 */
	return 1;
}

void ZipFile::test_saveMiniZipCompressedAll_111(const string& outFileName,
		const string& assetsFolder) {
	//see https://stackoverflow.com/questions/11370908/how-do-i-use-minizip-on-zlib

	stringstream ss;
	zip_fileinfo zfi;

	//string filename = assetsFolder + "graphics/tempTestZipFile.txt";

	//zipFile zf = zipOpen("myarch.zip",APPEND_STATUS_ADDINZIP);

	string filename = assetsFolder + "tempTestZipFile.txt";

	zipFile zf = zipOpen(outFileName.c_str(), APPEND_STATUS_ADDINZIP);

	//int ret = zipOpenNewFileInZip(zf, "myfile.txt", &zfi,
	int ret = zipOpenNewFileInZip(zf, filename.c_str(), &zfi,
	NULL, 0,
	NULL, 0, "my comment for this interior file", Z_DEFLATED, Z_NO_COMPRESSION);
	zipCloseFileInZip(zf);
	zipClose(zf, "my comment for exterior file");

}

// --------------------------------------------------------------------------
// Function:      test_initNotCompressedAll
// Purpose:       read file that contains uncompressed TZipDirHeader, TZipDirFileHeader, TZipLocalHeader
//                  display fh at screen
//                File was save using test_saveNotCompressedAll
// Parameters:
// --------------------------------------------------------------------------
bool ZipFile::test_initNotCompressedAll(const std::string& resFileName) {
	return true;
}

void ZipFile::test_saveNotCompressedAbcd(const std::string& outFileName) {

	stringstream ss;

	TZipDirFileHeader fh;
	fh.testInitiation();

	filtering_istreambuf inDec;

	//inDec.push(zlib_compressor());

	std::stringstream original;
	std::string fhstr = "ABCD";

	original << fhstr; // Dla plików ABCD
	inDec.push(original);
//	inDec.push(fhstr);

	vector<char> vecCharDec;

	// copy compressed inDec to vecCharDec
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

	path outFilePath { outFileName };
	ofstream ofs(outFilePath, ios::binary);

	/**
	 * //ofs.write(reinterpret_cast<char *>(&vecCharDec), sizeof(vecCharDec));

	 */

	//ofs.write(reinterpret_cast<char *>(&vecCharDec[0]), sizeof(vecCharDec));
	//ofs.write(reinterpret_cast<char *>(fhstr.data()), sizeof(fhstr));
	//ofs.write(fhstr.c_str(), fhstr.size());//OK wynik plik: ABCD
//		ofs << original.str();	//OK wynik plik: ABCD
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size());// OK wynik plik: ABCD; dla kompresji: x.strv...

	ofs.close();

}
;

void ZipFile::test_saveCompressedAbcd(const std::string& outFileName) {

//return; // ERROR - remove and fix the ERROR
	stringstream ss;

	TZipDirFileHeader fh;
	fh.testInitiation();

	//array_source src{reinterpret_cast<char *>(&fh),sizeof(fh)};
	filtering_istreambuf inDec;
	inDec.push(zlib_compressor());

	std::stringstream original;
	std::string fhstr = "ABCD";

	/*
	 * http://www.cplusplus.com/reference/ostream/ostream/write/
	 */
	original << fhstr; // Dla plików ABCD
//	original.write(reinterpret_cast<char *>(&fh), sizeof(fh));
	inDec.push(original);
//	inDec.push(fhstr);

	vector<char> vecCharDec;

	// copy compressed inDec to vecCharDec
	boost::iostreams::copy(inDec, boost::iostreams::back_inserter(vecCharDec));

//ss << vecCharDec;
//logger::info(ss);

	path outFilePath { outFileName };
	ofstream ofs(outFilePath, ios::binary);

	/**
	 for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
	 //cout << *it;
	 ofs.write(reinterpret_cast<char *>(&it),sizeof(it));
	 }
	 */
	/**
	 * //ofs.write(reinterpret_cast<char *>(&vecCharDec), sizeof(vecCharDec));

	 */

//ofs.write(reinterpret_cast<char *>(&vecCharDec[0]), sizeof(vecCharDec));
//ofs.write(reinterpret_cast<char *>(fhstr.data()), sizeof(fhstr));
//ofs.write(fhstr.c_str(), fhstr.size());//OK wynik plik: ABCD
//		ofs << original.str();	//OK wynik plik: ABCD
	ofs.write(reinterpret_cast<char *>(vecCharDec.data()), vecCharDec.size()); // OK wynik plik: ABCD; dla kompresji: x.strv...

	ofs.close();

}
;

// --------------------------------------------------------------------------
// Function:      ReadFile
// Purpose:       Uncompress a complete file
// Parameters:    The file index and the pre-allocated buffer
// --------------------------------------------------------------------------
bool ZipFile::readFile(int i, void *pBuf) {
	// TODO: decompress file
	return true;
}

}

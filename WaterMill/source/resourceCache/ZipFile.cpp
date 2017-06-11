#include "ZipFile.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"
#include "TZipDirHeader.h"
#include "TZipDirFileHeader.h"


#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/device/file.hpp> // boost::iostreams::file_source
#include <boost/iostreams/stream.hpp> // boost::iostreams::stream
#include <boost/iostreams/filtering_stream.hpp> // boost::iostreams::filtering_istream;
#include <boost/iostreams/device/array.hpp> // boost::iostreams::array_source, boost::iostreams::array_sink
#include <boost/filesystem/fstream.hpp>

#include <sstream>      // std::stringstream
#include <string>
#include <fstream> // ifstream
#include <vector> // vector
#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;

#include <cstring>// strcpy, stlen
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
using boost::iostreams::array_sink;

//typedef unsigned long dword;
//typedef unsigned short word;
//typedef unsigned char byte;


namespace base_game {
	ZipFile::ZipFile() {
		logger::info("Create ZipFile");
		m_pDirData = nullptr;
		//	fileData = nullptr;
	}

	ZipFile::~ZipFile() {
		logger::info("Destroy ZipFile");
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
			stream<file_source> fileSourceStream (myFile);


			// size of fileSourceStream
			int fileSourceStreamSize = boost::iostreams::seek(fileSourceStream,0,std::ios_base::end);
			boost::iostreams::seek(fileSourceStream,0,std::ios_base::beg); // return to the beginning before invoking any other actions

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
			memory_stream.seekg(0,ios::end);
			int size_memory_stream = memory_stream.tellg();

			ss << "size of memory_stream: " << size_memory_stream;
			logger::info(ss);

			//boost::iostreams::copy(memory_stream, ss);

			ss << memory_stream.str();
			logger::info(ss);

			logger::info("--2--");


			memory_stream.seekg(0,ios::beg); // we must return to the beginning of memory_stream before osbuf.push(memory_stream);


			filtering_istreambuf osbuf; //filtering_streambuf<output>
			osbuf.push(zlib_decompressor());
			osbuf.push(memory_stream);


			stringstream decompressed_memory;

			boost::iostreams::copy(osbuf, decompressed_memory);

			ss << decompressed_memory.str();
			logger::info(ss);

			// size of decompressed_memory
			decompressed_memory.seekg(0,ios::end);
			int size_decompressed_memory = decompressed_memory.tellg();
			decompressed_memory.seekg(0,ios::beg); // we must return to the beginning of decompressed_memory


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
			stream<file_source> fileSourceStream (myFile);


			int fileSourceStreamSize = boost::iostreams::seek(fileSourceStream,0,std::ios_base::end);

			boost::iostreams::seek(fileSourceStream,0,std::ios_base::beg); // return to the beginning before invoking any other actions

			ss << "file size: " << fileSourceStreamSize;
			logger::info(ss);


			filtering_istreambuf in; //filtering_streambuf<input>
			//filtering_streambuf<file_source> in;

			//filtering_istream in;
			in.push(zlib_compressor());
			in.push(fileSourceStream);

			boost::iostreams::copy(in, memory_stream);

			cout << memory_stream.str() <<  endl;
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
			memory_stream.seekg(0,ios::end);
			int size_memory_stream = memory_stream.tellg();

			ss << "size of memory_stream: " << size_memory_stream;
			logger::info(ss);


			ss << "size of memory_stream.str().length: " << memory_stream.str().length();
			logger::info(ss);



			m_pDirData = new char[size_memory_stream+1]; // 3+1


			ss << "size of m_pDirData: " << sizeof(m_pDirData)/sizeof(m_pDirData[0]);

			logger::info(ss);

			ss << "strlen of m_pDirData: " << strlen(m_pDirData);

			logger::info(ss);


			//			std::fill(m_pDirData, m_pDirData+sizeof(m_pDirData));

			for (int i=0; i<size_memory_stream; i++) { // <3 [0,1,2]
				m_pDirData[i] = '0' + i % 10 ;
			}
			m_pDirData[size_memory_stream] = '\0'; //[3]

			string dirDataIntoStr(m_pDirData);

			ss << "dirDataIntoStr init: " << dirDataIntoStr;
			logger::info(ss);

			strcpy(m_pDirData,memory_stream.str().c_str());
			m_pDirData[size_memory_stream] = '\0'; //[3] add the proper ending



			ss << "dirDataIntoStr length: " << dirDataIntoStr.length();
			logger::info(ss);

			string dirDataIntoStr2(m_pDirData);

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

			memory_stream.seekg(0,ios::beg); // we must return to the beginning of memory_stream before osbuf.push(memory_stream);


			filtering_istreambuf osbuf; //filtering_streambuf<output>
			osbuf.push(zlib_decompressor());
			osbuf.push(memory_stream);


			stringstream decompressed_memory;

			boost::iostreams::copy(osbuf, decompressed_memory);

			ss << decompressed_memory.str();
			logger::info(ss);


			logger::info("--decompressed 3--");

			// size of decompressed_memory
			decompressed_memory.seekg(0,ios::end);
			int size_decompressed_memory = decompressed_memory.tellg();
			decompressed_memory.seekg(0,ios::beg); // we must return to the beginning of decompressed_memory







			ss << "size of decompressed_memory: " << size_decompressed_memory;
			logger::info(ss);


			ss << "size of decompressed_memory.str().length: " << decompressed_memory.str().length();
			logger::info(ss);




			// //

			char *m_pDirDataDec  = new char[size_decompressed_memory+1]; // 3+1


			ss << "size of m_pDirDataDec: " << sizeof(m_pDirDataDec) / sizeof(m_pDirDataDec[0]);
			logger::info(ss);

			ss << "strlen of m_pDirDataDec: " << strlen(m_pDirDataDec);

			logger::info(ss);

			for (int i=0; i<size_decompressed_memory; i++) { // <3  [0,1,2]
				m_pDirDataDec[i] = '0' + i % 10 ;
			}
			m_pDirDataDec[size_decompressed_memory] = '\0'; //[3]


			string dirDataIntoStrDec(m_pDirDataDec);

			ss << "dirDataIntoStrDec init: " << dirDataIntoStrDec;
			logger::info(ss);


			strcpy(m_pDirDataDec,decompressed_memory.str().c_str());
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

		templates::safe_delete_array<char>(m_pDirData);

		return true;
	}

	bool ZipFile::init(const string& resFileName) {


		//stringstream memory_stream;

		stringstream ss;


		ss << "ZipFile::init: " << resFileName;
		logger::info(ss);

		//file_source myFile{resFileName};
		file_source myFile(resFileName); // typedef basic_file_source<char> file_source



		if (myFile.is_open()) {
			//			stream<file_source> fileSourceStream {myFile};
			stream<file_source> fileSourceStream (myFile);

			vector<char> vecChar;
			//back_insert_device<vector<char>> snk{vecChar};

			filtering_istreambuf in; //filtering_streambuf<input>

			in.push(zlib_compressor());
			in.push(fileSourceStream);

			boost::iostreams::copy(in,boost::iostreams::back_inserter(vecChar));

			ss << "Start compressed: ";

			for (vector<char>::iterator it = vecChar.begin(); it != vecChar.end(); ++it) {
				//cout << *it;
				ss << *it;
			}
			cout << endl;

			logger::info(ss);


			logger::info("-------------");

			array_source src{vecChar.data(), vecChar.size()};
			filtering_istreambuf inDec; //filtering_streambuf<input>

			inDec.push(zlib_decompressor());
			inDec.push(src);

			vector<char> vecCharDec;

			boost::iostreams::copy(inDec,boost::iostreams::back_inserter(vecCharDec));

			ss << "Start decompressed: ";

			for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
				//cout << *it;
				ss << *it;
			}
			cout << endl;

			logger::info(ss);
			//boost::iostreams::copy(in, vecChar);

			myFile.close();
		}

		templates::safe_delete_array<char>(m_pDirData);

		return true;
	}

// --------------------------------------------------------------------------
// Function:      initCompressed
// Purpose:       loads file that has compression saves data into vector<char> data
// Parameters:
// --------------------------------------------------------------------------

	bool ZipFile::initCompressed(const std::string& resFileName) {
		return true;
	};

	// --------------------------------------------------------------------------
	// Function:      initNotCompressed
	// Purpose:       loads file that has no compression and compress its data into vector<char> data
	// Parameters:
	// --------------------------------------------------------------------------
	bool ZipFile::initNotCompressed(const std::string& resFileName) {

		//stringstream memory_stream;
		stringstream ss;

		ss << "ZipFile::init: " << resFileName;
		logger::info(ss);

		//file_source myFile{resFileName};
		file_source myFile(resFileName); // typedef basic_file_source<char> file_source

		if (myFile.is_open()) {
			//			stream<file_source> fileSourceStream {myFile};
			stream<file_source> fileSourceStream (myFile);

			//	vector<char> vecChar;
			//back_insert_device<vector<char>> snk{vecChar};

			filtering_istreambuf in; //filtering_streambuf<input>

			in.push(zlib_compressor());// contains a chain of zero or more Filters
			in.push(fileSourceStream);// with an optional Device at the end.

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
			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));

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

			for (vector<char>::iterator it = fileData.begin(); it != fileData.end(); ++it) {
				//cout << *it;
				ss << *it;
			}
			cout << endl;

			logger::info(ss);


			logger::info("-------------");

			myFile.close();
		}

		templates::safe_delete_array<char>(m_pDirData);

		return true;
	}

	// --------------------------------------------------------------------------
	// Function:      test_initNotCompressedDirFileHeader
	// Purpose:       read file that contains only uncompressed TZipDirFileHeader fh
	//                  display fh at screen
	//                File was save using test_saveNotCompressedDirFileHeader
	// Parameters:
	// --------------------------------------------------------------------------
	bool ZipFile::test_initNotCompressedDirFileHeader(const std::string& resFileName) {

		//stringstream memory_stream;
		stringstream ss;

		ss << "ZipFile::test_initNotCompressedDirFileHeader: " << resFileName;
		logger::info(ss);

		/////////////////////////


		TZipDirFileHeader fh;

		ifstream ifs(resFileName,ios::binary);
		ifs.read(reinterpret_cast<char *>(&fh),sizeof(fh));

		ss << "CHECK FH: ";
		logger::info(ss);
		ss << fh;
		logger::info(ss);

		ss << "END CHECK FH";
		logger::info(ss);

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

	// ERROR
	//TZipDirFileHeader* pfh =
	//		reinterpret_cast<TZipDirFileHeader*>(vecCharDec.data(), vecCharDec.size());

	TZipDirFileHeader* pfh =
			reinterpret_cast<TZipDirFileHeader*>(vecCharDec.data());

// OK
//	char* pData = vecCharDec.data();
//	TZipDirFileHeader* pfh = reinterpret_cast<TZipDirFileHeader*>(pData);

	pfh->describeYourself();

	ss << "myTZipDirFileHeader contains:";
	logger::info(ss);
	ss << *pfh;
	logger::info(ss);


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


	// Saves data as compressed file
	void ZipFile::saveCompressed(const std::string& outFileName) {

		stringstream ss;
		//			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));


		path outFilePath{outFileName};
		ofstream ofs{outFilePath};

		ss << "Save compressed: ";

		for (vector<char>::iterator it = fileData.begin(); it != fileData.end(); ++it) {
			//cout << *it;
			ofs << *it;

			ss << *it;
		}
		cout << endl;

		logger::info(ss);


		logger::info("-------------");
	};

	// Saves data as compressed file
	void ZipFile::saveCompressedAll(const std::string& outFileName) {

		stringstream ss;
		//			boost::iostreams::copy(in,boost::iostreams::back_inserter(fileData));


		path outFilePath{outFileName};
		ofstream ofs{outFilePath};

		ss << "Save compressed: ";

		for (vector<char>::iterator it = fileData.begin(); it != fileData.end(); ++it) {
			//cout << *it;
			ofs << *it;

			ss << *it;
		}
		cout << endl;

		logger::info(ss);


		logger::info("-------------");
	};

	// Decompresses data and saves in decompressed file
	void ZipFile::saveNotCompressed(const std::string& outFileName) {
		stringstream ss;

		array_source src{fileData.data(), fileData.size()};
		filtering_istreambuf inDec; //filtering_streambuf<input>

		inDec.push(zlib_decompressor());
		inDec.push(src);

		vector<char> vecCharDec;

		boost::iostreams::copy(inDec,boost::iostreams::back_inserter(vecCharDec));


		path outFilePath{outFileName};
		ofstream ofs{outFilePath};

		ss << "Start decompressed: ";

		for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
			//cout << *it;
			ofs << *it;
			ss << *it;
		}

		cout << endl;

		logger::info(ss);
	};

	void ZipFile::saveNotCompressedAll_111(const std::string& outFileName) {


		stringstream ss;

		array_source src{fileData.data(), fileData.size()};
		filtering_istreambuf inDec; //filtering_streambuf<input>

		inDec.push(zlib_decompressor());
		inDec.push(src);

		vector<char> vecCharDec;

		boost::iostreams::copy(inDec,boost::iostreams::back_inserter(vecCharDec));


		path outFilePath{outFileName};
		//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
		ofstream ofs{outFilePath};

		ss << "Start decompressed: ";

		for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
			//cout << *it;


			// ofs.write(*it);
			ofs << *it;
			ss << *it;
		}


		TZipDirFileHeader fh;
		fh.verMade = 55;
		fh.isCompression = TZipDirFileHeader::Z_NO_COMPRESSION;

		//ofs.write(reinterpret_cast<const char*>(&fh.sig), sizeof fh.sig);

		ofs << fh;

		ofs << endl;

		TZipDirHeader dh;
		dh.dirSize = 77; //???
		dh.nDirEntries = 1;
		dh.isCompression = TZipDirHeader::Z_NO_COMPRESSION;

		ofs << dh;

		ofs << endl;

		cout << endl;

		logger::info(ss);
	};


	void ZipFile::saveNotCompressedAll(const std::string& outFileName) {


		stringstream ss;

		array_source src{fileData.data(), fileData.size()};
		filtering_istreambuf inDec; //filtering_streambuf<input>

		inDec.push(zlib_decompressor());
		inDec.push(src);

		vector<char> vecCharDec;

		boost::iostreams::copy(inDec,boost::iostreams::back_inserter(vecCharDec));


		path outFilePath{outFileName};
		//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
		//		ofstream ofs{outFilePath};
		ofstream ofs(outFilePath,ios::binary);


		ss << "Start decompressed: ";

		for (vector<char>::iterator it = vecCharDec.begin(); it != vecCharDec.end(); ++it) {
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

		ofs.write(reinterpret_cast<char *>(&fh),sizeof(fh));



		TZipDirHeader dh;
		dh.dirSize = 77; //???
		dh.nDirEntries = 1;
		dh.isCompression = TZipDirHeader::Z_NO_COMPRESSION;

		//ofs.write(reinterpret_cast<char *>(&dh),sizeof(dh));

		//		ofs << dh;

		//	ofs << endl;


		cout << endl;

		logger::info(ss);

		ss << "SIZE_OF_FH: " << sizeof(fh);
		logger::info(ss);

	};


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

	};



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
	void ZipFile::test_saveNotCompressedDirFileHeader(const std::string& outFileName) {


		stringstream ss;


		path outFilePath{outFileName};
		//			ofstream ofs{outFilePath, ios::out | ios::app | ios::binary};
		//		ofstream ofs{outFilePath};
		ofstream ofs(outFilePath,ios::binary);


		TZipDirFileHeader fh;
		fh.testInitiation();
	/*
	 * http://en.cppreference.com/w/cpp/io/basic_ostream/write
	 *
	 * basic_ostream& write( const char_type* s, std::streamsize count );
	 */
		ofs.write(reinterpret_cast<char *>(&fh),sizeof(fh));

		logger::info(ss);

		ss << "SIZE_OF_FH: " << sizeof(fh);
		logger::info(ss);

		ss << fh;
		logger::info(ss);

		ofs.close();

	};

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

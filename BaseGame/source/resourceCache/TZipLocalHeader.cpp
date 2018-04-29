#include "TZipLocalHeader.h"
#include "../debugging/Logger.h"

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;
using boost::filesystem::ofstream;

using std::endl;
using std::stringstream;

namespace base_game {
TZipLocalHeader::TZipLocalHeader() {
	logger::info("Create TZipLocalHeader");
	sig = TZipLocalHeader::SIGNATURE;
}

TZipLocalHeader::~TZipLocalHeader() {
	logger::info("Destroy TZipLocalHeader");
}

void TZipLocalHeader::testInitiation() {
	// unsigned long (4)
	sig = TZipLocalHeader::SIGNATURE;
	// unsigned short (2)
	isCompression = TZipLocalHeader::Z_NO_COMPRESSION; // Z_NO_COMPRESSION or Z_DEFLATED
	// unsigned short (2)
	version = 0x1111;
	// unsigned short (2)
	flag = 0x2222;
	// unsigned short (2)
	compression = TZipLocalHeader::Z_NO_COMPRESSION; // Z_NO_COMPRESSION or Z_DEFLATED
	// unsigned short (2)
	modTime = 0x3333;
	// unsigned short (2)
	modDate = 0x4444;
	// unsigned long (4)
	crc32 = 0x55334455;
	// unsigned long (4)
	cSize = 0x66889966;
	// unsigned long (4)
	ucSize = 0x77223377;
	// unsigned short (2)
	fnameLen = 0x8888;         // Filename string follows header.
	// unsigned short (2)
	xtraLen = 0x9999;
}

void TZipLocalHeader::describeYourself() {

	stringstream ss;

	ss << "TZipLocalHeader DescribeYourself";
	logger::info(ss);

	ss << reinterpret_cast<unsigned long>(sig) << endl << endl;

	ss << static_cast<unsigned long>(sig) << endl << endl;

	ss << std::bitset<32>(sig) << endl << endl;

	ss << "%S%" << std::hex << "SIG: " << sig << endl;

	ss << "VERSION: " << version << endl << "FLAG: " << flag << endl
			<< "COMPRESSION: " << compression << endl << "MODTIME: " << modTime
			<< endl << "MODDATE: " << modDate << endl << "CRC32: " << crc32
			<< endl << "CSIZE: " << cSize << endl << "UCSIZE: " << ucSize
			<< endl << "FNAMELEN: " << fnameLen << endl << "XTRALEN " << xtraLen
			<< endl << std::dec << "%E%";

	logger::info(ss);

	logger::info("TZipLocalHeader DescribeYourself END");

}

}

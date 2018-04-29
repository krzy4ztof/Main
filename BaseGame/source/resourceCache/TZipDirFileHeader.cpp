#include "TZipDirFileHeader.h"
#include "../debugging/Logger.h"

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;
#include <sstream>      // std::stringstream

#include <bitset> // bitset
using boost::filesystem::ofstream;
using std::endl;
using std::stringstream;

namespace base_game {
TZipDirFileHeader::TZipDirFileHeader() {
	logger::info("Create TZipDirFileHeader");
	sig = TZipDirFileHeader::SIGNATURE;
}

TZipDirFileHeader::~TZipDirFileHeader() {
	logger::info("Destroy TZipDirFileHeader");
}

void TZipDirFileHeader::describeYourself() {
	stringstream ss;

	ss << "TZipDirFileHeader DescribeYourself";
	logger::info(ss);

	ss << reinterpret_cast<unsigned long>(sig) << endl << endl;

	ss << static_cast<unsigned long>(sig) << endl << endl;

	ss << std::bitset<32>(sig) << endl << endl;

	ss << "%S%" << std::hex << "SIG: " << sig << endl

	<< "ISCOMPRESSION: " << isCompression << endl

	<< "VERMADE: " << verMade << endl

	<< "VERNEEDED: " << verNeeded << endl

	<< "FLAG: " << flag << endl

	<< "COMPRESSION: " << compression << endl << "MODTIME: " << modTime << endl
			<< "MODDATE: " << modDate << endl << "CRC32: " << crc32 << endl
			<< "CSIZE: " << cSize << endl << "UCSIZE: " << ucSize << endl
			<< "FNAMELEN: " << fnameLen << endl << "XTRALEN: " << xtraLen
			<< endl << "CMNTLEN: " << cmntLen << endl << "DISKSTART: "
			<< diskStart << endl << "INTATTR: " << intAttr << endl
			<< "EXTATTR: " << extAttr << endl << "HDROFFSET: " << hdrOffset
			<< endl << std::dec << "%E%";

	logger::info(ss);

	logger::info("TZipDirFileHeader DescribeYourself END");

}

void TZipDirFileHeader::testInitiation() {
	//unsigned long (4)
	sig = TZipDirFileHeader::SIGNATURE;

	//unsigned short (2)
	isCompression = TZipDirFileHeader::Z_NO_COMPRESSION; // Z_NO_COMPRESSION or Z_DEFLATED (Z_NOCOMPRESSION = 0)

	//unsigned short (2)
	verMade = 0x1111;

	//unsigned short
	verNeeded = 0x2222;

	//unsigned short
	flag = 0x3333;

	//unsigned short
	compression = 0x4154;      // COMP_xxxx

	//unsigned short
	modTime = 0x5555;

	//unsigned short
	modDate = 0x6666;

	//unsigned long
	crc32 = 0x77771177;

	//unsigned long
	cSize = 0x88221188;            // Compressed size

	//unsigned long
	ucSize = 0x99334499;           // Uncompressed size

	//unsigned short
	fnameLen = 0x1010;         // Filename string follows header.

	//unsigned short
	xtraLen = 0x2020;          // Extra field follows filename.

	//unsigned short
	cmntLen = 0x3030;          // Comment field follows extra field.

	//unsigned short
	diskStart = 0x4242;

	//unsigned short
	intAttr = 0x5050;

	//unsigned long
	extAttr = 0x61626364;

	//unsigned long
	hdrOffset = 0x71727374;

}

}

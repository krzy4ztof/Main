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

	void TZipDirFileHeader::testInitiation() {
		//unsigned long (4)
		sig = 0x02014b50;

		//unsigned short (2)
		isCompression = TZipDirFileHeader::Z_NO_COMPRESSION;      // Z_NO_COMPRESSION or Z_DEFLATED (Z_NOCOMPRESSION = 0)

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

	ofstream& operator<<(ofstream& ofs, const TZipDirFileHeader& zipDirFileHeader) {

		if (zipDirFileHeader.isCompression == TZipDirFileHeader::Z_NO_COMPRESSION) {

			ofs  << reinterpret_cast<unsigned long>(zipDirFileHeader.sig) << endl << endl;


			ofs << static_cast<unsigned long>(zipDirFileHeader.sig) << endl << endl;

			ofs <<  std::bitset<32>(zipDirFileHeader.sig) << endl << endl;

			ofs << "%S%"
				<< std::hex
				<< "SIG: "
				<< zipDirFileHeader.sig << endl

				<< "ISCOMPRESSION: "
				<< zipDirFileHeader.isCompression << endl

				<< "VERMADE: "
				<< zipDirFileHeader.verMade << endl

				<< "VERNEEDED: "
				<< zipDirFileHeader.verNeeded << endl

				<< "FLAG: "
				<< zipDirFileHeader.flag << endl

				<< "COMPRESSION: "
				<< zipDirFileHeader.compression << endl
				<< zipDirFileHeader.modTime << endl
				<< zipDirFileHeader.modDate << endl
				<< zipDirFileHeader.crc32 << endl
				<< zipDirFileHeader.cSize << endl
				<< zipDirFileHeader.ucSize << endl
				<< zipDirFileHeader.fnameLen << endl
				<< zipDirFileHeader.xtraLen << endl
				<< zipDirFileHeader.cmntLen << endl
				<< zipDirFileHeader.diskStart << endl
				<< zipDirFileHeader.intAttr << endl
				<< zipDirFileHeader.extAttr << endl
				<< zipDirFileHeader.hdrOffset << endl << std::dec
				<< "%E%";
		} else {


		}


		return ofs;
	}

	stringstream& operator<<(stringstream& ss, const TZipDirFileHeader& zipDirFileHeader) {

		if (zipDirFileHeader.isCompression == TZipDirFileHeader::Z_NO_COMPRESSION) {

			ss  << reinterpret_cast<unsigned long>(zipDirFileHeader.sig) << endl << endl;


			ss << static_cast<unsigned long>(zipDirFileHeader.sig) << endl << endl;

			ss <<  std::bitset<32>(zipDirFileHeader.sig) << endl << endl;

			ss
					<< std::hex
					<< "SIG: "
					<< zipDirFileHeader.sig << endl
					<< "ISCOMPRESSION: "
					<< zipDirFileHeader.isCompression << endl
					<< "VERMADE: "
					<< zipDirFileHeader.verMade << endl
					<< "VERNEEDED: "
					<< zipDirFileHeader.verNeeded << endl
					<< "FLAG: "
					<< zipDirFileHeader.flag << endl
					<< "COMPRESSION: "
					<< zipDirFileHeader.compression << endl
					<< "MODTIME: "
					<< zipDirFileHeader.modTime << endl
					<< "MODDATE: "
					<< zipDirFileHeader.modDate << endl
					<< "CRC32: "
					<< zipDirFileHeader.crc32 << endl
					<< "CSIZE: "
					<< zipDirFileHeader.cSize << endl
					<< "UCSIZE: "
					<< zipDirFileHeader.ucSize << endl
					<< "FNAMELEN: "
					<< zipDirFileHeader.fnameLen << endl
					<< "XTRALEN: "
					<< zipDirFileHeader.xtraLen << endl
					<< "CMNTLEN: "
					<< zipDirFileHeader.cmntLen << endl
					<< "DISKSTART: "
					<< zipDirFileHeader.diskStart << endl
					<< "INTATTR: "
					<< zipDirFileHeader.intAttr << endl
					<< "EXTATTR: "
					<< zipDirFileHeader.extAttr << endl
					<< "HROFFSET: "
					<< zipDirFileHeader.hdrOffset << endl << std::dec;
		} else {


		}


		return ss;
	}
}

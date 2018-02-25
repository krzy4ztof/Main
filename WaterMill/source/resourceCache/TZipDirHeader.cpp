#include "TZipDirHeader.h"
#include "../debugging/Logger.h"

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;
using boost::filesystem::ofstream;

using std::endl;
using std::stringstream;

namespace base_game {
TZipDirHeader::TZipDirHeader() {
	logger::info("Create TZipDirHeader");
	sig = TZipDirHeader::SIGNATURE;
}

TZipDirHeader::~TZipDirHeader() {
	logger::info("Destroy TZipDirHeader");
}

/*
 ofstream& operator<<(ofstream& ofs, const TZipDirHeader& zipDirHeader) {

 ofs << "|" << zipDirHeader.sig
 << "|" << zipDirHeader.nDisk
 << "|" << zipDirHeader.nStartDisk
 << "|" << zipDirHeader.nDirEntries
 << "|" << zipDirHeader.totalDirEntries
 << "|" << zipDirHeader.dirSize
 << "|" << zipDirHeader.dirOffset
 << "|" << zipDirHeader.cmntLen;

 return ofs;
 }
 */

void TZipDirHeader::testInitiation() {
	//unsigned long (4)
	sig = TZipDirHeader::SIGNATURE;
	//unsigned short (2)
	isCompression = TZipDirHeader::Z_NO_COMPRESSION; // Z_NO_COMPRESSION or Z_DEFLATED
	//unsigned short (2)
	nDisk = 0x1111;
	//unsigned short (2)
	nStartDisk = 0x2222;
	//unsigned short (2)
	nDirEntries = 0x3333;
	//unsigned short (2)
	totalDirEntries = 0x4444;
	//unsigned long (4)
	dirSize = 0x55112255;
	//unsigned long (4)
	dirOffset = 0x66112266;
	//unsigned short (2)
	cmntLen = 0x7777;

}

void TZipDirHeader::describeYourself() {
	stringstream ss;

	ss << "TZipDirHeader DescribeYourself";
	logger::info(ss);

	//ss << reinterpret_cast<unsigned long>(sig) << endl << endl;

	//ss << static_cast<unsigned long>(sig) << endl << endl;

	//ss << std::bitset<32>(sig) << endl << endl;

	ss << "%S%" << std::hex << "SIG: " << sig << endl

	<< "ISCOMPRESSION: " << isCompression << endl << "NDISK: " << nDisk << endl
			<< "NSTARTDISK: " << nStartDisk << endl << "NDIRENTRIES: "
			<< nDirEntries << endl << "TOTALDIRENTRIES: " << totalDirEntries
			<< endl << "DIRSIZE: " << endl << dirSize << endl << "DIROFFSET: "
			<< endl << dirOffset << endl << "CMTLEN: " << endl << cmntLen <<

			endl << std::dec << "%E%";

	logger::info(ss);

	logger::info("TZipDirHeader DescribeYourself END");

}
}

/*
 ||=== Build: Debug_Linux in Watermill (compiler: GNU GCC Compiler) ===|
 /home/kletki/my_home/prj/git/Main/WaterMill/source/resourceCache/TZipDirHeader.h|24|error: boost::filesystem::ofstream& base_game::TZipDirHeader::operator<<(boost::filesystem::ofstream&, const base_game::TZipDirHeader&) must take exactly one argument|
 /home/kletki/my_home/prj/git/Main/WaterMill/source/resourceCache/TZipDirHeader.cpp|16|error: boost::filesystem::ofstream& base_game::TZipDirHeader::operator<<(boost::filesystem::ofstream&, const base_game::TZipDirHeader&) must take exactly one argument|
 ||=== Build failed: 2 error(s), 0 warning(s) (0 minute(s), 3 second(s)) ===|
 */

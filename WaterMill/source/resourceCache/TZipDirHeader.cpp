#include "TZipDirHeader.h"
#include "../debugging/Logger.h"

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;
using boost::filesystem::ofstream;

namespace base_game {
	TZipDirHeader::TZipDirHeader() {
		logger::info("Create TZipDirHeader");
		sig = TZipDirHeader::SIGNATURE;
	}

	TZipDirHeader::~TZipDirHeader() {
		logger::info("Destroy TZipDirHeader");
	}

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
}

/*
||=== Build: Debug_Linux in Watermill (compiler: GNU GCC Compiler) ===|
/home/kletki/my_home/prj/git/Main/WaterMill/source/resourceCache/TZipDirHeader.h|24|error: ‘boost::filesystem::ofstream& base_game::TZipDirHeader::operator<<(boost::filesystem::ofstream&, const base_game::TZipDirHeader&)’ must take exactly one argument|
/home/kletki/my_home/prj/git/Main/WaterMill/source/resourceCache/TZipDirHeader.cpp|16|error: ‘boost::filesystem::ofstream& base_game::TZipDirHeader::operator<<(boost::filesystem::ofstream&, const base_game::TZipDirHeader&)’ must take exactly one argument|
||=== Build failed: 2 error(s), 0 warning(s) (0 minute(s), 3 second(s)) ===|
*/

#include "TZipLocalHeader.h"
#include "../debugging/Logger.h"

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream; boost::filesystem::path;
using boost::filesystem::ofstream;

namespace base_game {
	TZipLocalHeader::TZipLocalHeader() {
		logger::info("Create TZipLocalHeader");
		sig = TZipLocalHeader::SIGNATURE;
	}

	TZipLocalHeader::~TZipLocalHeader() {
		logger::info("Destroy TZipLocalHeader");
	}

		ofstream& operator<<(ofstream& ofs, const TZipLocalHeader& zipLocalHeader) {

		ofs << "|" << zipLocalHeader.sig
			<< "|" << zipLocalHeader.version
			<< "|" << zipLocalHeader.flag
			<< "|" << zipLocalHeader.compression
			<< "|" << zipLocalHeader.modTime
			<< "|" << zipLocalHeader.modDate
			<< "|" << zipLocalHeader.crc32
			<< "|" << zipLocalHeader.cSize
			<< "|" << zipLocalHeader.ucSize
			<< "|" << zipLocalHeader.fnameLen
			<< "|" << zipLocalHeader.xtraLen;

		return ofs;
	}
}

#ifndef TZIPDIRHEADER_H
#define TZIPDIRHEADER_H

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream;
#include <sstream>      // std::stringstream

#pragma pack(1)
namespace base_game {
class TZipDirHeader {
public:
	TZipDirHeader();
	virtual ~TZipDirHeader();
	enum {
		SIGNATURE = 0xC3C3C3C3,
		//SIGNATURE = 0x06054b50,
		BASE_GAME_Z_NO_COMPRESSION = 0, //Conflict names with Z_NO_COMPRESSION defined in <zlib.h>
		BASE_GAME_Z_DEFLATED = 1 //Conflict names with Z_DEFLATED defined in <zlib.h>
	};
	unsigned long sig = 0;
	unsigned short isCompression = 0; // BASE_GAME_Z_NO_COMPRESSION or BASE_GAME_Z_DEFLATED
	unsigned short nDisk = 0;
	unsigned short nStartDisk = 0;
	unsigned short nDirEntries = 0;
	unsigned short totalDirEntries = 0;
	unsigned long dirSize = 0;
	unsigned long dirOffset = 0;
	unsigned short cmntLen = 0;

	//friend boost::filesystem::ofstream& operator<<(boost::filesystem::ofstream& ofs, const TZipDirHeader& zipDirHeader);

	//friend std::stringstream& operator<<(std::stringstream& ss, const TZipDirHeader& zipDirHeader);

	void testInitiation();
	void describeYourself();

protected:

private:
};
}
#pragma pack()

#endif // TZIPDIRHEADER_H

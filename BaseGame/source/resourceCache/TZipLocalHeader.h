#ifndef TZIPLOCALHEADER_H
#define TZIPLOCALHEADER_H

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream;

#pragma pack(1)
namespace base_game {
class TZipLocalHeader {
public:
	TZipLocalHeader();
	virtual ~TZipLocalHeader();

	enum {
		SIGNATURE = 0xA1A1A1A1,
		//SIGNATURE = 0x04034b50,
		BASE_GAME_Z_NO_COMPRESSION = 0, //Conflict names with Z_NO_COMPRESSION deined in <zlib.h>
		BASE_GAME_Z_DEFLATED = 1 //Conflict names with Z_DEFLATED defined in <zlib.h>
	};
	unsigned long sig = 0;
	unsigned short isCompression = 0; //BASE_GAME_Z_NO_COMPRESSION or BASE_GAME_Z_DEFLATED
	unsigned short version = 0;
	unsigned short flag = 0;
	unsigned short compression = 0; //BASE_GAME_Z_NO_COMPRESSION or BASE_GAME_Z_DEFLATED
	unsigned short modTime = 0;
	unsigned short modDate = 0;
	unsigned long crc32 = 0;
	unsigned long cSize = 0;
	unsigned long ucSize = 0;
	unsigned short fnameLen = 0;         // Filename string follows header.
	unsigned short xtraLen = 0;          // Extra field follows filename.

	//friend boost::filesystem::ofstream& operator<<(boost::filesystem::ofstream& ofs, const TZipLocalHeader& zipLocalHeader);

	void testInitiation();
	void describeYourself();

protected:

private:
};
}
#pragma pack()

#endif // TZIPLOCALHEADER_H

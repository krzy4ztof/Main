#ifndef TZIPDIRFILEHEADER_H
#define TZIPDIRFILEHEADER_H

#include <boost/filesystem/fstream.hpp> //boost::filesystem::ofstream;
#include <sstream>      // std::stringstream

#pragma pack(1)
namespace base_game {
class TZipDirFileHeader {
public:
	TZipDirFileHeader();
	virtual ~TZipDirFileHeader();

	enum {
		SIGNATURE = 0xB2B2B2B2,
		//SIGNATURE = 0x02014b50,
		Z_NO_COMPRESSION = 0,
		Z_DEFLATED = 1
	};
	// unsigned long - 4 bytes
	// unsigned short - 2 bytes
	//6x4 = 24 bytes
	//12x2 = 24 bytes
	// 48 bytes

	// 36 + 36 + 8 = 80
	unsigned long sig = 0;
	unsigned short isCompression = 0;      // Z_NO_COMPRESSION or Z_DEFLATED
	unsigned short verMade = 0;
	unsigned short verNeeded = 0;
	unsigned short flag = 0;
	unsigned short compression = 0;      // COMP_xxxx
	unsigned short modTime = 0;
	unsigned short modDate = 0;
	unsigned long crc32 = 0;
	unsigned long cSize = 0;            // Compressed size
	unsigned long ucSize = 0;           // Uncompressed size
	unsigned short fnameLen = 0;         // Filename string follows header.
	unsigned short xtraLen = 0;          // Extra field follows filename.
	unsigned short cmntLen = 0;          // Comment field follows extra field.
	unsigned short diskStart = 0;
	unsigned short intAttr = 0;
	unsigned long extAttr = 0;
	unsigned long hdrOffset = 0;

	//friend boost::filesystem::ofstream& operator<<(boost::filesystem::ofstream& ofs, const TZipDirFileHeader& zipDirFileHeader);
	//friend std::stringstream& operator<<(std::stringstream& ss, const TZipDirFileHeader& zipDirFileHeader);

	char *GetName() const {
		return (char *) (this + 1);
	}
	char *GetExtra() const {
		return GetName() + fnameLen;
	}
	char *GetComment() const {
		return GetExtra() + xtraLen;
	}

	void testInitiation();
	void describeYourself();

protected:

private:
};
}
#pragma pack()

#endif // TZIPDIRFILEHEADER_H

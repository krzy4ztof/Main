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
				SIGNATURE = 0x06054b50,
				Z_NO_COMPRESSION = 0,
				Z_DEFLATED = 1
			};
			unsigned long   sig = 0;
			unsigned short    isCompression = 0;      // Z_NO_COMPRESSION or Z_DEFLATED
			unsigned short    nDisk = 0;
			unsigned short    nStartDisk = 0;
			unsigned short    nDirEntries = 0;
			unsigned short    totalDirEntries = 0;
			unsigned long   dirSize = 0;
			unsigned long   dirOffset = 0;
			unsigned short    cmntLen = 0;

			friend boost::filesystem::ofstream& operator<<(boost::filesystem::ofstream& ofs, const TZipDirHeader& zipDirHeader);

			//friend std::stringstream& operator<<(std::stringstream& ss, const TZipDirHeader& zipDirHeader);

		protected:

		private:
	};
}
#pragma pack()

#endif // TZIPDIRHEADER_H

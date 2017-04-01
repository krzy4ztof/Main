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
				SIGNATURE = 0x04034b50,
				Z_NO_COMPRESSION = 0,
				Z_DEFLATED = 1
			};
			unsigned long   sig = 0;
			unsigned short    isCompression = 0;      // Z_NO_COMPRESSION or Z_DEFLATED
			unsigned short    version = 0;
			unsigned short    flag = 0;
			unsigned short    compression = 0;      // Z_NO_COMPRESSION or Z_DEFLATED
			unsigned short    modTime = 0;
			unsigned short    modDate = 0;
			unsigned long   crc32 = 0;
			unsigned long   cSize = 0;
			unsigned long   ucSize = 0;
			unsigned short    fnameLen = 0;         // Filename string follows header.
			unsigned short    xtraLen = 0;          // Extra field follows filename.

			friend boost::filesystem::ofstream& operator<<(boost::filesystem::ofstream& ofs, const TZipLocalHeader& zipLocalHeader);
		protected:

		private:
	};
}
#pragma pack()

#endif // TZIPLOCALHEADER_H

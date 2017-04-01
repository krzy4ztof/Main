#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <string> //string
#include <vector> //vector


namespace base_game {
	class ZipFile {
		public:
			ZipFile();
			virtual ~ZipFile();

			bool init(const std::string& resFileName);
			bool temp_init_1(const std::string& resFileName);
			bool temp_init_2(const std::string& resFileName);

			bool readFile(int i, void *pBuf);

			bool initCompressed(const std::string& resFileName);
			bool initNotCompressed(const std::string& resFileName);

			void saveCompressed(const std::string& outFileName);
			void saveNotCompressed(const std::string& outFileName);

			void test_saveCompressedDirFileHeader(const std::string& outFileName); // todo
            bool test_initCompressedDirFileHeader(const std::string& resFileName); // todo

			void test_saveNotCompressedDirFileHeader(const std::string& outFileName); // ok
            bool test_initNotCompressedDirFileHeader(const std::string& resFileName); // ok



            void saveCompressedAll(const std::string& outFileName);
			void saveNotCompressedAll(const std::string& outFileName);
			void saveNotCompressedAll_111(const std::string& outFileName);



		protected:

		private:
//		    TZipDirHeader;
 //    TZipDirFileHeader;
  //   TZipLocalHeader;

            char *m_pDirData;	// Raw data buffer.
            std::vector <char> fileData;


	};
}
#endif // ZIPFILE_H

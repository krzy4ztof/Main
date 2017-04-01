#ifndef RESOURCEZIPFILE_H
#define RESOURCEZIPFILE_H

#include "IResourceFile.h"
#include "ZipFile.h"

#include <string> //string

namespace base_game {
	class ResourceZipFile : public IResourceFile {
		public:
			ResourceZipFile(const std::string fileName);
			virtual ~ResourceZipFile();
			virtual bool vOpen();

		protected:

		private:
			ZipFile *m_pZipFile;
			std::string m_resFileName;
	};
}
#endif // RESOURCEZIPFILE_H

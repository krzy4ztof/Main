#ifndef RESOURCEZIPFILE_H
#define RESOURCEZIPFILE_H

#include "IResourceFile.h"
#include <string> //string

namespace base_game {
	class ResourceZipFile : public IResourceFile {
		public:
			ResourceZipFile(const std::string fileName);
			virtual ~ResourceZipFile();

		protected:

		private:
	};
}
#endif // RESOURCEZIPFILE_H

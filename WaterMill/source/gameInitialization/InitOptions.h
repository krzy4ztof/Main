#ifndef INITOPTIONS_H
#define INITOPTIONS_H

#include <string> // string

namespace watermill {
	class InitOptions {
		public:
			InitOptions();
			virtual ~InitOptions();
			std::string getResourcesFolder();
		protected:

		private:
			const static std::string INIT_FILENAME;
			const static std::string RESOURCES_FOLDER;

			std::string resourcesFolder;

			void checkFile(const std::string &filename);
			void readFile(const std::string &filename);
	};
}
#endif // INITOPTIONS_H

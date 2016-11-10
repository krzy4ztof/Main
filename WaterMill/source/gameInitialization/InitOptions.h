#ifndef INITOPTIONS_H
#define INITOPTIONS_H

#include <string> // string

namespace base_game {
	class InitOptions {
		public:
			InitOptions();
			virtual ~InitOptions();
			std::string getAssetsFolder();
			std::string getGameFolder();
		protected:

		private:
			const static std::string INIT_FILENAME;
			const static std::string ASSETS_FOLDER;
			const static std::string GAME_FOLDER;


			std::string assetsFolder;
			std::string gameFolder;

			void checkFile(const std::string &filename);
			void readFile(const std::string &filename);
	};
}
#endif // INITOPTIONS_H

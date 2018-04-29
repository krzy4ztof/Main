#ifndef GAMEMESSAGES_H
#define GAMEMESSAGES_H

#include <string> // string

namespace base_game {
	class GameMessages {
		public:
			const static std::string STRINGS_FOLDER;
			const static std::string MESSAGE_DOMAIN;

			GameMessages(std::string assetsFolder, std::string language);
			virtual ~GameMessages();

			void testMessages();

		protected:

		private:
			//  std::string assetsFolder;
			//  std::string language;
	};
}
#endif // GAMEMESSAGES_H

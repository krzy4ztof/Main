#ifndef GAMEMESSAGES_H
#define GAMEMESSAGES_H

#include <string> // string

namespace watermill {
	class GameMessages {
		public:
			GameMessages(std::string assetsFolder, std::string language);
			virtual ~GameMessages();

			void testMessages();

		protected:

		private:
			//  std::string assetsFolder;
			//  std::string language;
	};

	namespace game_messages {
		void safe_delete(GameMessages* p);
	};
}
#endif // GAMEMESSAGES_H

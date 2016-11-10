#ifndef WATERMILLGAME_H
#define WATERMILLGAME_H

#include "../gameInitialization/GameCodeApp.h"
#include "../gameLogic/BaseGameLogic.h"
#include "../resourceCache/ResourceCache.h"

#include <string>



namespace watermill {
	class WatermillGame : public base_game::GameCodeApp {
		public:
			const static std::string GAME_APP_DIRECTORY;

			WatermillGame();
			virtual ~WatermillGame();
			virtual std::string vGetGameAppDirectory();

		protected:
			virtual base_game::BaseGameLogic *createGameAndView(base_game::ResourceCache* resourceCache);
		private:
	};
}
#endif // WATERMILLGAME_H

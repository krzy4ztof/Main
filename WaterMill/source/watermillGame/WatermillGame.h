#ifndef WATERMILLGAME_H
#define WATERMILLGAME_H

#include "../gameInitialization/GameCodeApp.hpp"
#include "../gameLogic/BaseGameLogic.h"

#include <string>

namespace watermill {
	class WatermillGame : public GameCodeApp {
		public:
			const static std::string GAME_APP_DIRECTORY;

			WatermillGame();
			virtual ~WatermillGame();
			virtual std::string vGetGameAppDirectory();

		protected:
			virtual BaseGameLogic *createGameAndView();
		private:
	};
}
#endif // WATERMILLGAME_H

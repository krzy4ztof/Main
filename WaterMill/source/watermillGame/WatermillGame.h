#ifndef WATERMILLGAME_H
#define WATERMILLGAME_H

#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"

//#include <gameInitialization/GameCodeApp.h>
//#include <gameLogic/BaseGameLogic.h>
//#include <resourceCache/ResourceCache.h>

//#include <GameCodeApp.h>
//#include <gameLogic/BaseGameLogic.h>
//#include <resourceCache/ResourceCache.h>


/*
#include "../gameInitialization/GameCodeApp.h"
#include "../gameLogic/BaseGameLogic.h"
#include "../resourceCache/ResourceCache.h"
 */

#include <string>
#include <memory> // shared_ptr, weak_ptr


namespace watermill {
	class WatermillGame : public base_game::GameCodeApp {
		public:
			const static std::string GAME_APP_DIRECTORY;

			WatermillGame();
			virtual ~WatermillGame();
			virtual std::string vGetGameAppDirectory();

		protected:
	virtual base_game::BaseGameLogic* createGameAndView(
			std::shared_ptr<base_game::ResourceCache> resourceCache);
		private:
	};
}
#endif // WATERMILLGAME_H

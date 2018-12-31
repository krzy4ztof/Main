#ifndef WATERMILLLOGIC_H
#define WATERMILLLOGIC_H

#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"

//#include <gameLogic/BaseGameLogic.h>
//#include <gameLogic/BaseGameState.h>





namespace watermill {
	class WatermillLogic : public base_game::BaseGameLogic {
		public:
			WatermillLogic();
			virtual ~WatermillLogic();

			virtual void vChangeState(base_game::BaseGameState newState);
	virtual void describeYourself();

		protected:

		private:
	};
}
#endif // WATERMILLLOGIC_H

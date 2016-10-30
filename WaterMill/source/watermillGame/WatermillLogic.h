#ifndef WATERMILLLOGIC_H
#define WATERMILLLOGIC_H

#include "../gameLogic/BaseGameLogic.h"
#include "../gameLogic/BaseGameState.h"


namespace watermill {
	class WatermillLogic : public base_game::BaseGameLogic {
		public:
			WatermillLogic();
			virtual ~WatermillLogic();

			virtual void vChangeState(base_game::BaseGameState newState);

		protected:

		private:
	};
}
#endif // WATERMILLLOGIC_H

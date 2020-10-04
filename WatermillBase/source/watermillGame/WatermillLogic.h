#ifndef WATERMILLLOGIC_H
#define WATERMILLLOGIC_H

#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"

//#include <gameLogic/BaseGameLogic.h>
//#include <gameLogic/BaseGameState.h>
#include <memory> // shared_ptr, weak_ptr

namespace watermill_base {
class WatermillLogic: public base_game::BaseGameLogic {
public:
	WatermillLogic(std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer,
			std::shared_ptr<base_game::GameMessages> gameMessages);
	virtual ~WatermillLogic();

	virtual void vChangeState(base_game::BaseGameState newState);
	virtual void describeYourself();

protected:
	std::shared_ptr<base_game::GameMessages> gameMessages;

private:
};
}
#endif // WATERMILLLOGIC_H

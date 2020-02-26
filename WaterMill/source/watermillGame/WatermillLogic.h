#ifndef WATERMILLLOGIC_H
#define WATERMILLLOGIC_H

#include "../../../BaseGame/source/gameLogic/BaseGameState.h"
#include "../../../BaseGame/source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"

//#include <gameLogic/BaseGameLogic.h>
//#include <gameLogic/BaseGameState.h>
#include <memory> // shared_ptr, weak_ptr

namespace watermill {
class WatermillLogic: public base_game::BaseGameLogic {
public:
	WatermillLogic(std::shared_ptr<base_game::OpenGLRenderer> openGLRenderer);
	virtual ~WatermillLogic();

	virtual void vChangeState(base_game::BaseGameState newState);
	virtual void describeYourself();

protected:

private:
};
}
#endif // WATERMILLLOGIC_H

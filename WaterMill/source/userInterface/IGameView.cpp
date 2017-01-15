#include "IGameView.h"
#include "../debugging/Logger.h"

namespace base_game {
	IGameView::~IGameView() {
		logger::info("Destroy IGameView");
	}
}

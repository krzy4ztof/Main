#ifndef BASEGAMESTATE_H
#define BASEGAMESTATE_H

namespace base_game {
enum BaseGameState {
	/*
	 BGS_Invalid,
	 BGS_Initializing,
	 BGS_MainMenu,
	 BGS_WaitingForPlayers,
	 BGS_LoadingGameEnvironment,
	 BGS_WaitingForPlayersToLoadEnvironment,*/
	initializing,
	spawningPlayersActors,
	running,
	showQuitMsgBox,
	confirmQuitMsgBox,
	cancelQuitMsgBox,
	tempActivateWatermillHumanView,
	tempActivateMainMenuView,
	tempActivateFiguresView,
	tempActivateJpegView,
	tempActivateFontsView,
	tempActivatePngView,
	tempActivateCombinedView
};
}

#endif // BASEGAMESTATE_H

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GameCodeApp.h
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 20:15
 */

#ifndef GAMECODEAPP_H
#define GAMECODEAPP_H

#include "DataFiles.h"
#include "AudioSystem.h"
#include "VideoSystem.h"
#include "InitOptions.h"
#include "DebuggingOptions.h"
#include "PlayerOptions.h"
#include "GameMessages.h"

#include "../resourceCache/ResourceCache.h"
#include "../luaScripting/LuaStateManager.h"
#include "../eventManager/EventManager.h"
#include "../gameLogic/BaseGameLogic.h"

#include <string>

namespace watermill {

	class GameCodeApp {
		public:
			const static std::string GAME_PROCESS_NAME;
			const static std::string DEBUG_OPTIONS_XML;
			const static std::string PLAYER_OPTIONS_XML;
			const static std::string ASSETS_ZIP;

			GameCodeApp();
			GameCodeApp(const GameCodeApp& orig);
			virtual ~GameCodeApp();

			bool initAllOptions();
			bool initInstance();
			void mainLoop();
			void onClose();

			// GameCode Specific Stuff
			BaseGameLogic *m_pGame;

			// You must define these functions to initialize your game.
			virtual BaseGameLogic *createGameAndView()=0;
			virtual std::string vGetGameAppDirectory()=0;


		private:
			static const int MEGABYTE = 1024 * 1024;

			InitOptions *initOptions;
			PlayerOptions *playerOptions;
			GameMessages *gameMessages;
			LuaStateManager *luaStateManager;
			EventManager *eventManager;
			DebuggingOptions *debuggingOptions;
			ResourceCache *resourceCache;
			DataFiles *dataFiles;
			AudioSystem *audioSystem;
			VideoSystem *videoSystem;

			std::string saveGameDirectory;
	};

    namespace game_code_app {
		void safe_delete(GameCodeApp* p);
	};
}
#endif /* GAMECODEAPP_H */


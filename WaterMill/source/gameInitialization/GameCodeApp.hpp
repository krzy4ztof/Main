/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GameCodeApp.hpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 20:15
 */

#ifndef GAMECODEAPP_HPP
#define GAMECODEAPP_HPP

#include "DataFiles.hpp"
#include "AudioSystem.hpp"
#include "VideoSystem.hpp"
#include "InitOptions.h"
#include "DebuggingOptions.h"
#include "PlayerOptions.h"
#include "GameMessages.h"

#include "../resourceCache/ResourceCache.h"
#include "../luaScripting/LuaStateManager.h"


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

			bool initInstance();
			bool initInstanceShortDebug();
		private:
			static const int MEGABYTE = 1024 * 1024;

			InitOptions *initOptions;
			PlayerOptions *playerOptions;
			GameMessages *gameMessages;
			LuaStateManager *luaStateManager;
			DebuggingOptions *debuggingOptions;
			ResourceCache *resourceCache;
			DataFiles *dataFiles;
			AudioSystem *audioSystem;
			VideoSystem *videoSystem;
	};
}
#endif /* GAMECODEAPP_HPP */


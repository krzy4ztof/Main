/*
    To change this license header, choose License Headers in Project Properties.
    To change this template file, choose Tools | Templates
    and open the template in the editor.
*/

/*
    File:   GameCodeApp.cpp
    Author: Krzysztof

    Created on 30 kwietnia 2016, 20:15
*/

#include "GameCodeApp.h"
#include<iostream> // cout

#include "Macros.h"
#include "DataFiles.h"
#include "AudioSystem.h"
#include "VideoSystem.h"
#include "ErrorCode.h"

#include "SystemCalls.h"
#include "InitOptions.h"
#include "DebuggingOptions.h"
#include "../resourceCache/ResourceCache.h"
#include "../resourceCache/IResourceFile.h"
#include "../resourceCache/ResourceZipFile.h"
#include "../resourceCache/XmlResourceLoader.h"
#include "../gameLogic/BaseGameLogic.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using std::cout;
using std::endl;
using std::stringstream;

namespace base_game {

	const string GameCodeApp::GAME_PROCESS_NAME = "watermill";
	const string GameCodeApp::DEBUG_OPTIONS_XML = "debugOptions.xml";
	const string GameCodeApp::PLAYER_OPTIONS_XML = "playerOptions.xml";

	const string GameCodeApp::ASSETS_ZIP = "assets.zip";

	GameCodeApp::GameCodeApp() {
		logger::info("Create GameCodeApp");

		initOptions = nullptr;
		playerOptions = nullptr;
		debuggingOptions = nullptr;

		resourceCache = nullptr;

		gameMessages = nullptr;
		luaStateManager = nullptr;
		eventManager = nullptr;
		dataFiles = nullptr;
		audioSystem = nullptr;
		videoSystem = nullptr;

		saveManager = nullptr;

	}

	GameCodeApp::GameCodeApp ( const GameCodeApp& orig ) {
	}

	GameCodeApp::~GameCodeApp() {
		logger::info("Destroy GameCodeApp");
		onClose();
	}

	bool GameCodeApp::initAllOptions() {
		bool returnCode = true;

		try {
			initOptions = new InitOptions;

			playerOptions = new PlayerOptions;
			string playerOptionsFilePath = initOptions->getGameFolder() + PLAYER_OPTIONS_XML;
			playerOptions->load(playerOptionsFilePath);

			// Load programmer's options for debugging purposes
			debuggingOptions = new DebuggingOptions;
			string debugFilePath = initOptions->getGameFolder() + DEBUG_OPTIONS_XML;
			debuggingOptions->load(debugFilePath);
		} catch ( ErrorCode& error ) {
			error.informUser();
			returnCode = false;
		}

		return returnCode;
	}

	bool GameCodeApp::initInstance() {
		bool returnCode = true;
		SystemCalls systemCalls;
#ifndef _DEBUG

		if ( !systemCalls.isOnlyInstance ( GameCodeApp::GAME_PROCESS_NAME ) ) {
			logger::warning("There is another process running");
			return false;
		}

#endif
		// Check for adequate machine resources.
		bool resourceCheck = false;

		while ( !resourceCheck ) {

			//			const DWORDLONG physicalRAM = 512 * MEGABYTE;
			//			const DWORDLONG virtualRAM = 1024 * MEGABYTE;
			//			const DWORDLONG diskSpace = 10 * MEGABYTE;

			//const unsigned long long physicalRAM = 512 * MEGABYTE;
			//const unsigned long long virtualRAM = 1024 * MEGABYTE;
			const unsigned long long physicalRAM = 1 * MEGABYTE;
			const unsigned long long virtualRAM = 1 * MEGABYTE;


			const unsigned long long diskSpace = 10 * MEGABYTE;

			if ( !systemCalls.checkHardDisk ( diskSpace ) ) {
				return false;
			}

			//const DWORD minCpuSpeed = 1300; // 1.3Ghz
			//DWORD thisCPU = systemCalls.readCPUSpeed();
			//const unsigned long minCpuSpeed = 1300; // 1.3Ghz
			const unsigned long minCpuSpeed = 900; // 0.9Ghz

			unsigned long thisCPU = systemCalls.readCPUSpeed();

			stringstream ss;
			ss << "CPU speed needed: " << minCpuSpeed << " [MHz], CPU speed available: " << thisCPU << " [MHz]";
			logger::trace(ss);

			if ( thisCPU < minCpuSpeed ) {
				logger::warning("GetCPUSpeed reports CPU is too slow for this game.");
				return false;
			}

			if ( !systemCalls.checkMemory ( physicalRAM, virtualRAM ) ) {
				return false;
			}

			resourceCheck = true;
		}

		IResourceFile *zipFile = new ResourceZipFile(ASSETS_ZIP);
		resourceCache = new ResourceCache(initOptions->getAssetsFolder(),50,zipFile);
		resourceCache->registerLoader(xml_resource_loader::createXmlResourceLoader());

		try {
			gameMessages = new GameMessages(initOptions->getAssetsFolder(), playerOptions->getOption(playerOptions->LANGUAGE));
			gameMessages->testMessages();

			luaStateManager = new LuaStateManager(initOptions->getAssetsFolder());
			luaStateManager->testLua("test.lua");

			eventManager = new EventManager();

			dataFiles = new DataFiles;
			audioSystem = new AudioSystem;
			videoSystem = new VideoSystem;

			logger::trace("videoSystem++++");

			// initialize the directory location you can store save game files
			//_tcscpy_s(m_saveGameDirectory, GetSaveGameDirectory(GetHwnd(), VGetGameAppDirectory()));
			//string* gameAppDir =

			saveManager = new SaveManager();
			string gameAppDirectory = vGetGameAppDirectory();

			stringstream ss;
			ss << "saveGame: " << gameAppDirectory;
			logger::info(ss);

			string userProfilePath = systemCalls.getUserProfilePath();

			ss << "userProfilePathStr: " << userProfilePath;
			logger::info(ss);


			saveManager->init(userProfilePath, gameAppDirectory);

			videoSystem->startFreeGlut(GAME_PROCESS_NAME);

			logger::trace("createGameAndView++++");

			m_pGame = createGameAndView(resourceCache);

			resourceCache->preLoad("*.jpg");

			/*
						bool done = false;
						logger::trace("Main loop+++");

						videoSystem->startFreeGlutMainLoop();
						while ( !done ) {
							// Main loop

							done = true;
						}
			*/

		} catch ( ErrorCode& error ) {
			error.informUser();
			returnCode = false;
		}
		return ( returnCode );
	}

	void GameCodeApp::mainLoop() {
		bool done = false;
		logger::trace("Main loop+++");

		//TODO: remove tempCreateActors
		//m_pGame->tempCreateActors();
		m_pGame->tempTestActors();

		videoSystem->startFreeGlutMainLoop();

		while ( !done ) {
			// Main loop

			done = true;
		}

	}

	void GameCodeApp::onClose() {

		base_game_logic::safe_delete(m_pGame);
		// gameView
		save_manager::safe_delete(saveManager);
		video_system::safe_delete(videoSystem);
		audio_system::safe_delete(audioSystem);
		data_files::safe_delete(dataFiles);
		event_manager::safe_delete(eventManager);

		lua_state_manager::safe_delete(luaStateManager);
		game_messages::safe_delete(gameMessages);


		resource_cache::safe_delete(resourceCache);
		//IResourceFile
		debugging_options::safe_delete(debuggingOptions);
		player_options::safe_delete(playerOptions);
		init_options::safe_delete(initOptions);

	}

	namespace game_code_app {
		void safe_delete(GameCodeApp* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}
}


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

#include "GameCodeApp.hpp"
#include<iostream> // cout

#include "Macros.hpp"
#include "DataFiles.hpp"
#include "AudioSystem.hpp"
#include "VideoSystem.hpp"
#include "ErrorCode.hpp"

#include "SystemCalls.hpp"
#include "InitOptions.h"
#include "DebuggingOptions.h"
#include "../resourceCache/ResourceCache.h"
#include "../resourceCache/IResourceFile.h"
#include "../resourceCache/ResourceZipFile.h"

#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream, std::stringbuf

using std::string;
using std::cout;
using std::endl;
using std::stringstream;

namespace watermill {

	const string GameCodeApp::GAME_PROCESS_NAME = "watermill";
	const string GameCodeApp::DEBUG_OPTIONS_XML = "debugOptions.xml";
	const string GameCodeApp::PLAYER_OPTIONS_XML = "playerOptions.xml";

	const string GameCodeApp::ASSETS_ZIP = "assets.zip";

	GameCodeApp::GameCodeApp() {

		initOptions = NULL;
		debuggingOptions = NULL;

		resourceCache = NULL;
		dataFiles = NULL;
		audioSystem = NULL;
		videoSystem = NULL;

	}

	GameCodeApp::GameCodeApp ( const GameCodeApp& orig ) {
	}

	GameCodeApp::~GameCodeApp() {
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
			const unsigned long minCpuSpeed = 1300; // 1.3Ghz
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
		resourceCache = new ResourceCache(50,zipFile);

		try {
			initOptions = new InitOptions;


			playerOptions = new PlayerOptions;
			string playerOptionsFilePath = initOptions->getGameFolder() + PLAYER_OPTIONS_XML;
			playerOptions->load(playerOptionsFilePath);


			logger::trace("init game messages");
			gameMessages = new GameMessages(initOptions->getAssetsFolder(), playerOptions->getOption(playerOptions->LANGUAGE));

			logger::trace("test game messages");
			gameMessages->testMessages();

			logger::trace("end game messages");

			luaStateManager = new LuaStateManager(initOptions->getAssetsFolder());
			luaStateManager->testLua("test.lua");

			eventManager = new EventManager();

			// Load programmer's options for debugging purposes
			debuggingOptions = new DebuggingOptions;

			//C:\home\myImportantFiles\projects\git\Main\WaterMill\media
			//C:\home\myImportantFiles\projects\git\Main\WaterMill\settings\codeblocks\Watermill
			//debuggingOptions.load("..\\..\\..\\media\\debugOptions.xml"); // OK
			//			debuggingOptions->load("../../../media/debugOptions.xml");

			logger::trace("debuggingOptions+++++");

			string debugFilePath = initOptions->getGameFolder() + DEBUG_OPTIONS_XML;
			logger::trace("debuggingOptions+++++2");

			debuggingOptions->load(debugFilePath);
			logger::trace("debuggingOptions+++++3");

			dataFiles = new DataFiles;
			audioSystem = new AudioSystem;
			videoSystem = new VideoSystem;

			logger::trace("videoSystem++++");

			// initialize the directory location you can store save game files
			//_tcscpy_s(m_saveGameDirectory, GetSaveGameDirectory(GetHwnd(), VGetGameAppDirectory()));
			//string* gameAppDir =

			saveGameDirectory = vGetGameAppDirectory();

			stringstream ss;
			ss << "saveGame: " << saveGameDirectory;
			logger::trace(ss);

			systemCalls.getSaveGameFolderPath();
			videoSystem->startFreeGlut(GAME_PROCESS_NAME);

			logger::trace("createGameAndView++++");

			m_pGame = createGameAndView();


			bool done = false;
			logger::trace("Main loop+++");

			videoSystem->startFreeGlutMainLoop();
			while ( !done ) {
				// Main loop

				done = true;
			}


		} catch ( ErrorCode& error ) {
			error.informUser();
			returnCode = false;
		}

		video_system::safe_delete ( videoSystem );
		audio_system::safe_delete ( audioSystem );
		data_files::safe_delete ( dataFiles );
		lua_state_manager::safe_delete(luaStateManager);
		event_manager::safe_delete(eventManager);

		debugging_options::safe_delete ( debuggingOptions );

		game_messages::safe_delete(gameMessages);
		player_options::safe_delete(playerOptions);
		init_options::safe_delete ( initOptions );

		return ( returnCode );
	}
}


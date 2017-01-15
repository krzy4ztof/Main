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
#include "../utilities/Templates.h"

#include <sstream>      // std::stringstream

using std::string;
using std::cout;
using std::endl;
using std::stringstream;

namespace base_game {
	GameCodeApp* g_pApp = nullptr;
	//g_pApp = nullptr;


	const string GameCodeApp::GAME_PROCESS_NAME = "watermill";
	const string GameCodeApp::DEBUG_OPTIONS_XML = "debugOptions.xml";
	const string GameCodeApp::PLAYER_OPTIONS_XML = "playerOptions.xml";

	const string GameCodeApp::ASSETS_ZIP = "assets.zip";

	GameCodeApp::GameCodeApp() {
		logger::trace("Create GameCodeApp");
		g_pApp = this;

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

		m_bQuitting = false;

		m_HasModalDialog = 0;

	}

	/*
	GameCodeApp::GameCodeApp ( const GameCodeApp& orig ) {
		logger::trace("Create GameCodeApp");
		g_pApp = this;
	}*/

	GameCodeApp::~GameCodeApp() {
		onClose();
		logger::trace("Destroy GameCodeApp");
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
			logger::trace(ss);

			string userProfilePath = systemCalls.getUserProfilePath();

			ss << "userProfilePathStr: " << userProfilePath;
			logger::trace(ss);


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
		m_pGame->tempAddViews();
		m_pGame->tempTestProcessManager();

		videoSystem->startFreeGlutMainLoop();

		while ( !done ) {
			// Main loop
			done = true;
		}

	}

	bool GameCodeApp::isQuitting() {
		return m_bQuitting;
	}

	bool GameCodeApp::hasModalDialog() {
		return m_HasModalDialog!=0;
	}

	void  GameCodeApp::onUpdateGame( double fTime, float fElapsedTime) { //, void* pUserContext  )
		if (hasModalDialog()) {
			// don't update the game if a modal dialog is up.
			return;
		}

		if (isQuitting()) {
			// TODO:
			//PostMessage(g_pApp->GetHwnd(), WM_CLOSE, 0, 0);
			logger::info("GameCodeApp::onUpdateGame - isQuitting");
		}

		//if (g_pApp->m_pGame)
		if (m_pGame)

		{
			/*
			      IEventManager::Get()->VUpdate(20); // allow event queue to process for up to 20 ms

				if (g_pApp->m_pBaseSocketManager)
					g_pApp->m_pBaseSocketManager->DoSelect(0);	// pause 0 microseconds


				g_pApp->m_pGame->VOnUpdate(float(fTime), fElapsedTime);
			*/

			m_pGame->vOnUpdate(float(fTime), fElapsedTime);

		}
	}

	void  GameCodeApp::onFrameRender( double fTime, float fElapsedTime) { //, void* pUserContext  )
		m_pGame->onFrameRender(fTime,fElapsedTime	);

		// TODO:
		// m_pGame->VRenderDiagnostics();
	}

	void GameCodeApp::onClose() {

		templates::safe_delete<BaseGameLogic>(m_pGame);
		// gameView
		templates::safe_delete<SaveManager>(saveManager);
		templates::safe_delete<VideoSystem>(videoSystem);
		templates::safe_delete<AudioSystem>(audioSystem);
		templates::safe_delete<DataFiles>(dataFiles);
		templates::safe_delete<EventManager>(eventManager);
		templates::safe_delete<LuaStateManager>(luaStateManager);
		templates::safe_delete<GameMessages>(gameMessages);

		templates::safe_delete<ResourceCache>(resourceCache);
		//IResourceFile
		templates::safe_delete<DebuggingOptions>(debuggingOptions);
		templates::safe_delete<PlayerOptions>(playerOptions);
		templates::safe_delete<InitOptions>(initOptions);

	}

	void GameCodeApp::testGlobal() {
		stringstream ss;
		ss << "test GameCodeApp global ";
		logger::info(ss);

		if (m_pGame) {
			//m_pGame->tempTestProcessManager();
		}

	}

}


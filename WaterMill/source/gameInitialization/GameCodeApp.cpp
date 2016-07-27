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
#include<iostream>
// cout

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


using namespace std;

namespace watermill {

	const string GameCodeApp::GAME_PROCESS_NAME = "watermill";
	const string GameCodeApp::DEBUG_OPTIONS_XML = "debugOptions.xml";
	const string GameCodeApp::PLAYER_OPTIONS_XML = "playerOptions.xml";

	const string GameCodeApp::ASSETS_ZIP = "assets.zip";


	//const string GameCodeApp::GAME_PROCESS_NAME = "watermill.exe";


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

	bool GameCodeApp::initInstanceShortDebug() {
		bool returnCode = true;

		IResourceFile *zipFile = new ResourceZipFile(ASSETS_ZIP);
		resourceCache = new ResourceCache(50,zipFile);

		try {
			initOptions = new InitOptions;

			// Load programmer's options for debugging purposes
			debuggingOptions = new DebuggingOptions;

			string debugFilePath = initOptions->getGameFolder() + DEBUG_OPTIONS_XML;
			debuggingOptions->load(debugFilePath);

			bool done = true;
			cout << "Main loop" << endl;

			while ( !done ) {
				// Main loop
			}
		} catch ( ErrorCode& error ) {
			error.informUser();
			returnCode = false;
		}

		debugging_options::safe_delete ( debuggingOptions );
		init_options::safe_delete ( initOptions );

		return ( returnCode );

	}

	bool GameCodeApp::initInstance() {
		bool returnCode = true;
		SystemCalls systemCalls;
#ifndef _DEBUG

		if ( !systemCalls.isOnlyInstance ( GameCodeApp::GAME_PROCESS_NAME ) ) {
			//if (!systemCalls.IsOnlyInstance(GAME_TITLE)) {
			cout << "There is another process running" << endl;
			return false;
		}

#endif
		// Check for adequate machine resources.
		bool resourceCheck = false;

		while ( !resourceCheck ) {

			//			const DWORDLONG physicalRAM = 512 * MEGABYTE;
			//			const DWORDLONG virtualRAM = 1024 * MEGABYTE;
			//			const DWORDLONG diskSpace = 10 * MEGABYTE;
			const unsigned long long physicalRAM = 512 * MEGABYTE;
			const unsigned long long virtualRAM = 1024 * MEGABYTE;
			const unsigned long long diskSpace = 10 * MEGABYTE;

			if ( !systemCalls.checkHardDisk ( diskSpace ) ) {
				return false;
			}

			//const DWORD minCpuSpeed = 1300; // 1.3Ghz
			//DWORD thisCPU = systemCalls.readCPUSpeed();
			const unsigned long minCpuSpeed = 1300; // 1.3Ghz
			unsigned long thisCPU = systemCalls.readCPUSpeed();

			cout << "CPU speed needed: " << minCpuSpeed << " [MHz], CPU speed available: " << thisCPU << " [MHz]" << endl;

			if ( thisCPU < minCpuSpeed ) {
				cout << "GetCPUSpeed reports CPU is too slow for this game." << endl;
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

			gameMessages = new GameMessages(initOptions->getAssetsFolder(), playerOptions->getOption(playerOptions->LANGUAGE));
			gameMessages->testMessages();

			// Load programmer's options for debugging purposes
			debuggingOptions = new DebuggingOptions;

			//C:\home\myImportantFiles\projects\git\Main\WaterMill\media
			//C:\home\myImportantFiles\projects\git\Main\WaterMill\settings\codeblocks\Watermill
			//debuggingOptions.load("..\\..\\..\\media\\debugOptions.xml"); // OK
			//			debuggingOptions->load("../../../media/debugOptions.xml");
			string debugFilePath = initOptions->getGameFolder() + DEBUG_OPTIONS_XML;
			debuggingOptions->load(debugFilePath);


			dataFiles = new DataFiles;
			audioSystem = new AudioSystem;
			videoSystem = new VideoSystem;
			bool done = true;
			cout << "Main loop" << endl;

			while ( !done ) {
				// Main loop
			}
		} catch ( ErrorCode& error ) {
			error.informUser();
			returnCode = false;
		}

		video_system::safe_delete ( videoSystem );
		audio_system::safe_delete ( audioSystem );
		data_files::safe_delete ( dataFiles );
		debugging_options::safe_delete ( debuggingOptions );

		game_messages::safe_delete(gameMessages);
		player_options::safe_delete(playerOptions);
		init_options::safe_delete ( initOptions );

		return ( returnCode );
	}
}


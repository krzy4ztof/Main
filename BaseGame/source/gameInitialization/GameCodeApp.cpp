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
#include <iostream> // cout
#include <string> // string
#include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h>

#include "Macros.h"
#include "DataFiles.h"
#include "AudioSystem.h"
#include "VideoSystem.h"
#include "VideoSystemGLFW.h"
#include "ErrorCode.h"

#include "SystemCalls.h"
#include "InitOptions.h"
#include "DebuggingOptions.h"
#include "../resourceCache/ResourceCache.h"
#include "../resourceCache/IResourceFile.h"
#include "../resourceCache/ResourceZipFile.h"
#include "../resourceCache/XmlResourceLoader.h"
#include "../resourceCache/TextFileLoader.h"
#include "../resourceCache/MessageLoader.h"

#include "../luaScripting/ScriptResourceLoader.h"
#include "../luaScripting/LuaStateManager.h"

#include "../graphics3d/ShaderResourceLoader.h"
#include "../graphics3d/TextureResourceLoader.h"
#include "../graphics3d/FreeTypeResourceLoader.h"
#include "../graphics3d/OpenGLRenderer.h"
#include "../graphics3d/FpsCounter.h"


#include "../gameLogic/BaseGameLogic.h"

#include "../debugging/Logger.h"
#include "../utilities/Templates.h"

#include "../resourceCache/DevelopmentResourceFolder.h"
#include "../resourceCache/DevelopmentResourceUnzipFile.h"
#include "../userInterface/QuitMessageBoxUI.h"


#include <sstream>      // std::stringstream
#include <memory> // shared_ptr, weak_ptr, make_shared
//#include <typeinfo> // typeid

using std::string;
using std::cout;
using std::endl;
using std::stringstream;
using std::make_shared;
using std::shared_ptr;

namespace base_game {
GameCodeApp* g_pApp = nullptr;
//g_pApp = nullptr;

const string GameCodeApp::GAME_PROCESS_NAME = "watermill";
const string GameCodeApp::DEBUG_OPTIONS_XML = "debugOptions.xml";
const string GameCodeApp::PLAYER_OPTIONS_XML = "playerOptions.xml";

//const string GameCodeApp::ASSETS_ZIP = "assets.zip";

GameCodeApp::GameCodeApp() {
	logger::trace("Create GameCodeApp");
	g_pApp = this;

	m_pGame = nullptr;

	initOptions = nullptr;
	playerOptions = nullptr;
	debuggingOptions = nullptr;

	// resourceCache = nullptr;
	shrdPtrResourceCache = nullptr;

	//gameMessages = nullptr;
	luaStateManager = nullptr;
	eventManager = nullptr;
	dataFiles = nullptr;
	audioSystem = nullptr;
	videoSystem = nullptr;
	videoSystemGLFW = nullptr;

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
	logger::trace("Start Destroy GameCodeApp");
	onClose();

	logger::trace("End Destroy GameCodeApp");
}

InitOptions* GameCodeApp::getInitOptions() {
	return this->initOptions;
}

shared_ptr<ResourceCache> GameCodeApp::getResourceCache() {
	return this->shrdPtrResourceCache;
}

bool GameCodeApp::initAllOptions() {
	bool returnCode = true;

	try {
		initOptions = new InitOptions;

		playerOptions = new PlayerOptions;
		string playerOptionsFilePath = initOptions->getGameFolder()
				+ PLAYER_OPTIONS_XML;
		playerOptions->load(playerOptionsFilePath);

		// Load programmer's options for debugging purposes
		debuggingOptions = new DebuggingOptions;
		string debugFilePath = initOptions->getGameFolder() + DEBUG_OPTIONS_XML;
		debuggingOptions->load(debugFilePath);

		string value = debuggingOptions->getOption("assetsReadMode");
		stringstream ss;
		ss << "debuggingOptions assetsReadMode: " + value;

		logger::info(ss);

	} catch (ErrorCode& error) {
		error.informUser();
		returnCode = false;
	}

	return returnCode;
}

bool GameCodeApp::initInstance() {
	bool returnCode = true;
	SystemCalls systemCalls;
#ifndef _DEBUG

	if (!systemCalls.isOnlyInstance(GameCodeApp::GAME_PROCESS_NAME)) {
		logger::warning("There is another process running");
		return false;
	}

#endif
	// Check for adequate machine resources.
	bool resourceCheck = false;

	while (!resourceCheck) {

		//			const DWORDLONG physicalRAM = 512 * MEGABYTE;
		//			const DWORDLONG virtualRAM = 1024 * MEGABYTE;
		//			const DWORDLONG diskSpace = 10 * MEGABYTE;

		//const unsigned long long physicalRAM = 512 * MEGABYTE;
		//const unsigned long long virtualRAM = 1024 * MEGABYTE;
		const unsigned long long physicalRAM = 1 * MEGABYTE;
		const unsigned long long virtualRAM = 1 * MEGABYTE;

		const unsigned long long diskSpace = 10 * MEGABYTE;

		if (!systemCalls.checkHardDisk(diskSpace)) {
			return false;
		}

		//const DWORD minCpuSpeed = 1300; // 1.3Ghz
		//DWORD thisCPU = systemCalls.readCPUSpeed();
		//const unsigned long minCpuSpeed = 1300; // 1.3Ghz
		const unsigned long minCpuSpeed = 900; // 0.9Ghz

		unsigned long thisCPU = systemCalls.readCPUSpeed();

		if (thisCPU < minCpuSpeed) {
			logger::warning(
					"GetCPUSpeed reports CPU is too slow for this game.");
			return false;
		}

		if (!systemCalls.checkMemory(physicalRAM, virtualRAM)) {
			return false;
		}

		resourceCheck = true;
	}

	string readMode = debuggingOptions->getOption(
			debuggingOptions->ASSETS_READ_MODE);
	string saveMode = debuggingOptions->getOption(
			debuggingOptions->ASSETS_SAVE_MODE);

//	IResourceFile *zipFile = nullptr; // Will be removed in ResourceCache destructor
	shared_ptr<IResourceFile> zipFile; // Will be removed in ResourceCache destructor

	if (IResourceFile::ASSETS_READ_MODE_FOLDER.compare(readMode) == 0) {
//			zipFile = new DevelopmentResourceZipFile(ASSETS_ZIP, readMode, initOptions->getAssetsFolder());

//		zipFile = new DevelopmentResourceFolder(initOptions->getRootFolder(),
//				initOptions->getAssetsFolder());

		zipFile = make_shared<DevelopmentResourceFolder>(
				initOptions->getRootFolder(), initOptions->getAssetsFolder());

	} else if (IResourceFile::ASSETS_READ_MODE_UNZIPFILE.compare(readMode)
			== 0) {
//		zipFile = new DevelopmentResourceUnzipFile(initOptions->getRootFolder(),
//				IResourceFile::ASSETS_UNZIP_FILE);

		zipFile = make_shared<DevelopmentResourceUnzipFile>(
				initOptions->getRootFolder(), IResourceFile::ASSETS_UNZIP_FILE);

	} else if (IResourceFile::ASSETS_READ_MODE_ZIPFILE.compare(readMode) == 0) {
//		zipFile = new ResourceZipFile(initOptions->getRootFolder(),
//				IResourceFile::ASSETS_ZIP_FILE);

		zipFile = make_shared<ResourceZipFile>(initOptions->getRootFolder(),
				IResourceFile::ASSETS_ZIP_FILE);

	}

//	resourceCache = new ResourceCache(initOptions->getAssetsFolder(), 50,
//			zipFile);

	//ResourceCache* resCache = new ResourceCache(initOptions->getAssetsFolder(),
	//	50, zipFile);

//	shrdPtrResourceCache->

	shrdPtrResourceCache = make_shared<ResourceCache>(
			initOptions->getAssetsFolder(), 50, zipFile);

	// Call to zipFile->vOpen();

	if (!shrdPtrResourceCache->init()) {
		// if (!resourceCache->init()) {
		logger::warning(
				"Failed to initialize resource cache!  Are your paths set up correctly?");
		return false;
	}

	//TODO
	//IResourceFile *zipFileSave = nullptr;
	if (IResourceFile::ASSETS_SAVE_MODE_NONE.compare(saveMode) == 0) {
		//zipFile = new DevelopmentResourceZipFile(ASSETS_ZIP);
	} else if (IResourceFile::ASSETS_SAVE_MODE_FOLDER.compare(saveMode) == 0) {
//		string zipClassName = typeid(zipFile.get()).name();
		string outputName;
		if (IResourceFile::ASSETS_READ_MODE_FOLDER.compare(readMode) == 0) {
			outputName = IResourceFile::ASSETS_FOLDER_TO_FOLDER;
		} else if (IResourceFile::ASSETS_READ_MODE_UNZIPFILE.compare(readMode)
				== 0) {
			outputName = IResourceFile::ASSETS_UNZIP_TO_FOLDER;
		} else if (IResourceFile::ASSETS_READ_MODE_ZIPFILE.compare(readMode)
				== 0) {
			outputName = IResourceFile::ASSETS_ZIP_TO_FOLDER;
		}

		// string outputName = IResourceFile::ASSETS_FOLDER_TO_FOLDER;
		// + IResourceFile::ASSETS_UNZIP_TO_FOLDER;
		// IResourceFile::ASSETS_ZIP_TO_FOLDER

		zipFile->vSave(saveMode, outputName);

		//TODO save method invocation

	} else if (IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE.compare(saveMode)
			== 0) {
		string outputName;
		if (IResourceFile::ASSETS_READ_MODE_FOLDER.compare(readMode) == 0) {
			outputName = IResourceFile::ASSETS_UNZIP_FILE;
		} else if (IResourceFile::ASSETS_READ_MODE_UNZIPFILE.compare(readMode)
				== 0) {
			outputName = IResourceFile::ASSETS_UNZIP_TO_UNZIP;
		} else if (IResourceFile::ASSETS_READ_MODE_ZIPFILE.compare(readMode)
				== 0) {
			outputName = IResourceFile::ASSETS_ZIP_TO_UNZIP;
		}
		// string outputName = IResourceFile::ASSETS_UNZIP_FILE;
		// IResourceFile::ASSETS_UNZIP_TO_UNZIP;
		// IResourceFile::ASSETS_ZIP_TO_UNZIP

		zipFile->vSave(saveMode, outputName);

		//TODO save method invocation
		//zipFile = new ResourceZipFile(ASSETS_ZIP);

	} else if (IResourceFile::ASSETS_SAVE_MODE_ZIPFILE.compare(saveMode) == 0) {
		//zipFile = new ResourceZipFile(ASSETS_ZIP);
		string outputName;
		if (IResourceFile::ASSETS_READ_MODE_FOLDER.compare(readMode) == 0) {
			outputName = IResourceFile::ASSETS_ZIP_FILE;
		} else if (IResourceFile::ASSETS_READ_MODE_UNZIPFILE.compare(readMode)
				== 0) {
			outputName = IResourceFile::ASSETS_UNZIP_TO_ZIP;
		} else if (IResourceFile::ASSETS_READ_MODE_ZIPFILE.compare(readMode)
				== 0) {
			outputName = IResourceFile::ASSETS_ZIP_TO_ZIP;
		}

		// string outputName = IResourceFile::ASSETS_ZIP_FILE;
		// IResourceFile::ASSETS_UNZIP_TO_ZIP;
		// IResourceFile::ASSETS_ZIP_TO_ZIP

		zipFile->vSave(saveMode, outputName);

		//TODO save method invocation
	}

	shrdPtrResourceCache->registerLoader(
			xml_resource_loader::createXmlResourceLoader());
	shrdPtrResourceCache->registerLoader(
			text_file_loader::createTextFileLoader());
	shrdPtrResourceCache->registerLoader(message_loader::createMessageLoader());
	shrdPtrResourceCache->registerLoader(
			script_resource_loader::createScriptResourceLoader());

	shrdPtrResourceCache->registerLoader(
			vertex_shader_resource_loader::createVertexShaderResourceLoader());
	shrdPtrResourceCache->registerLoader(
			fragment_shader_resource_loader::createFragmentShaderResourceLoader());
	shrdPtrResourceCache->registerLoader(
			jpeg_resource_loader::createJpegResourceLoader());
	shrdPtrResourceCache->registerLoader(
			png_resource_loader::createPngResourceLoader());
	shrdPtrResourceCache->registerLoader(
			free_type_resource_loader::createFreeTypeResourceLoader());


	try {
		gameMessages = make_shared<GameMessages>(shrdPtrResourceCache,
				playerOptions->getOption(playerOptions->LANGUAGE),
				playerOptions->getOption(playerOptions->LANGUAGES));

//		gameMessages = new GameMessages(initOptions->getAssetsFolder(),
		//			playerOptions->getOption(playerOptions->LANGUAGE));

		//gameMessages->initByPath(initOptions->getAssetsFolder(),
		//		playerOptions->getOption(playerOptions->LANGUAGE));

		//gameMessages->init(initOptions->getAssetsFolder(),
		//		playerOptions->getOption(playerOptions->LANGUAGE));

		//game_messages::temp_init_locale_pl();
		//game_messages::init_locale_en();

		gameMessages->init();
		gameMessages->temp_testMessagesGetText();

		// luaStateManager = new LuaStateManager(initOptions->getAssetsFolder());
		luaStateManager = new LuaStateManager(shrdPtrResourceCache);
		//luaStateManager->testLua("test.lua");
		luaStateManager->temp_testLuaResourceCache("test.lua");

		eventManager = new EventManager();

		dataFiles = new DataFiles;
		audioSystem = new AudioSystem;
		videoSystem = new VideoSystem;

		videoSystemGLFW = make_shared<VideoSystemGLFW>();
		// videoSystemGLFW = new VideoSystemGLFW;
		openGLRenderer = make_shared<OpenGLRenderer>(videoSystemGLFW,
				shrdPtrResourceCache);

		// initialize the directory location you can store save game files
		//_tcscpy_s(m_saveGameDirectory, GetSaveGameDirectory(GetHwnd(), VGetGameAppDirectory()));
		//string* gameAppDir =

		saveManager = new SaveManager();
		string gameAppDirectory = vGetGameAppDirectory();

		stringstream ss;

		string userProfilePath = systemCalls.getUserProfilePath();

		saveManager->init(userProfilePath, gameAppDirectory);

		bool glfw = true;

		if (glfw) {
			videoSystemGLFW->initialize();
			// videoSystemGLFW->startGLFW();
		} else {
			//	videoSystem->startFreeGlut(GAME_PROCESS_NAME);

		}

		openGLRenderer->initRenderers();

		m_pGame = createGameAndView(shrdPtrResourceCache, openGLRenderer,
				gameMessages);

		//shrdPtrResourceCache->preLoad("*.jpg",
		//		resource_cache::showPreLoadProgress);
		shrdPtrResourceCache->preLoad("*.txt",
				resource_cache::showPreLoadProgress);

		/*
		 bool done = false;
		 logger::trace("Main loop+++");

		 videoSystem->startFreeGlutMainLoop();
		 while ( !done ) {
		 // Main loop

		 done = true;
		 }
		 */

	} catch (ErrorCode& error) {
		error.informUser();
		returnCode = false;
	}
	return (returnCode);
}

void GameCodeApp::mainLoop() {
	bool done = false;

	m_pGame->tempTestActors();	//ok
	// m_pGame->tempAddViews();		//ok -> to remove

	bool glfw = true;

	if (glfw) {
		//videoSystemGLFW->startGLFW();
		videoSystemGLFW->mainLoop();
	} else {
		//	videoSystem->startFreeGlutMainLoop();

	}

	while (!done) {
		// Main loop
		done = true;
	}

}

bool GameCodeApp::isQuitting() {
	return m_bQuitting;
}

bool GameCodeApp::hasModalDialog() {
	return m_HasModalDialog != 0;
}

/**
 * See void CALLBACK GameCodeApp::OnUpdateGame( double fTime, float fElapsedTime, void* pUserContext  )
 */
void GameCodeApp::onUpdateGame(double fTime, float fElapsedTime) { //, void* pUserContext  )
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


void GameCodeApp::onFrameRender(double fTime, float fElapsedTime) { //, void* pUserContext  )
	m_pGame->onFrameRender(fTime, fElapsedTime);

	// TODO:
	// m_pGame->VRenderDiagnostics();
}

void GameCodeApp::onClose() {

	templates::safe_delete<BaseGameLogic>(m_pGame);
	// gameView
	templates::safe_delete<SaveManager>(saveManager);

	templates::safe_delete<VideoSystem>(videoSystem);
	//templates::safe_delete<VideoSystem>(openGLRenderer);
	openGLRenderer.reset();
	//templates::safe_delete<VideoSystemGLFW>(videoSystemGLFW);
	videoSystemGLFW.reset();
	templates::safe_delete<AudioSystem>(audioSystem);
	templates::safe_delete<DataFiles>(dataFiles);
	templates::safe_delete<EventManager>(eventManager);
	templates::safe_delete<LuaStateManager>(luaStateManager);
	//templates::safe_delete<GameMessages>(gameMessages);
	gameMessages.reset();


	//templates::safe_delete<ResourceCache>(resourceCache);
	shrdPtrResourceCache.reset();
	//IResourceFile
	templates::safe_delete<DebuggingOptions>(debuggingOptions);
	templates::safe_delete<PlayerOptions>(playerOptions);
	templates::safe_delete<InitOptions>(initOptions);

}

void GameCodeApp::testGlobal() {
	if (m_pGame) {
		//m_pGame->tempTestProcessManager();
	}

}

//
// GameCodeApp::GetHumanView()					- not described in the book
//
//    FUTURE WORK - This function should accept a player number for split screen games
//
shared_ptr<HumanView> GameCodeApp::getHumanView() {
	return m_pGame->getHumanView();
}

//
// class GameCodeApp::Modal						- Chapter 10, page 293
//
//int GameCodeApp::Modal(shared_ptr<IScreenElement> pModalScreen, int defaultAnswer)
int GameCodeApp::modal(shared_ptr<QuitMessageBoxUI> pMessageBox,
		int defaultAnswer) {
	stringstream ss;
	shared_ptr<HumanView> humanView = getHumanView();

	if (!humanView) {
		// Whoops! There's no human view attached.
		return defaultAnswer;
	}

	if (m_HasModalDialog & 0x10000000) {
		logger::warning("Too Many nested dialogs!");
		return defaultAnswer;
	}

	/*
	GCC_ASSERT(GetHwnd() != NULL && _T("Main Window is NULL!"));
	if ((GetHwnd() != NULL) && IsIconic(GetHwnd())) {
		FlashWhileMinimized();
	}
	 */

	m_HasModalDialog <<= 1;
	m_HasModalDialog |= 1;

	//pView->VPushElement(pModalScreen);
	///humanView->vPushElement(pMessageBox);

//	LPARAM lParam = 0;
//	int result = pumpUntilMessage(g_MsgEndModal, NULL, &lParam);
	int result = pumpUntilMessage(pMessageBox);

	/*
	if (lParam != 0) {
		if (lParam == g_QuitNoPrompt)
			result = defaultAnswer;
		else
			result = (int) lParam;
	}
	 */

	//pView->VRemoveElement(pModalScreen);
	//humanView->vRemoveElement(pMessageBox);
	m_HasModalDialog >>= 1;

	return result;
}

//
// class GameCodeApp::PumpUntilMessage			- Chapter 10, page 295
//
//int GameCodeApp::PumpUntilMessage(UINT msgEnd, WPARAM *pWParam,
//		LPARAM *pLParam) {

int GameCodeApp::pumpUntilMessage(shared_ptr<QuitMessageBoxUI> pMessageBox) {
	//int currentTime = timeGetTime();
	double currentTime = glfwGetTime();
	shared_ptr<FpsCounter> pFpsCounter = videoSystemGLFW->getFpsCounter();
	/*
	MSG msg;
	for (;;) {
		if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (msg.message == WM_CLOSE) {
				m_bQuitting = true;
				GetMessage(&msg, NULL, 0, 0);
				break;
			} else {
				// Default processing
				if (GetMessage(&msg, NULL, NULL, NULL)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				// Are we done?
				if (msg.message == msgEnd)
					break;
			}
		} else {
			// Update the game views, but nothing else!
			// Remember this is a modal screen.
			if (m_pGame) {
				int timeNow = timeGetTime();
				int deltaMilliseconds = timeNow - currentTime;
				for (GameViewList::iterator i = m_pGame->m_gameViews.begin();
						i != m_pGame->m_gameViews.end(); ++i) {
					(*i)->VOnUpdate(deltaMilliseconds);
				}
				currentTime = timeNow;
				DXUTRender3DEnvironment();
			}
		}
	}
	if (pLParam)
		*pLParam = msg.lParam;
	if (pWParam)
		*pWParam = msg.wParam;
	 */

	for (;;) {
		bool shouldEnd = pMessageBox->isShouldQuit();
		if (shouldEnd) {
			break;


		/*
		if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (msg.message == WM_CLOSE) {
				m_bQuitting = true;
				GetMessage(&msg, NULL, 0, 0);
				break;
			} else {
				// Default processing
				if (GetMessage(&msg, NULL, NULL, NULL)) {
					TranslateMessage (&msg);
					DispatchMessage(&msg);
				}

				// Are we done?
				if (msg.message == msgEnd)
					break;
		 */
		} else {

			// Update the game views, but nothing else!
			// Remember this is a modal screen.
			if (m_pGame) {
				double lastTime = pFpsCounter->getLastTime();
				double elapsedTime = currentTime - lastTime;
				float elapsedTimeFloat = static_cast<float>(elapsedTime);
				m_pGame->vOnUpdateModal(float(currentTime), elapsedTimeFloat);
				m_pGame->onFrameRender(float(currentTime), elapsedTimeFloat);
				glfwPollEvents();
			}
		}
	}

	return 0;
}


}

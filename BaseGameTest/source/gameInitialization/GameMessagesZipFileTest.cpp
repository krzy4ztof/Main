/*
 * GameMessagesTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"
#include "../testGame/TestGame.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
#include "../../../BaseGame/source/gameInitialization/PlayerOptions.h"
#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"
#include "../../../BaseGame/source/gameInitialization/ErrorCode.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/IResourceFile.h"
#include "../../../BaseGame/source/resourceCache/ResourceZipFile.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/resourceCache/MessageLoader.h"

#include <boost/test/unit_test.hpp>
#include <sstream>      // std::stringstream
#include <string> // std::string

using base_game::InitOptions;
using base_game::PlayerOptions;
using base_game::GameCodeApp;
using base_game::GameMessages;
using base_game::ErrorCode;
using base_game::IResourceFile;
using base_game::ResourceCache;

using base_game::ResourceZipFile;


namespace templates = base_game::templates;
namespace logger = base_game::logger;
namespace game_messages = base_game::game_messages;
namespace message_loader = base_game::message_loader;

using std::stringstream;
using std::string;
using std::shared_ptr;
using std::make_shared;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct GameMessagesZipFileFixture {

	//InitOptions* pInitOptions;
	PlayerOptions *pPlayerOptions;
	GameMessages *pGameMessages;
	TestGame* pTestGame;
	shared_ptr<ResourceCache> shrdPtrResourceCache;
	shared_ptr<IResourceFile> shrdPtrResourceFile; // Will be removed in ResourceCache destructor


	GameMessagesZipFileFixture() {
		logger::info("Create GameMessagesZipFileFixture");
		pTestGame = new TestGame;

		base_game::g_pApp = pTestGame;

		// START GameCodeApp::initAllOptions()
		InitOptions* pInitOptions = new InitOptions;
		shrdPtrResourceFile = make_shared<ResourceZipFile>(
				pInitOptions->getRootFolder(),
				IResourceFile::ASSETS_ZIP_FILE);

		pPlayerOptions = new PlayerOptions;
		pTestGame->setInitOptions(pInitOptions);

		string playerOptionsFilePath = pInitOptions->getGameFolder()
				+ GameCodeApp::PLAYER_OPTIONS_XML;
		pPlayerOptions->load(playerOptionsFilePath);
		// END GameCodeApp::initAllOptions()

		// START GameCodeApp::initInstance()
		shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, shrdPtrResourceFile);

		if (!shrdPtrResourceCache->init()) {
			logger::warning(
					"Failed to initialize resource cache!  Are your paths set up correctly?");
		}

		shrdPtrResourceCache->registerLoader(
				message_loader::createMessageLoader());
		
		pTestGame->setResourceCache(shrdPtrResourceCache);

		pGameMessages = new GameMessages(shrdPtrResourceCache,
				pPlayerOptions->getOption(pPlayerOptions->LANGUAGE),
				pPlayerOptions->getOption(pPlayerOptions->LANGUAGES));

		pGameMessages->init();

		logger::info("End Create GameMessagesZipFileFixture");
		// END GameCodeApp::initInstance()

}

	~GameMessagesZipFileFixture() {
		logger::info("Destroy GameMessagesZipFileFixture");

		templates::safe_delete<GameMessages>(pGameMessages);
		templates::safe_delete<PlayerOptions>(pPlayerOptions);

		shrdPtrResourceCache.reset();
		shrdPtrResourceFile.reset();
		//templates::safe_delete < InitOptions > (pInitOptions);

		templates::safe_delete<TestGame>(pTestGame);

}
};

BOOST_FIXTURE_TEST_SUITE(GameMessagesZipFileSuite, GameMessagesZipFileFixture)

BOOST_AUTO_TEST_CASE(messagessZipFileLoader, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(messagessZipFileLoader, * unit_test::enabled()) {
	try {
		pGameMessages->temp_testMessagesGetText();
		pGameMessages->switchCurrentLanguage("en.UTF-8");
		pGameMessages->temp_testMessagesGetText();
	} catch (ErrorCode& error) {
		error.informUser();
	}

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(messagessZipFileLoader2, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(messagessZipFileLoader2, * unit_test::enabled()) {
	try {
		pGameMessages->temp_testMessagesGetText();
	} catch (ErrorCode& error) {
		error.informUser();
	}

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

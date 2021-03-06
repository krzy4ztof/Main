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
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceFolder.h"
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

using base_game::DevelopmentResourceFolder;

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

struct GameMessagesFixture {

	// InitOptions* pInitOptions;
	PlayerOptions *pPlayerOptions;
	GameMessages *pGameMessages;
	TestGame* pTestGame;
	shared_ptr<ResourceCache> shrdPtrResourceCache;
	shared_ptr<IResourceFile> shrdPtrResourceFile; // Will be removed in ResourceCache destructor

	GameMessagesFixture() {
		logger::info("Create GameMessagesFixture");
		pTestGame = new TestGame;

		base_game::g_pApp = pTestGame;

		// START GameCodeApp::initAllOptions()
		InitOptions* pInitOptions = new InitOptions;
		shrdPtrResourceFile = make_shared<DevelopmentResourceFolder>(
				pInitOptions->getRootFolder(), pInitOptions->getAssetsFolder());

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
		// pTestGame->setResourceCache(shrdPtrResourceCache);

		shrdPtrResourceCache->registerLoader(
				message_loader::createMessageLoader());

		pTestGame->setResourceCache(shrdPtrResourceCache);

		pGameMessages = new GameMessages(shrdPtrResourceCache,
				pPlayerOptions->getOption(pPlayerOptions->LANGUAGE),
				pPlayerOptions->getOption(pPlayerOptions->LANGUAGES));
		//pGameMessages->initByPath(pInitOptions->getAssetsFolder(),
		//		pPlayerOptions->getOption(pPlayerOptions->LANGUAGE));

		// game_messages::init_locale_pl();
		//pGameMessages->init(pInitOptions->getAssetsFolder(),
		//		pPlayerOptions->getOption(pPlayerOptions->LANGUAGE));

		pGameMessages->init();

		// END GameCodeApp::initInstance()

	}

	~GameMessagesFixture() {
		logger::info("Destroy GameMessagesFixture");

		templates::safe_delete<GameMessages>(pGameMessages);
		templates::safe_delete<PlayerOptions>(pPlayerOptions);

		shrdPtrResourceCache.reset();
		shrdPtrResourceFile.reset();
		//templates::safe_delete < InitOptions > (pInitOptions);

		templates::safe_delete<TestGame>(pTestGame);

	}
};

BOOST_FIXTURE_TEST_SUITE(GameMessagesSuite, GameMessagesFixture)

BOOST_AUTO_TEST_CASE(messagesLoader, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(messagesLoader, * unit_test::enabled()) {
	try {
		pGameMessages->temp_testMessagesGetText();
		pGameMessages->switchCurrentLanguage("en.UTF-8");
		pGameMessages->temp_testMessagesGetText();
	} catch (ErrorCode& error) {
		error.informUser();
	}

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(messagesLoader2, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(messagesLoader2, * unit_test::enabled()) {
	try {
		pGameMessages->temp_testMessagesGetText();
	} catch (ErrorCode& error) {
		error.informUser();
	}

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

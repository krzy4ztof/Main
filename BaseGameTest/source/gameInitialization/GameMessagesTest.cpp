/*
 * GameMessagesTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
#include "../../../BaseGame/source/gameInitialization/PlayerOptions.h"
#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"
#include "../../../BaseGame/source/gameInitialization/GameMessages.h"
#include "../../../BaseGame/source/gameInitialization/ErrorCode.h"




#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>
#include <sstream>      // std::stringstream
#include <string> // std::string

using base_game::InitOptions;
using base_game::PlayerOptions;
using base_game::GameCodeApp;
using base_game::GameMessages;
using base_game::ErrorCode;


namespace templates = base_game::templates;
namespace logger = base_game::logger;

using std::stringstream;
using std::string;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct GameMessagesFixture {

	InitOptions* pInitOptions;
	PlayerOptions *pPlayerOptions;
	GameMessages *pGameMessages;

	GameMessagesFixture() {
		logger::info("Create GameMessagesFixture");

		pInitOptions = new InitOptions;
		pPlayerOptions = new PlayerOptions;

		string playerOptionsFilePath = pInitOptions->getGameFolder()
				+ GameCodeApp::PLAYER_OPTIONS_XML;
		pPlayerOptions->load(playerOptionsFilePath);

		pGameMessages = new GameMessages(pInitOptions->getAssetsFolder(),
				pPlayerOptions->getOption(pPlayerOptions->LANGUAGE));

}

	~GameMessagesFixture() {
		logger::info("Destroy GameMessagesFixture");

		templates::safe_delete<GameMessages>(pGameMessages);
		templates::safe_delete<PlayerOptions>(pPlayerOptions);
		templates::safe_delete < InitOptions > (pInitOptions);
}
};

BOOST_FIXTURE_TEST_SUITE(GameMessagesSuite, GameMessagesFixture)

BOOST_AUTO_TEST_CASE(primeSearch, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	try {
		pGameMessages->testMessages();
	} catch (ErrorCode& error) {
		error.informUser();
	}

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

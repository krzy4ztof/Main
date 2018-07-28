/*
 * LuaStateManagerTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
#include "../../../BaseGame/source/luaScripting/LuaStateManager.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>

using base_game::InitOptions;
using base_game::LuaStateManager;

namespace templates = base_game::templates;
namespace logger = base_game::logger;


namespace base_game_test {

struct LuaStateManagerFixture {

	InitOptions* pInitOptions;
	LuaStateManager *pLuaStateManager;

	LuaStateManagerFixture() {
		logger::info("Create LuaStateManagerFixture");

		pInitOptions = new InitOptions;
		pLuaStateManager = new LuaStateManager(pInitOptions->getAssetsFolder());


	}

	~LuaStateManagerFixture() {
		logger::info("Destroy LuaStateManagerFixture");

		templates::safe_delete < LuaStateManager > (pLuaStateManager);
		templates::safe_delete < InitOptions > (pInitOptions);
		
	}
};

BOOST_FIXTURE_TEST_SUITE(LuaStateManagerSuite, LuaStateManagerFixture)

BOOST_AUTO_TEST_CASE(luaRun) {

	//InitOptions initOptions;
	//LuaStateManager luaStateManager(initOptions.getAssetsFolder());
	pLuaStateManager->testLua("test.lua");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */


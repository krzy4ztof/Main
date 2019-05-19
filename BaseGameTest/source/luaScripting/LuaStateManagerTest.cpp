/*
 * LuaStateManagerTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
#include "../../../BaseGame/source/luaScripting/LuaStateManager.h"
#include "../../../BaseGame/source/luaScripting/ScriptResourceLoader.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/IResourceFile.h"
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceFolder.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"

#include <boost/test/unit_test.hpp>

using base_game::InitOptions;
using base_game::LuaStateManager;
using base_game::ResourceCache;
using base_game::IResourceFile;

using base_game::DevelopmentResourceFolder;

using std::shared_ptr;
using std::make_shared;

namespace templates = base_game::templates;
namespace logger = base_game::logger;

namespace script_resource_loader = base_game::script_resource_loader;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct LuaStateManagerFixture {

	InitOptions* pInitOptions;
	LuaStateManager *pLuaStateManager;

	shared_ptr<ResourceCache> shrdPtrResourceCache;
	shared_ptr<IResourceFile> shPtrResourceFolder; // Will be removed in ResourceCache destructor

	LuaStateManagerFixture() {
		logger::info("Create LuaStateManagerFixture");

		pInitOptions = new InitOptions;

		shPtrResourceFolder = make_shared<DevelopmentResourceFolder>(
				pInitOptions->getRootFolder(), pInitOptions->getAssetsFolder());

		shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, shPtrResourceFolder);

		if (!shrdPtrResourceCache->init()) {
			logger::warning(
					"Failed to initialize resource cache!  Are your paths set up correctly?");
		}

		// pLuaStateManager = new LuaStateManager(pInitOptions->getAssetsFolder());
		pLuaStateManager = new LuaStateManager(shrdPtrResourceCache);

		shrdPtrResourceCache->registerLoader(
				script_resource_loader::createScriptResourceLoader());

	}

	~LuaStateManagerFixture() {
		logger::info("Destroy LuaStateManagerFixture");

		shrdPtrResourceCache.reset();
		shPtrResourceFolder.reset();

		templates::safe_delete<LuaStateManager>(pLuaStateManager);
		templates::safe_delete<InitOptions>(pInitOptions);

	}
};

BOOST_FIXTURE_TEST_SUITE(LuaStateManagerSuite, LuaStateManagerFixture)

BOOST_AUTO_TEST_CASE(luaRun, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(luaRun, * unit_test::enabled()) {

	//InitOptions initOptions;
	//LuaStateManager luaStateManager(initOptions.getAssetsFolder());
	// pLuaStateManager->testLua("test.lua");

	// pLuaStateManager->temp_testLuaResourceCache("test1.lua");
	pLuaStateManager->temp_testLuaResourceCache("test.lua");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */


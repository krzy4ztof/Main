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
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceUnzipFile.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"

#include <boost/test/unit_test.hpp>

using base_game::InitOptions;
using base_game::LuaStateManager;
using base_game::ResourceCache;
using base_game::IResourceFile;

using base_game::DevelopmentResourceUnzipFile;

using std::shared_ptr;
using std::make_shared;

namespace templates = base_game::templates;
namespace logger = base_game::logger;

namespace script_resource_loader = base_game::script_resource_loader;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct LuaStateManagerUnzipFixture {

	InitOptions* pInitOptions;
	LuaStateManager *pLuaStateManager;

	shared_ptr<ResourceCache> shrdPtrResourceCache;
	shared_ptr<IResourceFile> shrdPtrResourceFile; // Will be removed in ResourceCache destructor

	LuaStateManagerUnzipFixture() {
		logger::info("Create LuaStateManagerUnzipFixture");

		pInitOptions = new InitOptions;

		shrdPtrResourceFile = make_shared<DevelopmentResourceUnzipFile>(
				pInitOptions->getRootFolder(),
				IResourceFile::ASSETS_UNZIP_FILE);

		shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, shrdPtrResourceFile);

		if (!shrdPtrResourceCache->init()) {
			logger::warning(
					"Failed to initialize resource cache!  Are your paths set up correctly?");
		}

		// pLuaStateManager = new LuaStateManager(pInitOptions->getAssetsFolder());
		pLuaStateManager = new LuaStateManager(shrdPtrResourceCache);

		shrdPtrResourceCache->registerLoader(
				script_resource_loader::createScriptResourceLoader());

	}

	~LuaStateManagerUnzipFixture() {
		logger::info("Destroy LuaStateManagerUnzipFixture");

		shrdPtrResourceCache.reset();
		shrdPtrResourceFile.reset();

		templates::safe_delete<LuaStateManager>(pLuaStateManager);
		templates::safe_delete<InitOptions>(pInitOptions);

	}
};

BOOST_FIXTURE_TEST_SUITE(LuaStateManagerUnzipSuite, LuaStateManagerUnzipFixture)

BOOST_AUTO_TEST_CASE(luaUnzipRun, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(luaUnzipRun, * unit_test::enabled()) {

	//InitOptions initOptions;
	//LuaStateManager luaStateManager(initOptions.getAssetsFolder());
	// pLuaStateManager->testLua("test.lua");

	// pLuaStateManager->temp_testLuaResourceCache("test1.lua");
	pLuaStateManager->temp_testLuaResourceCache("test.lua");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */


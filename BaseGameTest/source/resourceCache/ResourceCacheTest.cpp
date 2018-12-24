/*
 * ResourceCacheTest.cpp
 *
 *  Created on: 13 sie 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"
//#include "ActorFactoryTest.h"

//#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
//#include "../../source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/IResourceFile.h"
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceFolder.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/resourceCache/XmlResourceLoader.h"
#include "../../../BaseGame/source/resourceCache/TextFileLoader.h"
#include "../../../BaseGame/source/resourceCache/Resource.h"
#include "../../../BaseGame/source/resourceCache/ResourceHandle.h"
#include "../../../BaseGame/source/resourceCache/MessageLoader.h"

// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp> // boost::optional
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <memory> // shared_ptr, weak_ptr
#include <sstream>      // std::stringstream
#include <string> // string

using base_game::InitOptions;
using base_game::IResourceFile;
using base_game::ResourceCache;
using base_game::Resource;
using base_game::ResourceHandle;

//using base_game::BaseGameLogic;
namespace templates = base_game::templates;
namespace logger = base_game::logger;
namespace xml_resource_loader = base_game::xml_resource_loader;
namespace text_file_loader = base_game::text_file_loader;
namespace message_loader = base_game::message_loader;
namespace resource_cache = base_game::resource_cache;

//using base_game::templates::safe_delete;
using base_game::DevelopmentResourceFolder;

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;

using boost::optional;
using boost::uintmax_t;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct ResourceCacheFixture {

	InitOptions* pInitOptions;
	shared_ptr<ResourceCache> shrdPtrResourceCache;
	shared_ptr<IResourceFile> shrdPtrResourceFile; // Will be removed in ResourceCache destructor


	 ResourceCacheFixture() {
	 BOOST_TEST_MESSAGE("Setting up ResourceCacheFixture");

	 logger::info("Create ResourceCacheFixture");

	 pInitOptions = new InitOptions;
		shrdPtrResourceFile = make_shared<DevelopmentResourceFolder>(
				pInitOptions->getRootFolder(), pInitOptions->getAssetsFolder());

	 shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, shrdPtrResourceFile);

	 if (!shrdPtrResourceCache->init()) {
	 logger::warning(
	 "Failed to initialize resource cache!  Are your paths set up correctly?");
	 }

		shrdPtrResourceCache->registerLoader(
				xml_resource_loader::createXmlResourceLoader());
		shrdPtrResourceCache->registerLoader(
				text_file_loader::createTextFileLoader());

		shrdPtrResourceCache->registerLoader(
				message_loader::createMessageLoader());
	 }

	virtual ~ResourceCacheFixture() {
		BOOST_TEST_MESSAGE("Tearing down ResourceCacheFixture");
		//templates::safe_delete < BaseGameLogic > (m_pGame);

		shrdPtrResourceCache.reset();
		shrdPtrResourceFile.reset();

//		templates::safe_delete<IResourceFile>(pZipFile);
		templates::safe_delete<InitOptions>(pInitOptions);

		logger::info("Destroy ResourceCacheFixture");
//		logger::destroy();
	}

};


BOOST_FIXTURE_TEST_SUITE(ResourceCacheSuite, ResourceCacheFixture)
//BOOST_AUTO_TEST_SUITE(ActorFactorySuite)

//BOOST_AUTO_TEST_CASE(createActor) {

//BOOST_AUTO_TEST_CASE(textFileLoader, * unit_test::enabled()) {
BOOST_AUTO_TEST_CASE(textFileLoader, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	string resourceName = "texts/info.txt";

	Resource resource(resourceName);
	optional<shared_ptr<ResourceHandle>> pResourceHandle =
			shrdPtrResourceCache->getHandle(&resource);

	stringstream ss;

	ss << "resourceName: " << pResourceHandle.get()->getName();
	logger::info(ss);

	uintmax_t size = pResourceHandle.get()->getSize();
	char *resourceBuffer = pResourceHandle.get()->getBuffer();

	for (uintmax_t i = 0; i < size; i++) {

		if (*resourceBuffer == '\r') {
			ss << " CARRIAGE-RETURN";
		}

		if (*resourceBuffer == '\n') {
			ss << "LINE-FEED";
		}

		ss << *resourceBuffer;

//		*resourceBuffer++;

		resourceBuffer++;
	}

	logger::info(ss);



	BOOST_TEST(true);
}

//BOOST_AUTO_TEST_CASE(preLoad, * unit_test::enabled()) {
BOOST_AUTO_TEST_CASE(preLoad, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	stringstream ss;

	//logger::info(ss);

	//void (*callbackFunction)(int, bool&);
	//callbackFunction = resource_cache::showPreLoadProgress;

	shrdPtrResourceCache->preLoad("*.txt", resource_cache::showPreLoadProgress);

	

//	shrdPtrResourceCache->preLoad("*.txt", resource_cache::showPreLoadProgress);
	//shrdPtrResourceCache->preLoad("*.txt",
	//	resource_cache::showPreLoadProgressNoParam);

	
	
	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

}

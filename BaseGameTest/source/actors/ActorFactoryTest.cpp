/*
 * ActorFactoryTest.cpp
 *
 *  Created on: 8 kwi 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"
//#include "ActorFactoryTest.h"

//#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
//#include "../../source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/actors/ActorFactory.h"
#include "../../../BaseGame/source/actors/Actor.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/IResourceFile.h"
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceFolder.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/resourceCache/XmlResourceLoader.h"
#include "../../../BaseGame/source/resourceCache/Resource.h"
#include "../../../BaseGame/source/resourceCache/ResourceHandle.h"

// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>
#include <boost/optional.hpp> // boost::optional
#include <memory> // shared_ptr, weak_ptr
#include <sstream>      // std::stringstream
#include <string> // string

using base_game::InitOptions;
using base_game::IResourceFile;
using base_game::ResourceCache;
using base_game::Resource;
using base_game::ResourceHandle;

using base_game::ActorFactory;
using base_game::Actor;
namespace templates = base_game::templates;
namespace logger = base_game::logger;
namespace xml_resource_loader = base_game::xml_resource_loader;

using base_game::DevelopmentResourceFolder;

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;

using boost::optional;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct ActorFactoryFixture {
	InitOptions* pInitOptions;
	shared_ptr<ResourceCache> shrdPtrResourceCache;
	ActorFactory* pActorFactory;
	shared_ptr<IResourceFile> shPtrResourceFolder; // Will be removed in ResourceCache destructor

	ActorFactoryFixture() {
		BOOST_TEST_MESSAGE("Setting up ActorFactoryFixture");

		logger::info("Create ActorFactoryFixture");

		pInitOptions = new InitOptions;

		shPtrResourceFolder = make_shared<DevelopmentResourceFolder>(
				pInitOptions->getRootFolder(), pInitOptions->getAssetsFolder());

		shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, shPtrResourceFolder);

		if (!shrdPtrResourceCache->init()) {
			logger::warning(
					"Failed to initialize resource cache!  Are your paths set up correctly?");
		}

		shrdPtrResourceCache->registerLoader(
				xml_resource_loader::createXmlResourceLoader());

		pActorFactory = new ActorFactory(shrdPtrResourceCache);
		// BaseGameLogic niepotrzebne
		// Stworzyc ResourceCache i ActorFactory
		//m_pGame = new BaseGameLogic();
	}
	~ActorFactoryFixture() {
		BOOST_TEST_MESSAGE("Tearing down ActorFactoryFixture");

		shrdPtrResourceCache.reset();
		shPtrResourceFolder.reset();

		templates::safe_delete<InitOptions>(pInitOptions);
		templates::safe_delete<ActorFactory>(pActorFactory);

		logger::info("Destroy ActorFactoryFixture");
//		logger::destroy();
	}


};

BOOST_FIXTURE_TEST_SUITE(ActorFactorySuite, ActorFactoryFixture)
//BOOST_AUTO_TEST_SUITE(ActorFactorySuite)

//BOOST_AUTO_TEST_CASE(createActor) {

BOOST_AUTO_TEST_CASE(createActor, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
// BOOST_AUTO_TEST_CASE(createActor, * unit_test::enabled()) {

	string resourceName = "actors/player_character.xml";

	shared_ptr<Actor> actor = pActorFactory->createActor(resourceName);

	stringstream ss;
	ss << "Post init actor use_count: " << actor.use_count();
	logger::trace(ss);

	if (actor) {
		actor->describeYourself();
		logger::trace("Stworzono actor");
	} else {
		logger::error("Nie stworzono actor");
	}

	Resource resource(resourceName);
	optional < shared_ptr < ResourceHandle >> pResourceHandle =
			shrdPtrResourceCache->getHandle(&resource);

	ss << pResourceHandle.get()->getExtraData()->vToString();

	logger::info(ss);

	ss << "resHandleCount: " << pResourceHandle.get().use_count();
	logger::info(ss);


	actor->destroy();
	ss << "Post destroy actor use_count: " << actor.use_count();
	logger::trace(ss);

	// Destroy shared_ptr
	actor.reset();
	ss << "Post reset actor use_count: " << actor.use_count();

	logger::trace(ss);

	ss << "resHandleCount: " << pResourceHandle.get().use_count();
	logger::info(ss);

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(tempTestComponents, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(tempTestComponents, * unit_test::enable_if<MainTest::ENABLE>()) {
//BOOST_AUTO_TEST_CASE(tempTestComponents) {

	shared_ptr<Actor> actor = pActorFactory->createActor(
			"actors/player_character.xml");

	stringstream ss;
	ss << "X";

	logger::info(ss);
	if (actor) {
		actor->tempTestComponents();
		logger::trace("Stworzono actor");
	} else {
		logger::error("Nie stworzono actor");
	}


	BOOST_TEST(true);
}


BOOST_AUTO_TEST_SUITE_END()

}

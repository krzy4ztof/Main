/*
 * ActorFactoryTest.cpp
 *
 *  Created on: 8 kwi 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "ActorFactoryTest.h"

//#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
//#include "../../source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/actors/ActorFactory.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/IResourceFile.h"
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceFolder.h"
#include "../../../BaseGame/source/resourceCache/ResourceCache.h"

// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>
#include <memory> // shared_ptr, weak_ptr


using base_game::InitOptions;
using base_game::IResourceFile;
using base_game::ResourceCache;

//using base_game::BaseGameLogic;
using base_game::ActorFactory;
namespace templates = base_game::templates;
namespace logger = base_game::logger;
//using base_game::templates::safe_delete;
using base_game::DevelopmentResourceFolder;


using std::shared_ptr;
using std::make_shared;

//using base_game::ActorFactory;


/*
ActorFactoryTest::ActorFactoryTest() {
	// TODO Auto-generated constructor stub

}

ActorFactoryTest::~ActorFactoryTest() {
	// TODO Auto-generated destructor stub
}

 */

namespace base_game_test {

struct ActorFactoryFixture {
	//BaseGameLogic* m_pGame;

	InitOptions* pInitOptions;
	shared_ptr<ResourceCache> shrdPtrResourceCache;


	ActorFactory* pActorFactory;

//	IResourceFile* pZipFile = nullptr; // Will be removed in ResourceCache destructor
	shared_ptr<IResourceFile> shPtrZipFile; // Will be removed in ResourceCache destructor


//	ResourceCache(const std::string& assetsFolder, const unsigned int sizeInMb, IResourceFile *file);


//	ActorFactory(std::shared_ptr<ResourceCache> resourceCache);


	ActorFactoryFixture() {
		BOOST_TEST_MESSAGE("Setting up ActorFactoryFixture");

		logger::init("watermill-test.log");

		pInitOptions = new InitOptions;

		//pZipFile = new DevelopmentResourceFolder(pInitOptions->getRootFolder(),
		//		pInitOptions->getAssetsFolder());

		shPtrZipFile = make_shared<DevelopmentResourceFolder>(
				pInitOptions->getRootFolder(), pInitOptions->getAssetsFolder());

		shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, shPtrZipFile);


		// BaseGameLogic niepotrzebne
		// Stworzyc ResourceCache i ActorFactory
		//m_pGame = new BaseGameLogic();
		logger::info("End ActorFactoryFixture");
	}
	~ActorFactoryFixture() {
		BOOST_TEST_MESSAGE("Tearing down ActorFactoryFixture");
		//templates::safe_delete < BaseGameLogic > (m_pGame);

		shrdPtrResourceCache.reset();
		shPtrZipFile.reset();

//		templates::safe_delete<IResourceFile>(pZipFile);
		templates::safe_delete<InitOptions>(pInitOptions);
		logger::destroy();
	}


};

BOOST_FIXTURE_TEST_SUITE(ActorFactorySuite, ActorFactoryFixture)
//BOOST_AUTO_TEST_SUITE(ActorFactorySuite)

BOOST_AUTO_TEST_CASE(createActor) {

	BOOST_TEST(false);
}

BOOST_AUTO_TEST_SUITE_END()

}

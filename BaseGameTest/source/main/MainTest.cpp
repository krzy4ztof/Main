/*
 * MainTest.cpp
 *
 *  Created on: 8 kwi 2018
 *      Author: Krzysztof
 */

/*
 #include "MainTest.h"

 MainTest::MainTest() {
 // TODO Auto-generated constructor stub

 }

 MainTest::~MainTest() {
 // TODO Auto-generated destructor stub
 }
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE WatermillMainModule

#include "MainTest.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>

namespace logger = base_game::logger;

namespace base_game_test {

// const bool MainTest::ENABLE = true;

struct WatermillMainFixture {

	WatermillMainFixture() {
		logger::init("watermill-test.log");

		logger::info("Start WatermillMainFixture");
		logger::info("End WatermillMainFixture");
	}

	~WatermillMainFixture() {
		logger::info("Destroy WatermillMainFixture");

		logger::destroy();
	}
};

BOOST_GLOBAL_FIXTURE(WatermillMainFixture);

}


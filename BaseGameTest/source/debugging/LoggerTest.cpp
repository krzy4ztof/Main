/*
 * LoggerTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>
namespace logger = base_game::logger;

namespace base_game_test {

struct LoggerFixture {

	LoggerFixture() {
		logger::info("Create LoggerFixture");

}

	~LoggerFixture() {
		logger::info("Destroy LoggerFixture");
	}
};

BOOST_FIXTURE_TEST_SUITE(LoggerSuite, LoggerFixture)

BOOST_AUTO_TEST_CASE(loggerRun) {

	logger::test();

	logger::trace("Trace logged");
	logger::debug("Debug logged");
	logger::info("Information logged");
	logger::warning("Warning logged");
	logger::error("Error logged");
	logger::fatal("Fatal logged");

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

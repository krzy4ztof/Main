/*
 * LibClassTest.cpp
 *
 *  Created on: 14 kwi 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE BaseGameTest
#include <boost/test/unit_test.hpp>

#include "../../BaseGame/source/LibClass.h"
using base_game_lib::LibClass;

namespace base_game_test {

struct LibClassFixture {

	LibClass libClass;

	LibClassFixture() {
		BOOST_TEST_MESSAGE("Setting up LibClassFixture");

	}
	~LibClassFixture() {
		BOOST_TEST_MESSAGE("Tearing down LibClassFixture");
	}

};

BOOST_FIXTURE_TEST_SUITE(LibClassSuite, LibClassFixture)

BOOST_AUTO_TEST_CASE(doSth) {

	libClass.doSth();
	BOOST_TEST(false);
}

BOOST_AUTO_TEST_SUITE_END()

}

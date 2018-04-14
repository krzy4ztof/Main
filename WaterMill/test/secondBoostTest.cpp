/*
 * firstBoostTest.cpp
 *
 *  Created on: 28 mar 2018
 *      Author: Krzysztof
 */

/*
#define BOOST_TEST_MODULE My Test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test) {
	int i = 1;
	BOOST_TEST(i);
	BOOST_TEST(i == 2);
}
 */


//unit_tests.cpp
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE someModuleName
#include <boost/test/unit_test.hpp>
// #include <source/utilities/StringUtils.h>
#include "../source/utilities/StringUtils.h"


using base_game::string_utils::stringToChar;
struct template_objects {
	template_objects() {
		BOOST_TEST_MESSAGE("Setting up testing objects");
	}
	~template_objects() {
		BOOST_TEST_MESSAGE("Tearing down testing objects");
	}
};

BOOST_FIXTURE_TEST_SUITE(testSuiteName, template_objects)

BOOST_AUTO_TEST_CASE(first_test) {
	int i = 1;
	BOOST_TEST(i);
	BOOST_TEST(i == 1);
}

BOOST_AUTO_TEST_CASE(testCase1) {
	int wynik = 1;
	BOOST_CHECK(wynik);
}

BOOST_AUTO_TEST_CASE(testCase2) {
	char* wynik = stringToChar("probny");

	BOOST_CHECK(wynik);
}

 BOOST_AUTO_TEST_SUITE_END()


/*
 * StringUtilsTest.cpp
 *
 *  Created on: 8 kwi 2018
 *      Author: Krzysztof
 */

/*
#include "StringUtilsTest.h"

StringUtilsTest::StringUtilsTest() {
	// TODO Auto-generated constructor stub

}

StringUtilsTest::~StringUtilsTest() {
	// TODO Auto-generated destructor stub
}

 */

#define BOOST_TEST_DYN_LINK
// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>
// #include <source/utilities/StringUtils.h>
#include "../../source/utilities/StringUtils.h"
#include <string> // string

using std::string;
// using boost::test_tools::lexicographic;

using base_game::string_utils::stringToChar;


/*
struct template_objects {
	template_objects() {
		BOOST_TEST_MESSAGE("Setting up testing objects");
	}
	~template_objects() {
		BOOST_TEST_MESSAGE("Tearing down testing objects");
	}
};
 */

//BOOST_FIXTURE_TEST_SUITE(StringUtilsSuite, template_objects)
BOOST_AUTO_TEST_SUITE(StringUtilsSuite)


BOOST_AUTO_TEST_CASE(StringToChar) {
	string input = "StringToCheck";
	const char* expected = "StringToCheck";

	char* result = stringToChar(input);

	BOOST_TEST(result == expected);
}




/*
BOOST_AUTO_TEST_CASE(StringToChar) {
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
 */

BOOST_AUTO_TEST_SUITE_END()

/*
 * PrimeSearchTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"

#include "../../../BaseGame/source/utilities/MathUtils.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>
#include <sstream>      // std::stringstream

#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <vector> //std::vector

using std::vector;

using base_game::MathUtils;

// namespace templates = base_game::templates;
namespace logger = base_game::logger;

using std::stringstream;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct MathUtilsFixture {
	MathUtilsFixture() {
		logger::info("Create MathUtilsFixture");

	}

	~MathUtilsFixture() {
		logger::info("Destroy MathUtilsFixture");
	}
};

BOOST_FIXTURE_TEST_SUITE(MathUtilsSuite, MathUtilsFixture)

BOOST_AUTO_TEST_CASE(mathUtils, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(mathUtils1, * unit_test::enable_if<true>()) {

	stringstream ss;

	glm::vec2 point = glm::vec2(0.0f, 0.0f);

	glm::vec2 pointA = glm::vec2(-1.0f, -1.0f);
	glm::vec2 pointB = glm::vec2(-1.0f, 1.0f);
	glm::vec2 pointC = glm::vec2(1.0f, 1.0f);
	glm::vec2 pointD = glm::vec2(1.0f, -1.0f);

	vector<glm::vec2> polygon { pointA, pointB, pointC, pointD, pointA };


	bool result = MathUtils::pointInPoly(point, polygon);

	if (result) {
		logger::info("point inside polygon");
	} else {
		logger::info("point outside polygon");
	}

	logger::info("");

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_CASE(mathUtils2, * unit_test::enable_if<true>()) {

	stringstream ss;

	glm::vec2 point = glm::vec2(0.0f, 0.0f);

	glm::vec2 pointA = glm::vec2(-1.0f, -0.0f);
	glm::vec2 pointB = glm::vec2(0.0f, 1.0f);
	glm::vec2 pointC = glm::vec2(1.0f, 0.0f);
	glm::vec2 pointD = glm::vec2(0.0f, -1.0f);

	vector<glm::vec2> polygon { pointA, pointB, pointC, pointD, pointA };


	bool result = MathUtils::pointInPoly(point, polygon);

	if (result) {
		logger::info("point inside polygon");
	} else {
		logger::info("point outside polygon");
	}

	logger::info("");

	BOOST_TEST(true);

}


BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

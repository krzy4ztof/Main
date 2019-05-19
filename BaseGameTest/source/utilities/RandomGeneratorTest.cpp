/*
 * RandomGeneratorTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"

#include "../../../BaseGame/source/utilities/RandomGenerator.h"
// #include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>
#include <sstream>      // std::stringstream

using base_game::RandomGenerator;

// namespace templates = base_game::templates;
namespace logger = base_game::logger;

using std::stringstream;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct RandomGeneratorFixture {

	//RandomGenerator* pRandomGenerator;

	RandomGeneratorFixture() {
		logger::info("Create RandomGeneratorFixture");

		//	pRandomGenerator = new RandomGenerator;
	}

	~RandomGeneratorFixture() {
		logger::info("Destroy RandomGeneratorFixture");

		//templates::safe_delete<RandomGenerator>(pRandomGenerator);

	}
};

BOOST_FIXTURE_TEST_SUITE(RandomGeneratorSuite, RandomGeneratorFixture)

BOOST_AUTO_TEST_CASE(randomGeneratorRun, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	RandomGenerator rnd(1, 6, 0);
	RandomGenerator rndb(1, 6, 0);
	RandomGenerator rndc(1, 6, 0);

	stringstream ss;

	ss << "A: " << rnd.random() << ":" << rnd.random() << ":" << rnd.random()
			<< ":" << rnd.random() << ":" << rnd.random() << ":" << rnd.random()
			<< ":" << rnd.random();
	logger::info(ss);

	ss << "B: " << rndb.random() << ":" << rndb.random() << ":" << rndb.random()
			<< ":" << rndb.random() << ":" << rndb.random() << ":"
			<< rndb.random() << ":" << rndb.random();
	logger::info(ss);

	ss << "C: " << rndc.random() << ":" << rndc.random() << ":" << rndc.random()
			<< ":" << rndc.random() << ":" << rndc.random() << ":"
			<< rndc.random() << ":" << rndc.random();
	logger::info(ss);

	logger::info("");

	ss << "A: " << rnd.random() << ":" << rnd.random() << ":" << rnd.random()
			<< ":" << rnd.random() << ":" << rnd.random() << ":" << rnd.random()
			<< ":" << rnd.random();
	logger::info(ss);

	ss << "A: " << rnd.random() << ":" << rnd.random() << ":" << rnd.random()
			<< ":" << rnd.random() << ":" << rnd.random() << ":" << rnd.random()
			<< ":" << rnd.random();
	logger::info(ss);

	ss << "B: " << rndb.random() << ":" << rndb.random() << ":" << rndb.random()
			<< ":" << rndb.random() << ":" << rndb.random() << ":"
			<< rndb.random() << ":" << rndb.random();
	logger::info(ss);

	ss << "C: " << rndc.random() << ":" << rndc.random() << ":" << rndc.random()
			<< ":" << rndc.random() << ":" << rndc.random() << ":"
			<< rndc.random() << ":" << rndc.random();
	logger::info(ss);

	ss << "B: " << rndb.random() << ":" << rndb.random() << ":" << rndb.random()
			<< ":" << rndb.random() << ":" << rndb.random() << ":"
			<< rndb.random() << ":" << rndb.random();
	logger::info(ss);

	ss << "C: " << rndc.random() << ":" << rndc.random() << ":" << rndc.random()
			<< ":" << rndc.random() << ":" << rndc.random() << ":"
			<< rndc.random() << ":" << rndc.random();
	logger::info(ss);
	logger::info(ss);

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */


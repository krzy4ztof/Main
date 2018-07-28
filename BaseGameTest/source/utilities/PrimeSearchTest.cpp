/*
 * PrimeSearchTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */


#define BOOST_TEST_DYN_LINK

#include "../../../BaseGame/source/utilities/PrimeSearch.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>
#include <sstream>      // std::stringstream

using base_game::PrimeSearch;

// namespace templates = base_game::templates;
namespace logger = base_game::logger;

using std::stringstream;


namespace base_game_test {

struct PrimeSearchFixture {
	PrimeSearchFixture() {
		logger::info("Create PrimeSearchFixture");

}

	~PrimeSearchFixture() {
		logger::info("Destroy PrimeSearchFixture");
}

	void primeSearchRun(int pixels) {
		int pixelsArray[pixels];
		for (int i = 0; i < pixels; i++) {
			pixelsArray[i] = 0;
		}

		stringstream ss;

		PrimeSearch search(pixels);

		int p;
		for (int i = 0; i < pixels; i++) {
			ss << pixelsArray[i];
		}

		ss << "   [START:" << pixels << "]";

		logger::info(ss);

		while ((p = search.getNext()) != -1) {

			pixelsArray[p] = 1;

			for (int i = 0; i < pixels; i++) {
				ss << pixelsArray[i];
			}

			ss << "   [" << p << "]";
		}

		logger::info(ss);
		logger::info("");
	}

};

BOOST_FIXTURE_TEST_SUITE(PrimeSearchSuite, PrimeSearchFixture)

BOOST_AUTO_TEST_CASE(primeSearch) {

	primeSearchRun(7);
	primeSearchRun(8);
	primeSearchRun(9);
	primeSearchRun(10);

	primeSearchRun(17);
	primeSearchRun(19);


	primeSearchRun(50);

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

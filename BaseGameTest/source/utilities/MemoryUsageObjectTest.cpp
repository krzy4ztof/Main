/*
 * MemoryUsageObjectTest.cpp
 *
 *  Created on: 28 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"

#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/utilities/MemoryUsageObject.h"
#include "../../../BaseGame/source/debugging/Logger.h"

#include <boost/test/unit_test.hpp>
//#include <sstream>      // std::stringstream

using base_game::MemoryUsageObject;

namespace templates = base_game::templates;
namespace logger = base_game::logger;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct MemoryUsageObjectFixture {

	MemoryUsageObjectFixture() {
		logger::info("Create MemoryUsageObjectFixture");

		MemoryUsageObject::initMemoryPool(3, "MemoryUsageObject");

	}

	~MemoryUsageObjectFixture() {
		logger::info("Destroy MemoryUsageObjectFixture");
		MemoryUsageObject::destroyMemoryPool();
	}

};

BOOST_FIXTURE_TEST_SUITE(MemoryUsageObjectSuite, MemoryUsageObjectFixture)

BOOST_AUTO_TEST_CASE(memoryPoolRun, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	logger::info("new mem1");
	MemoryUsageObject* mem1 = new MemoryUsageObject();
	logger::info("new mem2");
	MemoryUsageObject* mem2 = new MemoryUsageObject();
	logger::info("destr mem1");
	templates::safe_delete<MemoryUsageObject>(mem1);
	logger::info("destr mem2");
	templates::safe_delete<MemoryUsageObject>(mem2);

	logger::info("new mem3");
	MemoryUsageObject* mem3 = new MemoryUsageObject();
	logger::info("new mem4");
	MemoryUsageObject* mem4 = new MemoryUsageObject();

	logger::info("new mem5");
	MemoryUsageObject* mem5 = new MemoryUsageObject();
	logger::info("new mem6");
	MemoryUsageObject* mem6 = new MemoryUsageObject();

	logger::info("destr mem6");
	templates::safe_delete<MemoryUsageObject>(mem6);
	logger::info("destr mem5");
	templates::safe_delete<MemoryUsageObject>(mem5);
	logger::info("destr mem4");
	templates::safe_delete<MemoryUsageObject>(mem4);
	logger::info("destr mem3");
	templates::safe_delete<MemoryUsageObject>(mem3);

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_CASE(memoryPoolRunSecond, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	logger::info("new SecondMem1");
	MemoryUsageObject* mem1 = new MemoryUsageObject();
	logger::info("new SecondMem2");
	MemoryUsageObject* mem2 = new MemoryUsageObject();
	logger::info("destr SecondMem1");
	templates::safe_delete<MemoryUsageObject>(mem1);
	logger::info("destr SecondMem2");
	templates::safe_delete<MemoryUsageObject>(mem2);

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_SUITE_END()

} /* namespace base_game_test */

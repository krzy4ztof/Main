/*
 * ProcessManagerTest.cpp
 *
 *  Created on: 27 lip 2018
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"

#include "../../../BaseGame/source/mainLoop/DelayProcess.h"
#include "../../../BaseGame/source/mainLoop/Process.h"
#include "../../../BaseGame/source/mainLoop/ProcessManager.h"
#include "../../../BaseGame/source/mainLoop/TempTestProcess.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"


#include <boost/test/unit_test.hpp>
#include <memory> // shared_ptr, weak_ptr

using base_game::DelayProcess;
using base_game::Process;
using base_game::ProcessManager;
using base_game::TempTestProcess;

namespace templates = base_game::templates;
namespace logger = base_game::logger;

using std::shared_ptr;
namespace unit_test = boost::unit_test;

namespace base_game_test {

struct ProcessManagerFixture {
	ProcessManager* pProcessManager;				// a game logic entity


	ProcessManagerFixture() {
		BOOST_TEST_MESSAGE("Setting up ProcessManagerFixture");

		logger::info("Create ProcessManagerFixture");

		//	logger::init("watermill-test2.log");
		pProcessManager = new ProcessManager;

	}

	~ProcessManagerFixture() {
		BOOST_TEST_MESSAGE("Tearing down ProcessManagerFixture");
		logger::info("Destroy ProcessManagerFixture");

		templates::safe_delete < ProcessManager > (pProcessManager);


//		logger::destroy();
	}

};

BOOST_FIXTURE_TEST_SUITE(ProcessManagerSuite, ProcessManagerFixture)

BOOST_AUTO_TEST_CASE(tempTestProcessManager, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {

	// state = running;

	shared_ptr<Process> pProcess1(
			new TempTestProcess("Initalize Action GROUP 1"));
	pProcessManager->attachProcess(pProcess1);
	shared_ptr<Process> pProcess2(new TempTestProcess("Second Action GROUP 1"));
	pProcess1->attachChild(pProcess2);
	shared_ptr<Process> pProcess3(new TempTestProcess("Third Action GROUP 1"));
	pProcess1->attachChild(pProcess3);
	shared_ptr<Process> pProcess4(new TempTestProcess("Last Action GROUP 1"));
	pProcess2->attachChild(pProcess4);

	shared_ptr<Process> pDelay(new DelayProcess(500)); // delay for 0.5 second
	pProcessManager->attachProcess(pDelay);

	shared_ptr<Process> pProcess1g2(
			new TempTestProcess("Initalize Action GROUP 2"));
	pDelay->attachChild(pProcess1g2);
	shared_ptr<Process> pProcess2g2(
			new TempTestProcess("Second Action GROUP 2"));
	pProcess1g2->attachChild(pProcess2g2);
	shared_ptr<Process> pProcess3g2(
			new TempTestProcess("Third Action GROUP 2"));
	pProcess2g2->attachChild(pProcess3g2);

	//vOnUpdate(0,0);

	shared_ptr<Process> pProcess1g3(
			new TempTestProcess("Initalize Action GROUP 3"));
	pProcessManager->attachProcess(pProcess1g3);
	shared_ptr<Process> pProcess2g3(
			new TempTestProcess("Second Action GROUP 3"));
	pProcess1g3->attachChild(pProcess2g3);
	shared_ptr<Process> pProcess3g3(
			new TempTestProcess("Third Action GROUP 3"));
	pProcess1g3->attachChild(pProcess3g3);

	/*
	 vOnUpdate(0,1);
	 vOnUpdate(0,2);
	 vOnUpdate(0,3);
	 vOnUpdate(0,4);
	 vOnUpdate(0,5);
	 vOnUpdate(0,6);
	 vOnUpdate(0,7);
	 */

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

}

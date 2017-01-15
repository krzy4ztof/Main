/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestClass.cpp
 * Author: Krzysztof
 *
 * Created on 29 kwietnia 2016, 21:30
 */

#include "TestClass.h"
#include "../utilities/PrimeSearch.h"
#include "../utilities/RandomGenerator.h"
#include "../utilities/MemoryUsageObject.h"
#include "../gameInitialization/Macros.h"
#include "../gameInitialization/GameMessages.h"
#include "../gameInitialization/InitOptions.h"
#include "../gameInitialization/PlayerOptions.h"
#include "../gameInitialization/GameCodeApp.h"
#include "../gameInitialization/ErrorCode.h"
#include "../luaScripting/LuaStateManager.h"
#include "../gameInitialization/VideoSystem.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"


using std::cout;
using std::endl;
using std::string;

//using base_game::memory_usage_object::safe_delete;

namespace base_game {

	void TestClass::bitwiseOrOperatorRun() {
		unsigned short int successCount = 1;
		unsigned short int failCount = 5536;
		unsigned int result = successCount << 16;
		unsigned int resultOr = ((successCount << 16) | failCount);

		cout << " << 16: " << result << " : " << resultOr << endl;


	}

	void TestClass::shiftOperatorRun() {


		//unsigned short int - 2 bytes
		// << 16 = 0

		unsigned short int successCount = 8;
		// unsigned int successCount = 8;


		//	unsigned short int failCount = 1;

		cout << successCount << endl;
		successCount = successCount << 1;
		cout << " << 1 " << successCount << endl;

		successCount = 8;
		successCount = successCount << 2;
		cout << " << 2 " << successCount << endl;

		successCount = 8;
		successCount = successCount << 3;
		cout << " << 3 " << successCount << endl;

		successCount = 8;
		cout << successCount << endl;
		successCount = successCount << 6;
		cout << " << 6 " << successCount << endl;



		successCount = 8;
		successCount = successCount << 7;
		cout << " << 7 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 8;
		cout << " << 8 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 9;
		cout << " << 9 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 10;
		cout << " << 10 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 11;
		cout << " << 11 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 12;
		cout << " << 12 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 13;
		cout << " << 13 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 14;
		cout << " << 14 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 15;
		cout << " << 15 " << successCount << endl;


		successCount = 8;
		successCount = successCount << 16;
		cout << " << 16 " << successCount << endl;


	}

	void TestClass::loggerRun() {
		logger::init();

		logger::test();

		logger::trace("Trace logged");
		logger::debug("Debug logged");
		logger::info("Information logged");
		logger::warning("Warning logged");
		logger::error("Error logged");
		logger::fatal("Fatal logged");

		logger::destroy();
	}

	/*
		void TestClass::videoFreeGlutRun() {
			VideoSystem*	videoSystem = new VideoSystem;
			videoSystem->startFreeGlut(GameCodeApp::GAME_PROCESS_NAME);

			videoSystem->startFreeGlutMainLoop();

			video_system::safe_delete(videoSystem);
		}*/

	//void TestClass:saveRun(){
	//}

	void TestClass::luaRun() {
		InitOptions initOptions;
		LuaStateManager luaStateManager(initOptions.getAssetsFolder());
		luaStateManager.testLua("test.lua");
	}

	void TestClass::messagesRun() {
		InitOptions initOptions;
		PlayerOptions playerOptions;

		string playerOptionsFilePath = initOptions.getGameFolder() + GameCodeApp::PLAYER_OPTIONS_XML;

		playerOptions.load(playerOptionsFilePath);

		try {
			GameMessages  msg(initOptions.getAssetsFolder(), playerOptions.getOption(playerOptions.LANGUAGE));
			msg.testMessages();
		} catch ( ErrorCode& error ) {
			error.informUser();
		}
	}


	void TestClass::memoryPoolRun() {

		logger::init();

		cout << "new mem1" << endl;
		MemoryUsageObject* mem1 = new MemoryUsageObject();
		cout << "new mem2" << endl;
		MemoryUsageObject* mem2 = new MemoryUsageObject();
		cout << "destr mem1" << endl;
		templates::safe_delete<MemoryUsageObject>(mem1);
		cout << "destr mem2" << endl;
		templates::safe_delete<MemoryUsageObject>(mem2);

		cout << "new mem3" << endl;
		MemoryUsageObject* mem3 = new MemoryUsageObject();
		cout << "new mem4" << endl;
		MemoryUsageObject* mem4 = new MemoryUsageObject();


		cout << "new mem5" << endl;
		MemoryUsageObject* mem5 = new MemoryUsageObject();
		cout << "new mem6" << endl;
		MemoryUsageObject* mem6 = new MemoryUsageObject();

		cout << "destr mem6" << endl;
		templates::safe_delete<MemoryUsageObject>(mem6);
		cout << "destr mem5" << endl;
		templates::safe_delete<MemoryUsageObject>(mem5);
		cout << "destr mem4" << endl;
		templates::safe_delete<MemoryUsageObject>(mem4);
		cout << "destr mem3" << endl;
		templates::safe_delete<MemoryUsageObject>(mem3);

	}


	void TestClass::randomGeneratorRun() {
		RandomGenerator rnd(1,6,0);
		RandomGenerator rndb(1,6,0);
		RandomGenerator rndc(1,6,0);

		cout << "A: " << rnd.random() << ":" << rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<endl;
		cout << "B: " << rndb.random() << ":" << rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<endl;
		cout << "C: " << rndc.random() << ":" << rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<endl;
		cout << endl;
		cout << "A: " << rnd.random() << ":" << rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<endl;
		cout << "A: " << rnd.random() << ":" << rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<rnd.random() << ":" <<endl;
		cout << "B: " << rndb.random() << ":" << rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<endl;
		cout << "C: " << rndc.random() << ":" << rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<endl;
		cout << "B: " << rndb.random() << ":" << rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<rndb.random() << ":" <<endl;
		cout << "C: " << rndc.random() << ":" << rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<rndc.random() << ":" <<endl;
		cout << endl;


	}

	void TestClass::primeSearchRun(int pixels) {
		int pixelsArray [pixels];
		for (int i=0; i<pixels; i++) {
			pixelsArray[i] = 0;
		}

		PrimeSearch search(pixels);

		int p;
		for (int i=0; i<pixels; i++) {
			cout << pixelsArray[i];
		}

		cout << "   [START:" << pixels << "]" << endl;

		while((p=search.getNext())!=-1) {

			pixelsArray[p] = 1;

			for (int i=0; i<pixels; i++) {
				cout << pixelsArray[i] ;
			}


			cout << "   [" << p << "]" << endl;
		}

		cout << endl;


	}

	void TestClass::primeSearchRun() {
		primeSearchRun(7);
		primeSearchRun(8);
		primeSearchRun(9);
		primeSearchRun(10);


		primeSearchRun(17);
		primeSearchRun(19);


		primeSearchRun(50);


	}

	void TestClass::simpleRun() {
		cout << "Water Mill Simple" << endl;
	}
}

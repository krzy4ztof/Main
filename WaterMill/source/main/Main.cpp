/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Krzysztof
 *
 * Created on 28 kwietnia 2016, 17:51
 */


//#include <cstdlib>
//#include <stdio.h>

#include<iostream> // cout, endl
//#include "../gameInitialization/Macros.h"
#include "../testClasses/TestClass.h"
//#include <sstream>      // std::stringstream
#include "GameMain.h"


//#include <windows.h>  // For MS Windows
//#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

//using std::string;
using std::cout;
using std::endl;
//using std::stringstream;


void testMain() {
	watermill::TestClass testClass;
	//testClass.simpleRun();
	//testClass.run();
	//testClass.primeSearchRun();
	//testClass.randomGeneratorRun();
	//testClass.memoryPoolRun();
	//testClass.messagesRun();
	//testClass.luaRun();
	//testClass.videoFreeGlutRun();
	testClass.loggerRun();
}

/*
int mainInit(int argc, char** argv) {

	//TODO: see
	// C:\home\myNormalFiles\GameCoding\source-archive\gamecode4\trunk\Source
	// \GCC4\GameCode4\GameCode4.cpp

	//  INT WINAPI GameCode4(HINSTANCE hInstance,
	//                 HINSTANCE hPrevInstance,
	//                 LPWSTR    lpCmdLine,
	//                 int       nCmdShow)

	watermill::logger::init();
	watermill::logger::test();


	watermill::GameCodeApp * gameCodeApp;
	gameCodeApp = new watermill::WatermillGame;

	bool resInit = gameCodeApp->initInstance();

	if (!resInit) {
		watermill::logger::error("gameCodeApp init failed");
		return 1;
	} else {
		watermill::logger::trace("gameCodeApp init succeeded");
	}

	watermill::logger::destroy();

	return 0;
}
*/

int main(int argc, char** argv) {
	/*
	 * main (int argc, char* argv[])
	 * 'char** argv'  the same as   'char* argv[]' means pointer to pointer to char
	 * argv - returns address
	 */

	//testMain();

	watermill::GameMain gameMain;
	int res = 0;
	res = gameMain.init(argc, argv);
	cout << "MAIN END" << endl;

	return res;
}


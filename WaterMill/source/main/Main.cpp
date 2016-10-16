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

using base_game::TestClass;
using watermill::GameMain;

void testMain() {
	TestClass testClass;
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

int main(int argc, char** argv) {
	/*
	 * main (int argc, char* argv[])
	 * 'char** argv'  the same as   'char* argv[]' means pointer to pointer to char
	 * argv - returns address
	 */

	//testMain();

	GameMain gameMain;
	int res = 0;
	res = gameMain.init(argc, argv);
	cout << "MAIN END" << endl;

	return res;
}


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

#ifdef __WIN64
#include <windows.h>
#endif /* __WIN64 */

#include<iostream> // cout, endl
#include "GameMain.h"

using std::cout;
using std::endl;

using watermill::GameMain;

/*
 * main (int argc, char* argv[])
 * 'char** argv'  the same as   'char* argv[]' means pointer to pointer to char
 * argv - returns address
 */

#ifdef __WIN64
// __WIN64 Only 64 bit
// MinGW64
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine,
		INT nCmdShow) {
	int argc = 0;
	char** argv = new char*[0];
#else
// MinGW
	int main(int argc, char** argv) {
#endif /* __WIN64 */
		GameMain gameMain;

		int res = 0;
		res = gameMain.init(argc, argv);
		cout << "MAIN END" << endl;

		return res;

	}

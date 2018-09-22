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

int main(int argc, char** argv) {

	GameMain gameMain;

	int res = 0;
	res = gameMain.init(argc, argv);
	cout << "MAIN END" << endl;

	return res;

}

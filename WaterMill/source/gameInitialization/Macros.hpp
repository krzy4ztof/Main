/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   lMacros.hpp
 * Author: Krzysztof
 *
 * Created on 1 maja 2016, 18:53
 */

#ifndef LMACROS_HPP
#define LMACROS_HPP

namespace watermill {
	namespace macros {

//#define SAFE_DELETE(p) { if (p) { delete (p); (p)=NULL; } }

#define GAME_TITLE  "WaterMill Game"
		// #define GAME_PROCESS_NAME  "watermill.exe"

#if defined(_DEBUG)
	#define GCC_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
	#define GCC_NEW new
#endif

#define GCC_ERROR(str) {cout << "ERROR: " << str << endl;}

#define GCC_ASSERT(expr) { if (!expr) {cout << "ASSERT " << endl;} }

	}
}

#endif /* LMACROS_HPP */


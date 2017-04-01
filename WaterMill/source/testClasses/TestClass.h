/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestClass.h
 * Author: Krzysztof
 *
 * Created on 29 kwietnia 2016, 21:37
 */

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <iostream>

//#include <boost/lambda/lambda.hpp>
//#include <iterator>
//#include <algorithm>

namespace base_game {

	class TestClass {
		public:
			// void run();
			void simpleRun();
			void primeSearchRun();
			void randomGeneratorRun();
			void memoryPoolRun();
			void messagesRun();
			void luaRun();
			//  void videoFreeGlutRun();
			void loggerRun();
			void shiftOperatorRun();
			void bitwiseOrOperatorRun();
			void writeReadZlibRun();
		protected:
			void primeSearchRun(int pixels);

		private:

	};
}
#endif /* TESTCLASS_H */


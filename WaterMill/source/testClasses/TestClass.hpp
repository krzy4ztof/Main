/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TestClass.hpp
 * Author: Krzysztof
 *
 * Created on 29 kwietnia 2016, 21:37
 */

#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP

#include <iostream>

//#include <boost/lambda/lambda.hpp>
//#include <iterator>
//#include <algorithm>

namespace watermill {

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
    protected:
        void primeSearchRun(int pixels);

    private:

    };
}
#endif /* TESTCLASS_HPP */


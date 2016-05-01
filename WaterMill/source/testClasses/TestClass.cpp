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

#include "TestClass.hpp"

using namespace std;

void TestClass::SimpleRun() {
    cout << "Water Mill Simple" << endl;
}

void TestClass::Run() {
    cout << "Water Mill" << endl;

    cout << "Type 1 2 3 + Enter " << endl;

    cout << "Press Z + Enter to end " << endl;


    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
            in(std::cin), in(), std::cout << (_1 * 3) << " ");
}

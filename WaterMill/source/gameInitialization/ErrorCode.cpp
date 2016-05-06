/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ErrorCode.cpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 13:58
 */

#include<stdio.h>
// printf
#include<string.h>
// strcpy
#include<iostream>
// cout
#include "ErrorCode.hpp"

using namespace std;
// std::string

namespace watermill {

    ErrorCode::ErrorCode() {
    }

    //ErrorCode::ErrorCode(char error_message[], int error_number) {

    ErrorCode::ErrorCode(const string& error_message, int error_number) {
        number = error_number;
        message = error_message;
        //strcpy(message, error_message);
    }

    ErrorCode::ErrorCode(const ErrorCode& orig) {
    }

    ErrorCode::~ErrorCode() {
    }

    void ErrorCode::informUser() {
        std::cout << "Error Code: " << message << "; number: " << number << std::endl;
    }
}


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

#include<iostream> // cout
#include "ErrorCode.h"
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::string;
using std::stringstream;

namespace base_game {

	ErrorCode::ErrorCode() {
	}

	//ErrorCode::ErrorCode(char error_message[], int error_number) {

	ErrorCode::ErrorCode(const string& error_message, int error_number) {
		number = error_number;
		message = error_message;
	}

	ErrorCode::ErrorCode(const ErrorCode& orig) {
	}

	ErrorCode::~ErrorCode() {
	}

	void ErrorCode::informUser() {
		stringstream ss;
		ss << "Error Code: " << message << "; number: " << number;
		logger::error(ss);
	}
}


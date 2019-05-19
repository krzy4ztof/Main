/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ErrorCode.h
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 13:58
 */

#ifndef ERRORCODE_H
#define ERRORCODE_H
#include <string>

namespace base_game {

class ErrorCode {
public:
	ErrorCode();
	ErrorCode(const std::string&, int);
	ErrorCode(const ErrorCode& orig);
	virtual ~ErrorCode();
	void informUser(void);
private:
	std::string message;
	int number;

};
}
#endif /* ERRORCODE_H */


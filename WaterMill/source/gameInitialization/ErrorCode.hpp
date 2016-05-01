/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ErrorCode.hpp
 * Author: Krzysztof
 *
 * Created on 30 kwietnia 2016, 13:58
 */

#ifndef ERRORCODE_HPP
#define ERRORCODE_HPP

class ErrorCode {
public:
    ErrorCode();
    ErrorCode(char[], int);
    ErrorCode(const ErrorCode& orig);
    virtual ~ErrorCode();
    void informUser(void);
private:
    char message[256];
    int number;

};

#endif /* ERRORCODE_HPP */


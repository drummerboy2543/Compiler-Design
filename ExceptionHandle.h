/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExceptionHangle.h
 * Author: Andrew
 *
 * Created on February 10, 2017, 7:45 PM
 */
#include <string>
#include <iostream>
#include <cassert>
#define Type_Error 0
#define Arithmetic_Error 1
#ifndef EXCEPTIONHANGLE_H
#define EXCEPTIONHANGLE_H
/*
 This Function displays a Exceptions and stops the program due to a compiler error. 
 *  The ExceptionType is used to determine the type of exception we are having which changes the output.
 *  The Exception message is the message that will display in the exception based on the input.
 *  If the program stops it will be called by this function.
 */
void ExceptionThrow(int ExecptionType,std::string ExceptionMessage){

    switch (ExecptionType){
    
        case Type_Error: {std::cout<< "TYPE ERROR: "<<ExceptionMessage;
        assert(0);
        }
        break;
        case Arithmetic_Error: {std::cout<<" Arithmitic Error"<<ExceptionMessage;
        assert(0);}
    }


}

#endif /* EXCEPTIONHANGLE_H */


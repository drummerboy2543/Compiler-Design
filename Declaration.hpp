/* 
 * File:   Declaration.hpp
 * Author: student16
 *
 * Created on April 15, 2017, 8:09 PM
 */

#ifndef DECLARATION_HPP
#define	DECLARATION_HPP
#include "ast.hpp"
#include <string>
class Declaration {
public:
    std::string Name="";
};

class Var_Declaration:Declaration{
    EXPR* Variable;
    Var_Declaration(std::string n, EXPR* Var){
        Name=n;
        Variable=Var;
    }
};

class Func_Declaration:Declaration{

};
#endif	/* DECLARATION_HPP */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   token.hpp
 * Author: Andrew
 *
 * Created on March 8, 2017, 11:38 AM
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <sstream>
#include <bitset>

enum Token_Types {
    Int_Token, // integer token
    Bool_Token, // Boolean token
    Plus_Token, // + token
    Minus_Token, // - token
    Mul_Token, // * token
    Div_Token, // / token
    Mod_Token, // % token
    And_Token, // & token
    Or_Token, // | token
    Xor_Token, // ^ token
    Not_Token, // ! token
    Equal_Token, // = token
    Not_Equal_Token, // != token
    LT_Token, // < token
    GT_Token, // > token
    Lteq_Token, // <= token
    Gteq_Token, // >= token
    Question_Token, // ? token
    Colon_Token, // : token
    EQ_EQ_Token, // == token
    And_And_Token, // && token
    Or_Or_Token, // || token
    LPar_Token, // ( token
    RPar_Token, // ) token
    Tilda_Token, // ~ token
    EndOfFile_Token // Eof Token
};

class Token {
protected:
    std::string Token_String;

    ~Token() {
        ;
    }
public:
    int Token_Type;

    virtual std::string Send_Value() {
    };

    std::string Get_Token_String(int val);

    std::string Print_Token() {
        return Token_String;
    }
};

class Boolean_Token : public Token {
    bool value;
public:

    Boolean_Token(bool v) : value(v) {
        Token_Type = Bool_Token;
        Token_String = Get_Token_String(Bool_Token);
    };

    std::string Send_Value() {
        if (value) {
            return "true";
        } else {
            return "false";
        };
    };
    bool Send_Bool_Value(){
        return value;
    }
};

class Integer_Token : public Token {
    int value;
    int opt;
public:

    Integer_Token(int i,int op) : value(i) {
        opt=op;
        Token_Type = Int_Token;
        Token_String = Get_Token_String(Int_Token);
    }

    std::string Send_Value() {
        std::stringstream ss;
        if (opt == 0) {
            
            ss << value;
        } else if (opt == 1) {
            ss << "0x" << std::hex << value;
        } else if (opt == 2) {
            std::string s = "0b"+std::bitset< 32 >(value).to_string();
            return s;
        } else {

            std::cout<<"Error no option for int ";
        }
        std::string str = ss.str();
        return str;
    };
   int Send_Int_Value(){
       return value;
    }
};

class Punc_Token : public Token {
public:

    Punc_Token(Token_Types Val) {
        Token_Type=Val;
        Token_String = Get_Token_String(Val);
    }

};

std::string Token::Get_Token_String(int val) {
    switch (val) {

        case Int_Token: // integer token
            return "Integer Token";
        case Bool_Token: // Boolean token
            return "Boolean Token";
        case Plus_Token: // + token
            return "Plus sign Token";
        case Minus_Token: // - token
            return "Minus sign Token";
        case Mul_Token: // * token
            return "Multiply Token";
        case Div_Token: // / token
            return "Divide Token";
        case Mod_Token: // % token
            return "Modulus Token";
        case And_Token: // & token
            return "And Token";
        case Or_Token: // | token
            return "Or Token";
        case Xor_Token: // ^ token
            return "Xor Token";
        case Not_Token: // ! token
            return "Not Token";
        case Equal_Token: // = token
            return "Equal Token";
        case Not_Equal_Token: // != token
            return "Not Equal Token";
        case LT_Token: // < token
            return "Less Than Token";
        case GT_Token: // > token
            return "Greater Than Token";
        case Lteq_Token: // <= token
            return "Less Than Or Equal To Token";
        case Gteq_Token: // >= token
            return "Greater Than Or Equal To Token";
        case Question_Token: // ? token
            return "Question Token";
        case Colon_Token: // : token
            return "Colon Token";
        case EQ_EQ_Token: // == token
            return "Double Equal Token";
        case And_And_Token: // && token
            return "Double And Token";
        case Or_Or_Token: // || token
            return "Double Or Token";
        case LPar_Token: // ( token
            return "Left Parenthese Token";
        case RPar_Token: // ) token
            return "Right Parenthese_Token";
        case Tilda_Token: // ~ token
            return "Tilda Token";
        case EndOfFile_Token:
            return " End Of File Token"; // Eof Token
        default: return "ERRROR TOKEN NOT FOUND";
    }

}



#endif /* TOKEN_HPP */


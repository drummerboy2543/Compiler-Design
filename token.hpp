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
    Var_Token, //Token For Variables
    Var_Ref_Token, //Token For refrence to Variables
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
    Int_KW_Token, // "int" Keyword Token
    Bool_KW_Token, // "bool" Keyword Token
    Var_KW_Token, // "var" Keyword Token
    Null_KW_Token, // "null" Keyword Token
    Break_KW_Token, // 'break' keyword token
    Continue_KW_Token, // 'continue' keyword token
    Def_KW_Token, // 'def' keyword token
    Else_KW_Token, // 'else' keyword token
    If_KW_Token, // 'if' keyword token
    Return_KW_Token, // 'return' keyword token
    While_KW_Token, // 'while' keyword token
    EndOfFile_Token, // Eof Token
    Semi_Token, // ; token
    L_Brace_Token,
    R_Brace_Token

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

    virtual std::string Send_Type() {
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

    bool Send_Bool_Value() {
        return value;
    }
};

class Integer_Token : public Token {
    int value;
    int opt;
public:

    Integer_Token(int i, int op) : value(i) {
        opt = op;
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
            std::string s = "0b" + std::bitset< 32 >(value).to_string();
            return s;
        } else {

            std::cout << "Error no option for int ";
        }
        std::string str = ss.str();
        return str;
    };

    int Send_Int_Value() {
        return value;
    }
};

class Variable_Token : public Token {
    std::string Token_Content;
public:

    Variable_Token(std::string Variable_Name) {

        Token_Content = Variable_Name;
        Token_Type = Var_Token;
        Token_String = Get_Token_String(Var_Token);
    }

    std::string Send_Value() {
        return Token_Content;
    }
};


class Punc_Token : public Token {
public:

    Punc_Token(Token_Types Val) {
        Token_Type = Val;
        Token_String = Get_Token_String(Val);
    }

}

;

std::string Token::Get_Token_String(int val) {
    switch (val) {

        case Int_Token: // integer token
            return "Integer Token";
        case Bool_Token: // Boolean token
            return "Boolean sToken";
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
        case Var_Token:
            return "Variable Token";
        case Var_Ref_Token:
            "Variable Reference Token";
        case EndOfFile_Token:
            return " End Of File Token"; // Eof Token
        case Int_KW_Token: // 'int' keyword token
            return "Integer Keyword Token";
        case Bool_KW_Token: // 'bool' keyword token
            return "Boolean Keyword Token";
        case Var_KW_Token: // 'var' keyword token
            return "Var Keyword Token";
        case Null_KW_Token: // 'null' keyword token
            return "null Keyword Token";
        case Break_KW_Token: // 'break' keyword token
            return "break Keyword Token";
        case Continue_KW_Token: // 'continue' keyword token
            return "continue Keyword Token";
        case Def_KW_Token: // 'def' keyword token
            return "def Keyword Token";
        case Else_KW_Token: // 'else' keyword token
            return "else Keyword Token";
        case If_KW_Token: // 'if' keyword token
            return "if Keyword Token";
        case Return_KW_Token: // 'return' keyword token
            return "return Keyword Token";
        case While_KW_Token: // 'while' keyword token
            return "while Keyword Token";
        case Semi_Token:
            return "Semicolon Token";
        case L_Brace_Token:
            return "Left Brace";
        case R_Brace_Token:
            return "Right Brace";
        default: return "ERRROR TOKEN NOT FOUND";
    }

}



#endif /* TOKEN_HPP */


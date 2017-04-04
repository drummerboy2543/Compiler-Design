/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lexer.hpp
 * Author: Andrew
 *
 * Created on March 8, 2017, 11:38 AM
 */
#include "token.hpp"
#include "ExceptionHandle.h"
#include <iostream>
#include <vector>
#include<sstream>
#ifndef LEXER_HPP
#define LEXER_HPP
#define Decimal 0
#define Hex 1
#define Binary 2
#define Syntax_ErrorL 3
class Lexer {
    int display_option=Decimal;
    // Vector to hold all tokens created
    std::vector <Token*> Vector_Of_All_Tokens;
    std::string::iterator Start_String;
    std::string::iterator End_String;
    //Function to clear comments
    std::string Clear_Comments(std::string s);
    //Function to check boolean for a boolean token
    void checkbool(bool start_Letter);
    //Function to check Interger for a integer token
   void  Check_Num();
    bool Consume_Whitespace();
    //Increments the string ittereator
    void Consume() {
        Start_String++;
    }
    char Look_Ahead() {
        return *Start_String;
    }
   void Next();
public:


//Returns a vector of tokens after the lexer lexes for the parser to parse
    std::vector <Token*>  Read_Line(std::string Input_Str,int option);
    void Print();
    void Clear_Vec(){
    Vector_Of_All_Tokens.clear();
    }
};

std::string Lexer::Clear_Comments(std::string Input_str) {
    size_t comment_start = Input_str.find_first_of('#');
    if (comment_start != -1) {
        Input_str.erase(comment_start);
        return Input_str;

    } else {
        return Input_str;
    }

}
//Main function sets the itterators and then calls next until the string is has been parsed.
std::vector <Token*> Lexer::Read_Line(std::string Input_Str,int option) {
    display_option=option;
    std::string Trimed_Str;
    Trimed_Str = Clear_Comments(Input_Str); //Get rid of any comments
     
    Start_String = Trimed_Str.begin();
   
    End_String = Trimed_Str.end();
   
    while(Start_String<End_String){
    Next();} //Call next until end of line.
    return Vector_Of_All_Tokens;
}

bool Lexer::Consume_Whitespace() {
    while (Start_String != End_String) {
        switch (*Start_String) {
            case ' ':
            case ',':
                Consume();
                break;
            default: return false;
        }
    }
    return true;
}
//Goes through and determines the token for a char/symbol
void Lexer::Next() {
    bool Has_Line_Finished =false;
   Has_Line_Finished= Consume_Whitespace();
   if (Has_Line_Finished){
       return;
        }
    switch (Look_Ahead()) {
        
        case 't':
        case'T':
            checkbool(true); //Verify it is a true boolean
            break;
            case 'f':
        case'F':
                checkbool(false); //Verify it is a false boolean
                break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            Check_Num(); // Get the whole number.
            break;
                                 
        case '+':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Plus_Token));
            break;
        case '-':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Minus_Token));
            break;
        case '*':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Mul_Token));
            break;
        case '/':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Div_Token));
            break;

        case '%':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Mod_Token)); // % token
            break;
        case '&':
            Consume();
            if (Look_Ahead() == '&') {// & token
                Consume();
                Vector_Of_All_Tokens.push_back(new Punc_Token(And_And_Token));
            } else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(And_Token));
            }
            break;
        case '|':
            Consume();
            if (Look_Ahead() == '|') {
                Consume();
                Vector_Of_All_Tokens.push_back(new Punc_Token(Or_Or_Token));
            }
            else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(Or_Token));
            }
            break;

        case '^':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Xor_Token));
            break;

        case '=':
            Consume();
            if (Look_Ahead() == '=') {
                Consume();
                Vector_Of_All_Tokens.push_back(new Punc_Token(Equal_Token));
            } else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(EQ_EQ_Token));
            }
            break;

        case '!':
            Consume();
            if (Look_Ahead() == '=') {
                Consume();
                Vector_Of_All_Tokens.push_back(new Punc_Token(Not_Equal_Token));
            } else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(Not_Token));
            }
            break;

        case '<':
            Consume();
            if (Look_Ahead() == '=') {
                Consume();
                Vector_Of_All_Tokens.push_back(new Punc_Token(Lteq_Token));
            } else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(LT_Token));
            }

            break;
        case '>':
            Consume();
            if (Look_Ahead() == '=') {
                Consume();
                Vector_Of_All_Tokens.push_back(new Punc_Token(Gteq_Token));
            } else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(GT_Token));
            }
            break;

        case '?':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Question_Token));
            break;
        case ':':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Colon_Token));
            break;
        case '(':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(LPar_Token));
            break;
        case ')':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(RPar_Token));
            break;
        case '~':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Tilda_Token));
            break;
        default:
		//Throw a exception invalid token
        ExceptionThrow(Syntax_ErrorL, " No Token");
        Consume();
        break;

    };
}

void Lexer::checkbool(bool start_Letter) {

    if (start_Letter) {
        Consume();
        if (Look_Ahead() == 'r' || Look_Ahead() == 'R') {
            Consume();
            if (Look_Ahead() == 'u' || Look_Ahead() == 'U') {
                Consume();

                if (Look_Ahead() == 'e' || Look_Ahead() == 'E') {
                    Consume();
                    Vector_Of_All_Tokens.push_back(new Boolean_Token(true));
                    return;
                }
            }
        }



    } else {
        Consume();
        if (Look_Ahead() == 'a' || Look_Ahead() == 'A') {
            Consume();
            if (Look_Ahead() == 'l' || Look_Ahead() == 'L') {
                Consume();
                if (Look_Ahead() == 's' || Look_Ahead() == 'S') {
                    Consume();
                    if (Look_Ahead() == 'e' || Look_Ahead() == 'E') {
                        Consume();
                      Vector_Of_All_Tokens.push_back(new Boolean_Token(false));
                      return;
                    }

                }

            }
        }
    }
	//Throw a Lexer exception invalid construction of boolean.
    ExceptionThrow(Syntax_ErrorL, " Failed to construct bool");
}

void Lexer::Check_Num(){
    std::string Sring_Number;
while (std::isdigit(Look_Ahead())){
    Sring_Number=Sring_Number+Look_Ahead();
    Consume();
   
}

      std::istringstream str(Sring_Number);
      int numerical_Number;
        str >>numerical_Number ;
    
Vector_Of_All_Tokens.push_back(new Integer_Token(numerical_Number,display_option));
}


   void Lexer::Print(){
       std::vector <Token*>::iterator Start_Vec;
Token* Temp;
std::string output;
       for (Start_Vec=Vector_Of_All_Tokens.begin();Start_Vec < Vector_Of_All_Tokens.end();Start_Vec++){
       
     Temp=  (*Start_Vec);
     output=Temp->Print_Token();
     
     if ((Temp->Token_Type==0)||(Temp->Token_Type==1)){
     std::cout<<" The Token is a "<<output<<"and the value is "<<Temp->Send_Value()<<" \n";
       }
     else{
    std:: cout<<" The Token is "<<output<<"\n";}
       }
    }

   
   

#endif /* LEXER_HPP */


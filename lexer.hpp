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
#include <unordered_map>
#ifndef LEXER_HPP
#define LEXER_HPP
#define boolean_type 0
#define integer_type 1
#define new_var 0
#define old_var 1
#define Decimal 0
#define Hex 1
#define Binary 2
#define Syntax_ErrorL 3
class Lexer {
    int display_option=Decimal;
    // Vector to hold all tokens created
    std::vector <Token*> Vector_Of_All_Tokens;
     enum KW_Token {
        Int_KW,
        Bool_KW,
        True_KW,
        False_KW,
        Null_KW,
        Var_KW,
        Break_KW,
        Continue_KW,
        Def_KW,
        Else_KW,
        If_KW,
        Return_KW,
        While_KW
     };
    std::unordered_map <std::string,KW_Token > Key_Words= {
        {"int",Int_KW},
        {"bool",Bool_KW},
        {"true",True_KW},
        {"false",False_KW},
        {"null",Null_KW},
        {"var",Var_KW},
        {"break",Break_KW},
        {"continue",Continue_KW},
        {"def",Def_KW},
        {"else",Else_KW},
        {"if",If_KW},
        {"return",Return_KW},
        {"while",While_KW}
    };
    std::string::iterator Start_String;
    std::string::iterator End_String;
    //Function to clear comments
    std::string Clear_Comments(std::string s);
    //Function to check boolean for a boolean token
    void checkbool(bool start_Letter);
    //Function to check Interger for a integer token
   void  Check_Num();
   bool Check_Keyword(std::string var_name);
    void Check_New_Variable();
    void Lex_Other();
 
    bool empty_line_space=true;

    void Lex_Type();
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


    std::vector <Token*>  Read_Line(std::string Input_Str,int option);
    void Print();
    void Clear_Vec(){
    Vector_Of_All_Tokens.clear();
    }
     
       std::string Get_Option(std::string Input_Str);
        bool All_White_Space();
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
    empty_line_space=true;
    display_option=option;
    std::string Trimed_Str;
    Trimed_Str = Clear_Comments(Input_Str); //Get rid of any comments
     
    Start_String = Trimed_Str.begin();
   
    End_String = Trimed_Str.end();
   
    while(Start_String<End_String){
    Next();
  } //Call next until end of line.
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
   empty_line_space=false;
    switch (Look_Ahead()) {
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
                Vector_Of_All_Tokens.push_back(new Punc_Token(EQ_EQ_Token));
            } else {
                Vector_Of_All_Tokens.push_back(new Punc_Token(Equal_Token));
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
             case ';':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(Semi_Token));
            break;
              case '{':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(L_Brace_Token));
            break;
              case '}':
            Consume();
            Vector_Of_All_Tokens.push_back(new Punc_Token(R_Brace_Token));
            break;
        case 'a'...'z':
        case 'A' ... 'Z':
        case '_': 
            Lex_Other();
            break;
        default:
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
    ExceptionThrow(Syntax_ErrorL, " Failed to construct bool");
}

void Lexer::Check_New_Variable() {
    Consume();
    if (Look_Ahead() == 'a') {
        Consume();
        if (Look_Ahead() == 'r') {
            Consume();
            if (Look_Ahead() == ' ') {
                Consume();
                while (Look_Ahead() == ' '){
                 Consume();
                }
                Lex_Type();
                return;
            }
        }
    }
    
    ExceptionThrow(Syntax_ErrorL, " Failed to construct var");
}



void Lexer::Lex_Type() {
    if (Look_Ahead() == 'i') {
        Consume();
        if (Look_Ahead() == 'n') {
            Consume();
            if (Look_Ahead() == 't') {
                Consume();
            if (Look_Ahead() == ' ') {
                Consume();
                while (Look_Ahead() == ' '){
                 Consume();
                }
               // Lex_Variable(new_var,integer_type);
                return;
            }
        }
        }
    }
        else if (Look_Ahead() == 'b'){
            Consume();
        
        if (Look_Ahead() == 'o'){
            Consume();
        }
        if (Look_Ahead() == 'o'){
            Consume();
        }
        if (Look_Ahead() == 'l'){
            Consume();
        }
        if (Look_Ahead() == ' '){
            Consume();
        }
        while (Look_Ahead() == ' '){
                 Consume();
                }
               // Lex_Variable(new_var,boolean_type);
        return;
    }


    ExceptionThrow(Syntax_ErrorL, " Failed to construct keyword for var");
}

void Lexer::Lex_Other() {
    bool is_key_word = false;

    std::string Variable_Name = "";
    if (std::isalpha(Look_Ahead()) || Look_Ahead() == '_') {
        Variable_Name = Variable_Name + Look_Ahead();
        Consume();
        while ((std::isdigit(Look_Ahead())) || (std::isalpha(Look_Ahead())) || (Look_Ahead() == '_')) {
            Variable_Name = Variable_Name + Look_Ahead();

            Consume();
        }
        is_key_word = Check_Keyword(Variable_Name);
        if (is_key_word == false) {
            Vector_Of_All_Tokens.push_back(new Variable_Token(Variable_Name));
        }
    } else {
        ExceptionThrow(Syntax_ErrorL, " Failed to construct a variable");
    }
}

bool Lexer::Check_Keyword(std::string var_name) {
    std::unordered_map <std::string, KW_Token >::iterator val;

    val = Key_Words.find(var_name);
    if (val == Key_Words.end()) {
        return false;
    } else {
        KW_Token Tok_Type;
        Tok_Type = val->second;
        switch (Tok_Type) {
            case Int_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Int_KW_Token));
                break;
            case Bool_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Bool_KW_Token));
                break;
            case Null_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Null_KW_Token));
                break;
            case True_KW:
                Vector_Of_All_Tokens.push_back(new Boolean_Token(true));
                break;
            case False_KW:
                Vector_Of_All_Tokens.push_back(new Boolean_Token(false));
                break;
            case Var_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Var_KW_Token));
                break;
            case Break_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Break_KW_Token));
                break;
            case Continue_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Continue_KW_Token));
                break;
            case Def_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Def_KW_Token));
                break;
            case Else_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Else_KW_Token));
                break;
            case If_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(If_KW_Token));
                break;
            case Return_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(Return_KW_Token));
                break;
            case While_KW:
                Vector_Of_All_Tokens.push_back(new Punc_Token(While_KW_Token));
                break;

        }
    }
    return true;
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
     
     if ((Temp->Token_Type<=Var_Token)){
     std::cout<<" The Token is a "<<output<<" and the value is "<<Temp->Send_Value()<<" \n";
       }
     else{
    std:: cout<<" The Token is "<<output<<"\n";}
       }
    }

   
      std::string Lexer::Get_Option(std::string Input_Str){
          std::string Trimed_Str="";
Trimed_Str = Clear_Comments(Input_Str); //Get rid of any comments       
 std:: cout<<" The char is "<<Trimed_Str<<"\n \n \n";
      return Trimed_Str;
    }
     bool Lexer::All_White_Space(){
      
          return empty_line_space;
      }
   
   

#endif /* LEXER_HPP */


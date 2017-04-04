/* 
 * File:   Parser.hpp
 * Author: student16
 *
 * Created on April 3, 2017, 8:35 PM
 */

#ifndef PARSER_HPP
#define	PARSER_HPP
#include "ast.hpp"
#include "lexer.hpp"
#include "Print.hpp"
#include "Eval.hpp"
#define Syntax_Error 2

class Parser {
    std::vector <Token*> Parsing_Token_Vect;
    std::vector <Token*>::iterator Token_Itter;

    EXPR* Final_Expression;
    bool End_OF_Line() {
        if (Token_Itter == Parsing_Token_Vect.end()) {
            return true;
        } else {
            return false;
        }
    }

    bool has_parsed=false;
    Token* Look_Ahead();
    Token* Look_Multiple_Ahead(int amount);

    void Consume() {
        Token_Itter = Token_Itter + 1;
    }
    bool Match_Statement(Token_Types type, Token* Current_Token);
    bool Match_Statement(Token_Types type);
    void Parse();

    //Expressions

    EXPR * Parse_Expression();
    EXPR * Parse_Conditonal_Expression();
    EXPR * Parse_Or_Expression();
    EXPR * Parse_And_Expression();
    EXPR * Parse_Bit_Or_Expression();
    EXPR * Parse_Bit_Xor_Expression();
    EXPR * Parse_Bit_And_Expression();
    EXPR * Parse_Equality_Expression();
    EXPR * Parse_Ordering_Expression();
    EXPR * Parse_Additive_Expression();
    EXPR * Parse_Multplicative_Expression();
    EXPR * Parse_Unary_Expression();
    EXPR * Parse_Primary_Expression();
public:
        Parser(std::vector<Token*> Lex_Tokens) {
        Parsing_Token_Vect = Lex_Tokens;
        Token_Itter = Parsing_Token_Vect.begin();
    }
    void Parser_Print();
    int Parser_Eval(int option);

};
void Parser::Parser_Print(){
    if (!has_parsed){
       Parse();
    has_parsed=true;}
Print(Final_Expression);
}
 int Parser::Parser_Eval(int option){ 
     int value;
      if (!has_parsed){
       Parse();
    has_parsed=true;}
value=Eval(Final_Expression);

if  (Final_Expression->EXPR_type==0){
        if (value==0){
        std::cout<<"\nThe Value it equals is false";
        }
        else {
        std::cout<<"\nThe Value it equals is true";
        }
    }
    else{
                  if (option==0){
                   std::cout<<"\nThe Value it equals is "<<value;}
                  else if (option==1){
                      std::cout<<"\nThe Value it equals is 0x"<<std::hex <<value;
                  }
                  else if (option==2){
                       std::string s = "0b"+std::bitset< 32 >(value).to_string();
                   std::cout<<"\nThe Value it equals is 0b"<<s;
                  
                  }
    }
return value;
    }
   void  Parser::Parse() {
    EXPR* Temp_Expr;
    Temp_Expr = Parse_Expression();
    
    Final_Expression= Temp_Expr;
    ;
}
Token* Parser::Look_Ahead() {
    if (End_OF_Line() == true) {

        return new Punc_Token(EndOfFile_Token); //Not File but line close enough.
    } else {
        return *Token_Itter;
    }
};

Token* Parser::Look_Multiple_Ahead(int amount) {
    std::vector <Token*>::iterator Temp_Itter;
    Temp_Itter = Token_Itter;
    for (int count = 0; count < amount; count++) {

        //Making sure we are not skipping over eof.
        if (Temp_Itter == Parsing_Token_Vect.end()) {
            return NULL;
        }

        Temp_Itter = Temp_Itter + 1;
    }
    return *Temp_Itter;
}

bool Parser::Match_Statement(Token_Types type, Token* Current_Token) {
    if (Current_Token->Token_Type == type) {
        return true;
    } else {
        return false;
    }

}

bool Parser::Match_Statement(Token_Types type) {
    if (Look_Ahead()->Token_Type == type) {
        return true;
    } else {
        return false;
    }
}



EXPR * Parser::Parse_Expression() {
    return Parse_Conditonal_Expression();
    ;
}

EXPR * Parser::Parse_Conditonal_Expression() {
    EXPR* E1;
    E1 = Parse_Or_Expression();
    while (true) {
        if (Match_Statement(Question_Token)) {
            Consume();
            EXPR* E2 = Parse_Expression();
            if (Match_Statement(Colon_Token)) {
                Consume();
                EXPR* E3 = Parse_Expression();
                E1 = new Cond_EXPR(E1, E2, E3);
            }
        }
        else {
            return E1;
        }
    }

}

EXPR * Parser::Parse_Or_Expression() {
    EXPR* E1;
    E1 = Parse_And_Expression();
    while (true) {
        if (Match_Statement(Or_Or_Token)) {
            Consume();
            EXPR* E2 = Parse_And_Expression();
            E1 = new Or_EXPR(E1, E2);

        } else {
            return E1;
        }
    }
}

EXPR * Parser::Parse_And_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Bit_Or_Expression();
    while (true) {
        if (Match_Statement(And_And_Token)) {
            Consume();
            E2 = Parse_Bit_Or_Expression();
            E1 = new And_EXPR(E1, E2);
        } else {
            return E1;
        }

    }

}

EXPR * Parser::Parse_Bit_Or_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Bit_Xor_Expression();
    while (true) {
        if (Match_Statement(Or_Token)) {
            Consume();
            E2 = Parse_Bit_Xor_Expression();
            E1 = new Bit_Or_EXPR(E1, E2);
        } else {
            return E1;
        }

    }
}

EXPR * Parser::Parse_Bit_Xor_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Bit_And_Expression();
    while (true) {
        if (Match_Statement(Xor_Token)) {
            Consume();
            E2 = Parse_Bit_And_Expression();
            E1 = new Xor_EXPR(E1, E2);
        } else {
            return E1;
        }

    }
}

EXPR * Parser::Parse_Bit_And_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Equality_Expression();
    while (true) {
        if (Match_Statement(And_Token)) {
            Consume();
            E2 = Parse_Equality_Expression();
            E1 = new Bit_And_EXPR(E1, E2);
        }
        else {
            return E1;
        }

    }
}
// Includes Equal, Not Equal

EXPR * Parser::Parse_Equality_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Ordering_Expression();
    while (true) {
        if (Match_Statement(EQ_EQ_Token)) {
            Consume();
            E2 = Parse_Ordering_Expression();
            E1 = new Eq_EXPR(E1, E2);
        }
        else if (Match_Statement(Not_Equal_Token)) {

            Consume();
            E2 = Parse_Ordering_Expression();
            E1 = new Neq_EXPR(E1, E2);
        }
        else {
            return E1;
        }

    }
}
// Less than greater than, Less_Eq Greater_eq

EXPR * Parser::Parse_Ordering_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Additive_Expression();
    while (true) {
        if (Match_Statement(LT_Token)) {
            Consume();
            E2 = Parse_Additive_Expression();
            E1 = new Lt_EXPR(E1, E2);
        }
        else if (Match_Statement(GT_Token)) {

            Consume();
            E2 = Parse_Additive_Expression();
            E1 = new Gt_EXPR(E1, E2);
        } else if (Match_Statement(Lteq_Token)) {

            Consume();
            E2 = Parse_Additive_Expression();
            E1 = new Lteq_EXPR(E1, E2);
        } else if (Match_Statement(Gteq_Token)) {

            Consume();
            E2 = Parse_Additive_Expression();
            E1 = new Gteq_EXPR(E1, E2);
        }
        else {
            return E1;
        }

    }



}
//Add and Subtract

EXPR * Parser::Parse_Additive_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Multplicative_Expression();
    while (true) {
        if (Match_Statement(Plus_Token)) {
            Consume();
            E2 = Parse_Multplicative_Expression();
            E1 = new Add_EXPR(E1, E2);
        }
        else if (Match_Statement(Minus_Token)) {

            Consume();
            E2 = Parse_Multplicative_Expression();
            E1 = new Minus_EXPR(E1, E2);
        }
        else {
            return E1;
        }

    }
}
// Multiply Divide Modulate

EXPR * Parser::Parse_Multplicative_Expression() {
    EXPR* E1;
    EXPR* E2;
    E1 = Parse_Unary_Expression();
    while (true) {
        if (Match_Statement(Mul_Token)) {
            Consume();
            E2 = Parse_Unary_Expression();
            E1 = new Mul_EXPR(E1, E2);
        }
        else if (Match_Statement(Div_Token)) {
            Consume();
            E2 = Parse_Unary_Expression();
            E1 = new Div_EXPR(E1, E2);
        } else if (Match_Statement(Mod_Token)) {
            Consume();
            E2 = Parse_Unary_Expression();
            E1 = new Mod_EXPR(E1, E2);
        } else {
            return E1;
        }

    }

}

EXPR * Parser::Parse_Unary_Expression() {
    EXPR* E1;
    if (Match_Statement(Tilda_Token)) {
        Consume();
        E1 = Parse_Unary_Expression();
        return new Bit_Not_EXPR(E1);
    }
    else if (Match_Statement(Not_Token)) {
        Consume();
        E1 = Parse_Unary_Expression();
        return new Not_EXPR(E1);
    } else if (Match_Statement(Minus_Token)) {
        Consume();
        E1 = Parse_Unary_Expression();
        return new Negation_EXPR(E1);
    } else {
        return Parse_Primary_Expression();
    }


}

EXPR * Parser::Parse_Primary_Expression() {
    Token* Temp;
    if (Match_Statement(Bool_Token)) {

        Boolean_Token* BE1;
        Temp = Look_Ahead();
        BE1 = dynamic_cast<Boolean_Token*> (Temp);
        Consume();
        return new Bool_EXPR(BE1->Send_Bool_Value());
    } else if (Match_Statement(Int_Token)) {
        Integer_Token* IE1;
        Temp = Look_Ahead();
        IE1 = dynamic_cast<Integer_Token*> (Temp);
        Consume();
        return new Int_EXPR(IE1->Send_Int_Value());
    } 
    else if (Match_Statement(LPar_Token)) {
        Consume();
        EXPR* E1 = Parse_Expression();
        if (Match_Statement(RPar_Token)) {
            Consume();
            return E1;

        } else {
            ExceptionThrow(Syntax_Error, "Error parentheses is not closed ");
        }
    } 
    else {
          ExceptionThrow(Syntax_Error, " No Valid Type");
    }

}

#endif	/* PARSER_HPP */


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
#include"tables.hpp"
#include "algorithm"
#include "Declaration.hpp"
#include <unordered_map>
#define Syntax_Error 2

class Parser {
    Scope_Symbol_Table Scope_Tables;
    std::vector <Token*> Parsing_Token_Vect;
    std::unordered_map <std::string, EXPR*> Var_List;
    std::vector <Token*>::iterator Token_Itter;
  std::vector<std::string> Key_Words {"var","int","bool","true","false"};
    EXPR* Final_Expression=NULL;
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
    bool  Key_Word_Check(std::string var_name);
    EXPR *  Check_For_New_Var();
    EXPR * Check_Var(std::string);
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
        Parser() {
       
    }
        int check_Scope();
        void Parse_Line(std::vector<Token*> Lex_Tokens);
    void Parser_Print();
    int Parser_Eval(int option);

};

int Parser::check_Scope() {
    return Scope_Tables.Number_Of_Scope;
}


EXPR * Parser::Check_Var(std::string name){
    EXPR * E1;
    std::unordered_map <std::string, EXPR*> ::iterator val;
    val = Var_List.find(name);
    if (val == Var_List.end()){
        //Assert variable needs to be assigned in order to be used. 
    }
    else{
        E1=val->second;
        return E1;
    }
}

EXPR *  Parser::Check_For_New_Var() {
    EXPR* E1;
     EXPR* E2;
    std::string Var_Name;
    if (Match_Statement(Var_KW_Token)) {
        Token* Temp;
         //std::cout<<"In Var KW \n";
        Variable_Token* Var_Tok_Class;
        Consume();
        if (Match_Statement(Int_KW_Token)) {
           // std::cout<<"In Int KW \n";
            Consume();
            if (Var_Token) {
 //std::cout<<"In Var \n";
                Temp = Look_Ahead();
                Var_Tok_Class = dynamic_cast<Variable_Token*> (Temp);
                Var_Name = Var_Tok_Class->Send_Value();
Consume();
                

std::unordered_map <std::string, EXPR*> ::iterator val;
   val = Var_List.find(Var_Name);
    if (val == Var_List.end()) {
 
                if (Match_Statement(Equal_Token)) {
                    // std::cout<<"In equal \n";
                    Consume();
                    if (Match_Statement(Int_Token)) {
                 E2= Parse_Expression();
                         //std::cout<<"In Int value \n";
                        int Int_Val;
                        Integer_Token* Int_Tok;
                        Int_EXPR* Int_Exprs;
                        Temp = Look_Ahead();
                        if (E2->EXPR_type==E2->Int_Type){
                            
                        Int_Exprs = dynamic_cast< Int_EXPR*> (E2);
                        Int_Val = Int_Exprs->Value;
                      
                        Consume();
                         E1= new Var_Int_EXPR(Var_Name, Int_Val);
                         Var_List.insert({Var_Name,E1});
                         return E1;
                        //HAVE TO ADD VAR TO TABLE
                        }
                        else {
                        //Assert right side typing is wrong. 
                        }
                    }

                }
            }
   else {
        //ASSERT Cant have mutiple defintions of a variable
        }

            }


        } else if (Match_Statement(Bool_KW_Token)) {
Consume();
            if (Var_Token) {

                Temp = Look_Ahead();
                Var_Tok_Class = dynamic_cast<Variable_Token*> (Temp);
                Var_Name = Var_Tok_Class->Send_Value();
Consume();
                // Check If Var has been in scope or not.
std::unordered_map <std::string, EXPR*> ::iterator val;
   val = Var_List.find(Var_Name);
    if (val == Var_List.end()){ 
 
                if (Match_Statement(Equal_Token)) {
                    Consume();
                    if (Match_Statement(Bool_Token)) {
                        
                         E2= Parse_Expression();
                         //std::cout<<"In Bool value \n";
                        int Bool_Val;
                        
                        Bool_EXPR* Bool_Exprs;
                  
                        if (E2->EXPR_type==E2->Bool_Type){
                            
                        Bool_Exprs = dynamic_cast< Bool_EXPR*> (E2);
                        Bool_Val = Bool_Exprs->Value;
                      
                        Consume();
                         E1= new Var_Bool_EXPR(Var_Name, Bool_Val);
                         Var_List.insert({Var_Name,E1});
                         return E1;
                        //HAVE TO ADD VAR TO TABLE
                        }
                        else {
                        //Assert right side typing is wrong. 
                        }
                  
                    }

                }
            }
    else {
      //ASSERT Cant have mutiple defintions of a variable
    }

            }
        }
    }


    //return true;
    ;
}
void Parser::Parse_Line(std::vector<Token*> Lex_Tokens){
    Parsing_Token_Vect = Lex_Tokens;
        Token_Itter = Parsing_Token_Vect.begin();
has_parsed=false;
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
     if (Final_Expression==NULL){}
     else{
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
return value;}
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

bool Parser::Key_Word_Check(std::string var_name){
   return  std::find(Key_Words.begin(),Key_Words.end(),var_name) !=Key_Words.end();
}

EXPR * Parser::Parse_Expression() {
    if (Match_Statement(L_Brace_Token)) {
        Scope_Tables.Add_Count();
            Consume();
    }
    else if (Match_Statement(R_Brace_Token)) {
         Scope_Tables.Remove_Count();
            Consume();    
     }
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
           else if (Match_Statement(R_Brace_Token)){
         Scope_Tables.Remove_Count();
          Consume();
    
    }
            if (Match_Statement(L_Brace_Token)) {
        Scope_Tables.Add_Count();
            Consume();
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
    else if (Match_Statement(Var_KW_Token)){
      EXPR* Val=Check_For_New_Var();
    return Val;
    }
    else if (Match_Statement(Var_Token)){
        Variable_Token* VE1;
        Temp = Look_Ahead();
        VE1 = dynamic_cast<Variable_Token*> (Temp);
        Consume();
        EXPR* Val;
    Val=Check_Var(VE1->Send_Value());
    return Val;
    }
    else if (Match_Statement(L_Brace_Token)){
        Consume();
        return new No_Comp_EXPR();
    }

     else if (Match_Statement(R_Brace_Token)){
         Scope_Tables.Remove_Count();
          Consume();
        return new No_Comp_EXPR();
    
    }
    else {
          ExceptionThrow(Syntax_Error, " No Valid Type");
    }

}

#endif	/* PARSER_HPP */


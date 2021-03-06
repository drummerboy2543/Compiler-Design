/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Andrew
 *
 * Created on February 11, 2017, 5:40 PM
 */
#include <cstdlib>
#include <limits> 
#include <iostream>
#include <string>
#include "ast.hpp"
#include "Eval.hpp"
#include "Check.hpp"
#include "Print.hpp"
#include "Parser.hpp"
#include <fstream>
using namespace std;

/*
 *
 * This is a test with expression print
 */
void Expression_Print(std::string message, EXPR*e) {

    std::cout << message;
    Print(e);
    Check(e);
    std::cout << " == " << Eval(e) << "\n \n";
}

/*
 * This is the start of the main function.
 */
int main(int argc, char** argv) {
   /*
    int count=0;
    
     std::cout << "Welcome to Andrew Thornborough's Compiler  \n------------------------------------------- \n";		
     char Option_Input;
     int option; 
     std::cout << "Welcome to Andrew Thornborough's Lexer  \n------------------------------------------- \n";
     std::cin>>Option_Input;
     Lexer x;
     string Whole_Input="";
     string input;
     if (Option_Input=='d'){
         option=0;
     }
     else if (Option_Input=='h'){
         option=1;
     }
     else if (Option_Input=='b'){
         option=2;
     }
     while(getline(std::cin,input, '\n')){
         count=count+1;
     
         if (!input.empty()){
            if (*input.c_str()=='q'){
                break;
        }
          }
      
 Whole_Input=Whole_Input+input+"\n";
          x.Read_Line(input,option);
        
     }
     cout<<"The whole input is the following: \n \n"<<Whole_Input;
             
          cout<<"\nThe final output of this file is: \n \n";
         x.Print();
         
         std::cout<<"\n Testing Bit Expressions \n \n";
         
          EXPR* e;
          e = new Bit_Not_EXPR(new Int_EXPR(13));
         Expression_Print("Bit_Not_Expression Test(~13): e == ", e);
          e = new Bit_And_EXPR(new Int_EXPR(14),new Int_EXPR(7));
          Expression_Print("Bit_And_Expression Test(14&7): e == ", e);
          e = new Bit_Or_EXPR(new Int_EXPR(14),new Int_EXPR(7));
          Expression_Print("Bit_Or_Expression Test(14|7): e == ", e);
          e = new Xor_EXPR(new Int_EXPR(14),new Int_EXPR(7));
          Expression_Print("Bit_Xor_Expression Test with int (14^7): e == ", e);
     e = new Xor_EXPR(new Bool_EXPR(1),new Bool_EXPR(0));
          Expression_Print("Bit_Xor_Expression Test with bool (1^0): e == ", e);
           e = new Xor_EXPR(new Bool_EXPR(1),new Bool_EXPR(1));
          Expression_Print("Bit_Xor_Expression Test with bool (1^1): e == ", e);
         //This is was the implemintation to the AST I am keeping this for keeping.
    */
  /*
     * Part 3*/
     std::string Option_Inpu;
    bool Picked_Option=false;
    int option;
    int eval_Value;
    Lexer Lexer_1;
    bool finish_calc=false;
    bool first=false;
    std::ifstream file("test2.txt");
    std::string str; 
    Parser Parse_1 ;
    bool hit_q=false;

    while (std::getline(std::cin, str,'\n')&&!hit_q)
    {
        
          
        if (first==false){
            Option_Inpu=Lexer_1.Get_Option(str);
            cout<<"The Option Value is "<<Option_Inpu[0]<<"\n \n";
        if (Option_Inpu[0]=='d'){
        option=0;
        Picked_Option=true;
    }
    else if (Option_Inpu[0]=='h'){
        option=1;
        Picked_Option=true;
    }
    else if (Option_Inpu[0]=='b'){
        option=2;
        Picked_Option=true;
    }
    else {
        std::cout<<"Invalid Option \n";
    }
        first=true;
        }
        else {
            if (Option_Inpu[0]=='q'){
                      hit_q=true;}else {
       Lexer_1.Read_Line(str,option);
       bool is_white_space=Lexer_1.All_White_Space();
       if (is_white_space){
           //std::cout<<"space!! \n"; 
       }
       else{
        // cout<<"\n";
        // cout<<"The string is "<<str;
        //  cout<<"\n";
        //  cout<<"The lexed value is \n";
        // Lexer_1.Print();
        // cout<<"\n";
        // cout<<"\n";
       
             Parse_1.Parse_Line(Lexer_1.Read_Line(str,option));
                   cout<<" \nThe Statement from this line you inputed \n";
                    cout<<"\n";
                       Parse_1.Parser_Print();
                       
                       cout<<"\n";
                  eval_Value= Parse_1.Parser_Eval(option);
                 cout<<"\n";
                   Lexer_1.Clear_Vec();}
       }
    }
    }
    
    /*
    std::cout << "Welcome to Andrew Thornborough's Calculator  \n----------------------------------------------------------------------- \n";
    std::cout<<"This calculator can do the following \n";
      std::cout<<"1. One row calculations.\n2. Bitwise operators and exclusive/inclusive OR \n";
     std::cout<<"3. Output in various formats like hex and binary.\n4. Can handle comments with #\n";
     std::cout<<"\n----------------------------------------------------------------------- \n\n";
    while(Picked_Option==false){
        std::cout<<"Please insert the following command d for decimal h for hex or b for binary \n";
    std::cin>>Option_Input;

    if (Option_Input=='d'){
        option=0;
        Picked_Option=true;
    }
    else if (Option_Input=='h'){
        option=1;
        Picked_Option=true;
    }
    else if (Option_Input=='b'){
        option=2;
        Picked_Option=true;
    }
    else {
        std::cout<<"Invalid Option \n";
    }
    }
    std::cout<<"Format Selected. Press q then enter to quit. \n Enter a command: \n";
    
    while(finish_calc==false){
        getline(std::cin,input);
        
        if (!input.empty()){
            if (*input.c_str()=='q'){
                break;
        }
            cout<<"\n";
             Parser Parse_1 ( Lexer_1.Read_Line(input,option));
                   cout<<"The Value you inputed \n";
                       Parse_1.Parser_Print();
                       
                  eval_Value= Parse_1.Parser_Eval(option);
                   cout<<"\n";
                 
                   Lexer_1.Clear_Vec();
        }

    }
    */
    /* From Part 2.
    cout<<"The whole input is the following: \n \n"<<Whole_Input;
            
         cout<<"\nThe final output of this file is: \n \n";
        Lexer_1.Print();
        
        std::cout<<"\n Testing Bit Expressions \n \n";
        
         EXPR* e;
         e = new Bit_Not_EXPR(new Int_EXPR(13));
         Expression_Print("Bit_Not_Expression Test(~13): e == ", e);
         e = new Bit_And_EXPR(new Int_EXPR(14),new Int_EXPR(7));
         Expression_Print("Bit_And_Expression Test(14&7): e == ", e);
         e = new Bit_Or_EXPR(new Int_EXPR(14),new Int_EXPR(7));
         Expression_Print("Bit_Or_Expression Test(14|7): e == ", e);
         e = new Xor_EXPR(new Int_EXPR(14),new Int_EXPR(7));
         Expression_Print("Bit_Xor_Expression Test with int (14^7): e == ", e);
    e = new Xor_EXPR(new Bool_EXPR(1),new Bool_EXPR(0));
         Expression_Print("Bit_Xor_Expression Test with bool (1^0): e == ", e);
          e = new Xor_EXPR(new Bool_EXPR(1),new Bool_EXPR(1));
         Expression_Print("Bit_Xor_Expression Test with bool (1^1): e == ", e);
         //This is was the implemintation to the AST I am keeping this for keeping.
     * */
  /*
 std::cout << "Welcome to Andrew Thornborough's Compiler  \n------------------------------------------- \n";
    int count = 0;
    int max_num = 8;
    EXPR* e;

    e = new Bool_EXPR(true);
    Expression_Print("Bool Val Test(T): e == ", e);

    e = new Bool_EXPR(false);
    Expression_Print("Bool Val Test(F): e == ", e);

    e = new Not_EXPR(new Bool_EXPR(true));
    Expression_Print("Simple Not Test: e == ", e);

    e = new And_EXPR(new Bool_EXPR(true), new Bool_EXPR(true));
    Expression_Print("Simple And Test: e == ", e);

    e = new Or_EXPR(new Bool_EXPR(true), new Bool_EXPR(false));
    Expression_Print("Simple Or Test: e == ", e);

    e = new Xor_EXPR(new Bool_EXPR(true), new Bool_EXPR(true));
    Expression_Print("Simple Xor Test: e == ", e);

    e = new Int_EXPR(5);
    Expression_Print("Positive Int Test: e == ", e);

    e = new Int_EXPR(-5);
    Expression_Print("Negative Int Test: e == ", e);

    e = new Eq_EXPR(new Int_EXPR(7), new Int_EXPR(13));
    Expression_Print("Equality Test: e == ", e);

    e = new Neq_EXPR(new Int_EXPR(7), new Int_EXPR(13));
    Expression_Print("Non Equality Test: e == ", e);

    e = new Gt_EXPR(new Int_EXPR(32), new Int_EXPR(31));
    Expression_Print("Greater than Test: e == ", e);

    e = new Lt_EXPR(new Int_EXPR(32), new Int_EXPR(31));
    Expression_Print("Less than Test: e == ", e);

    e = new Gteq_EXPR(new Int_EXPR(16), new Int_EXPR(15));
    Expression_Print("Greater than Test 1: e == ", e);

    e = new Gteq_EXPR(new Int_EXPR(15), new Int_EXPR(15));
    Expression_Print("Greater than Test 2: e == ", e);

    e = new Lteq_EXPR(new Int_EXPR(14), new Int_EXPR(15));
    Expression_Print("Less than or equal to Test 1: e == ", e);

    e = new Lteq_EXPR(new Int_EXPR(15), new Int_EXPR(15));
    Expression_Print("Less than or equal to Test 2: e == ", e);

    e = new Add_EXPR(new Int_EXPR(15), new Int_EXPR(5));
    Expression_Print("Simple Add Test 1: e == ", e);

    e = new Add_EXPR(new Int_EXPR(-15), new Int_EXPR(-5));
    Expression_Print("Simple Add Test 2: e == ", e);

    e = new Minus_EXPR(new Int_EXPR(15), new Int_EXPR(5));
    Expression_Print("Simple Subtract Test 1: e == ", e);

    e = new Minus_EXPR(new Int_EXPR(15), new Int_EXPR(-5));
    Expression_Print("Simple Subtract Test 2: e == ", e);


    e = new Mul_EXPR(new Int_EXPR(15), new Int_EXPR(5));
    Expression_Print("Simple Multiply Test 1: e == ", e);

    e = new Mul_EXPR(new Int_EXPR(15), new Int_EXPR(-5));
    Expression_Print("Simple Multiply Test 2: e == ", e);


    e = new Div_EXPR(new Int_EXPR(15), new Int_EXPR(5));
    Expression_Print("Simple Divide Test 1: e == ", e);

    e = new Div_EXPR(new Int_EXPR(15), new Int_EXPR(-5));
    Expression_Print("Simple Divide Test 2: e == ", e);

    e = new Mod_EXPR(new Int_EXPR(15), new Int_EXPR(4));
    Expression_Print("Simple Modulus Test 1: e == ", e);

    e = new Mod_EXPR(new Int_EXPR(15), new Int_EXPR(-4));
    Expression_Print("Simple Modulus Test 2: e == ", e);

    e = new Negation_EXPR(new Int_EXPR(15));
    Expression_Print("Simple Negation Test:(value=15) e == ", e);

    e = new Cond_EXPR(new Bool_EXPR(true), new Int_EXPR(14), new Int_EXPR(21));
    Expression_Print("Simple If then Test: e == ", e);

    e = new AndThen_EXPR(new Bool_EXPR(true), new Bool_EXPR(true));
    Expression_Print("Simple And Then Test: e == ", e);

    e = new OrElse_EXPR(new Bool_EXPR(true), new Bool_EXPR(true));
    Expression_Print("Simple Or Else Test: e == ", e);

    e = new Xor_EXPR(new Neq_EXPR(new Mod_EXPR(new Mul_EXPR(new Int_EXPR(7), new Int_EXPR(5)), new Int_EXPR(3)), new Int_EXPR(3.8)), new Bool_EXPR(false));
    Expression_Print("Complex Logic Example: e == ", e);

    int y;
    std::string options [max_num] = {"Bool operator Type Error", "Int operator Type error", "Addition Overflow", "Subtraction Underflow", "Multiplication Overflow", "Divide by 0 ", "Modulate by 0", "if condition not same type"};

    std::cout << "Menu to trigger error: \n";
    for (int x = 0; x < max_num; x++) {
        std::cout << x << ": " << options[x] << " \n";
    }

    std::cout << "Please select a input between the numbers from 0 to 7  \n";
    std::cin>>y;
    switch (y) {
        case 0: std::cout << "Selecting Bool operator Type Error \n";
            e = new And_EXPR(new Int_EXPR(5), new Bool_EXPR(true));
            Expression_Print("e == ", e);
            break;

        case 1: std::cout << "Selecting Int operator Type error \n";
            e = new Add_EXPR(new Bool_EXPR(true), new Int_EXPR(31));
            Expression_Print("e == ", e);
            break;

        case 2: std::cout << "Selecting Addition Overflow \n";
            e = new Add_EXPR(new Int_EXPR(2147483646), new Int_EXPR(1));
            Expression_Print("e == ", e);
            e = new Add_EXPR(new Int_EXPR(2147483646), new Int_EXPR(3));
            Expression_Print("e == ", e);
            break;

        case 3: std::cout << "Selecting Subtraction Underflow \n";
            e = new Minus_EXPR(new Int_EXPR(-2147483647), new Int_EXPR(1));
            Expression_Print("e == ", e);
            e = new Minus_EXPR(new Int_EXPR(-2147483647), new Int_EXPR(3));
            Expression_Print("e == ", e);
            break;
        case 4: std::cout << "Selecting Multiplication Overflow \n";
            e = new Mul_EXPR(new Int_EXPR(2147483646), new Int_EXPR(3));
            Expression_Print("e == ", e);
            break;

        case 5: std::cout << "Selecting Divide by 0 \n";
            e = new Div_EXPR(new Int_EXPR(646), new Int_EXPR(0));
            Expression_Print("e == ", e);
            break;

        case 6: std::cout << "Selecting Modulate by 0 \n";
            e = new Mod_EXPR(new Int_EXPR(64), new Int_EXPR(0));
            Expression_Print("e == ", e);
            break;

        case 7: std::cout << "Selecting if condition not same type \n";
            e = new Cond_EXPR(new Bool_EXPR(true), new Bool_EXPR(14), new Int_EXPR(21));
            Expression_Print("e == ", e);
            break;

    }
   * */ 
     std::cout<<" \n \nCompiler Exiting have a great day!";
//    return eval_Value;
     return 0;
}


/* 
 * File:   tables.hpp
 * Author: student16
 *
 * Created on April 9, 2017, 5:50 PM
 */
#include <string>
#ifndef TABLES_HPP
#define	TABLES_HPP
#include "Declaration.hpp"
#include <unordered_map> 
#include <iostream>


class Scope_Symbol_Table {
   // int Number_Of_Scope=0;
    struct Stack {
     struct Stack_Node{
   
     std::unordered_map <std::string,Declaration*> Symbol_Table;
     Stack_Node* prev;
     Stack_Node(){};
   
     };
    Stack_Node* top=NULL;
    Stack_Node* Tranverse=NULL;
     Stack();
   void Push();
   std::unordered_map <std::string,Declaration*>  Peek();
   void Pop();
    bool If_Empty();
    void Print_Stack();
    };
     
    Stack* Symbol_Table_Stack;
public:
     int Number_Of_Scope=0;
  Scope_Symbol_Table();
 void Insert_in_Scope();   
 void Add_Scope();
 void Remove_Scope();
 void Edit_Variable();
 Declaration* Check_Variable(std::string var_name);
void Add_Count();
void Remove_Count();
int Is_Scope_Balanced();
};

#endif	/* TABLES_HPP */

void Scope_Symbol_Table::Add_Count(){
Number_Of_Scope=Number_Of_Scope+1;
}
void Scope_Symbol_Table::Remove_Count(){
    Number_Of_Scope=Number_Of_Scope-1;
}
int Scope_Symbol_Table::Is_Scope_Balanced(){
    return Number_Of_Scope;
}

Scope_Symbol_Table::Scope_Symbol_Table(){};
void Scope_Symbol_Table::Add_Scope(){
Symbol_Table_Stack->Push();
}

void Scope_Symbol_Table::Remove_Scope(){
    if (Symbol_Table_Stack->If_Empty()){
        std::cout<<"Error no scope";
    }
    else {
Symbol_Table_Stack->Pop();}
}


Declaration* Scope_Symbol_Table::Check_Variable(std::string var_name){
Symbol_Table_Stack->Tranverse=Symbol_Table_Stack->top;

while(Symbol_Table_Stack->Tranverse!=NULL){
    std::unordered_map <std::string,Declaration*>::iterator val;

    val = Symbol_Table_Stack->Tranverse->Symbol_Table.find(var_name);
    if (val != Symbol_Table_Stack->Tranverse->Symbol_Table.end()) {
      return val->second;  
    }
 
Symbol_Table_Stack->Tranverse=Symbol_Table_Stack->top->prev;

}
if (Symbol_Table_Stack->Tranverse==NULL){

std::cout<< "Error no table checked";}
return NULL;
}




//
   void Scope_Symbol_Table::Stack::Push(){
       if (If_Empty()){
         Stack_Node* temp= new Stack_Node();
        temp->prev=NULL;
        top=temp;
       }
       else{
          Stack_Node* temp= new Stack_Node();
       temp->prev=top;
       top=temp;
       }
       
   };
   
   std::unordered_map <std::string,Declaration*>  Scope_Symbol_Table::Stack::Peek(){
       return top->Symbol_Table;
   };
  void Scope_Symbol_Table::Stack::Pop(){
         Stack_Node* temp;
        temp=top;
        top=top->prev;
        delete temp;      
    };
    
    bool Scope_Symbol_Table::Stack::If_Empty(){
        if (top==NULL){return true;}
      else{return false;}
    };
    

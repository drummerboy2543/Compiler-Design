
/* 
 * File:   Check.hpp
 * Author: Andrew
 *
 * Created on February 10, 2017, 4:58 PM
 */

#ifndef CHECK_HPP
#define CHECK_HPP
#define ERROR -1
#include "ExceptionHandle.h"
#define Type_Error 0
#define Arithmetic_Error 1
/*
 This Function Checks the typing of each node. Using the Visitor Pattern
 *  This is to make sure the sub-expressions are well typed for the given expression they are in.
 *  The main 2 types are Boolean and Integer. 
 *  If there is a typing error a function called ExceptionThrow is called which is from ExceptionHandle.h
 *  This function  displays a given string that was a input to the function and calls assert to stop the program due to the error.
 */
int Check(EXPR* e) {

    struct V : EXPR::Visitor {
        bool Outcome;
     //Basic Type checking should never see a error.
        void visit(Bool_EXPR* e) {
            if (e->EXPR_type == e->Bool_Type) {
                Outcome = e->Bool_Type;
            } else {
                ExceptionThrow(Type_Error, "Bool is reported as a INT");
                Outcome = ERROR;
            }
        }

        void visit(Int_EXPR* e) {
            if (e->EXPR_type == e->Int_Type) {
                Outcome = e->Int_Type;
            } else {
                ExceptionThrow(Type_Error, "Int is reported as a Bool");
                Outcome = ERROR;
            }
        }
        
   //These checks requires a Boolean Expression to be well typed.
        void visit(Not_EXPR* e) {
            if (Check(e->e1) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "Not Error:Expression is not a Bool");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }
        
           void visit(Bit_Not_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Bit Not Error:Expression is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }
        
        
       //These boolean operator expressions require two boolean sub expressions 
        void visit(Or_EXPR* e) {
            if (Check(e->e1) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "Or Error:Expression 1 is not a Bool");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "Or Error:Expression 2 is not a Bool");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }

         void visit(Bit_Or_EXPR* e) {

            if (Check(e->e1) != Check(e->e2)) {
                ExceptionThrow(Type_Error, "Bit Or Error:Expression are not the same type.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }

        }
        
        
        void visit(And_EXPR* e) {

            if (Check(e->e1) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "And Error:Expression 1 is not a Bool");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "And Error:Expression 2 is not a Bool");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }
        
             void visit(Bit_And_EXPR* e) {

            if (Check(e->e1) != Check(e->e2)) {
                ExceptionThrow(Type_Error, "Bit And Error:Expression are not the same type.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }

        }
        

        
        void visit(Xor_EXPR* e) {
            
               if (Check(e->e1) != Check(e->e2)) {
                ExceptionThrow(Type_Error, "Xor Error:Expression are not the same type.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }
        
     //This if statement requires a if of boolean sub expression and then 2 condtions that are the same type.
        void visit(Cond_EXPR* e) {

            if (Check(e->e1) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "If Cond Error:Expression 1 is not a Bool");
                Outcome = ERROR;
            } else if (Check(e->e2) != Check(e->e3)) {
                ExceptionThrow(Type_Error, "if Cond Error:IF and else Implementation is the same type.");
                Outcome = ERROR;
            } else {
                Outcome = e->e2->EXPR_type;
            }
        }
        
//These specific if statements expressions require two boolean sub expressions 
        void visit(AndThen_EXPR* e) {

            if (Check(e->e1) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "And Then Cond Error:Expression 1 is not a Bool");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "And Then Cond Error:Expression 2 is not a Bool.");
                Outcome = ERROR;
            } else {
                Outcome = e->e2->EXPR_type;
            }
        }

        void visit(OrElse_EXPR* e) {

            if (Check(e->e1) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "Or Else Cond Error:Expression 1 is not a Bool");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Bool_Type) {
                ExceptionThrow(Type_Error, "Or Else Cond Error:Expression 2 is not a Bool.");
                Outcome = ERROR;
            } else {
                Outcome = e->e2->EXPR_type;
            }
        }
        
//The following equality operator expressions require two  sub expressions of the same type. 
        void visit(Eq_EXPR* e) {

            if (Check(e->e1) != Check(e->e2)) {
                ExceptionThrow(Type_Error, "Eq Error:Expression are not the same type.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }

        }

        void visit(Neq_EXPR* e) {

            if (Check(e->e1) != Check(e->e2)) {
                ExceptionThrow(Type_Error, "Neq Error:Expression are not the same type.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }

        }
        
   //These inequality operator expressions require two Integer sub expressions 
        void visit(Gt_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Greater Than Error:Expression 1 is not a Int.");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Greater Than Error:Expression 2 is not a Int.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }

        void visit(Lt_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Less Than Error:Expression 1 is not a Int.");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Less Than Error:Expression 2 is not a Int.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }

        void visit(Gteq_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Greater Than Equal To Error:Expression 1 is not a Int.");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Greater Than Equal To Error:Expression 2 is not a Int.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }

        void visit(Lteq_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Less Than Equal To Error:Expression 1 is not a Int.");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Less Than Equal To Error:Expression 2 is not a Int.");
                Outcome = ERROR;
            } else {
                Outcome = e->Bool_Type;
            }
        }
        
//These Arithmitic operator expressions require two Integer sub expressions 
        void visit(Add_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Add Error:Expression 1 is not a Int");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Add Error:Expression 2 is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Int_Type;
            }
        }

        void visit(Minus_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Minus Error:Expression 1 is not a Int");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Minus Error:Expression 2 is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Int_Type;
            }
        }

        void visit(Mul_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Multiply Error:Expression 1 is not a Int");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Multiply Error:Expression 2 is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Int_Type;
            }
        }

        void visit(Div_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Divide Error:Expression 1 is not a Int");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Divide Error:Expression 2 is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Int_Type;
            }
        }

        void visit(Mod_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Modulus Error:Expression 1 is not a Int");
                Outcome = ERROR;
            } else if (Check(e->e2) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Modulus Error:Expression 2 is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Int_Type;
            }
        }

        void visit(Negation_EXPR* e) {
            if (Check(e->e1) != e->Int_Type) {
                ExceptionThrow(Type_Error, "Negation Error:Expression is not a Int");
                Outcome = ERROR;
            } else {
                Outcome = e->Int_Type;
            }
        }
    };
    V vis;
    e->accept(vis);
    return vis.Outcome;
}


#endif /* CHECK_HPP */


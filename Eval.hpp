/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Eval.hpp
 * Author: Andrew
 *
 * Created on February 11, 2017, 8:08 PM
 */

#ifndef EVAL_HPP
#define EVAL_HPP
#include "Check.hpp"
#include <limits> 
#include <cmath> 
#include "ExceptionHandle.h"
#define Type_Error 0
#define Arithmetic_Error 1


/*
 This Function Evaluates the typing of each node. Using the Visitor Pattern
 *  Before the Evaluation it checks if the typing in the expression is still sound as a double check.
 *  Depending on the operation it is evaluating it will check if there is any arithmetic errors before evaluating (for example divide by 0).
 * If these checks do not have errors it will then evaluate the expression based on the expression type.
 */
int Eval(EXPR* e) {

    struct Visiting : EXPR::Visitor {
        int Outcome;
        
        
      // The following functions simply Returns values
        void visit(Bool_EXPR* e) {
           // std::cout<<"Eval Bool \n";
            Outcome = e->Value;
        }

        void visit(Int_EXPR* e) {
             // std::cout<<"Eval Int \n";
            Outcome = e->Value;
        }

        
        // The following functions returns the boolean logic result based on the expression inputs.
        void visit(Not_EXPR* e) {
            assert(Check(e->e1) == e->Bool_Type);
            Outcome = (!(Eval(e->e1)));
        }
    void visit(Bit_Not_EXPR* e) {
            assert(Check(e->e1) == e->Int_Type);
            Outcome = (~(Eval(e->e1)));
        }
        
        void visit(Or_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Bool_Type);
            Outcome = (Eval(e->e1) ? true : Eval(e->e2));
        }
        void visit(Bit_Or_EXPR* e) {
            assert((Check(e->e1) == Check(e->e2)));
            Outcome = ((Eval(e->e1)) | (Eval(e->e2)));
        }
        void visit(And_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Bool_Type);
            Outcome = (Eval(e->e1) ? Eval(e->e2) : false);
        }

        void visit(Bit_And_EXPR* e) {
            assert((Check(e->e1) == Check(e->e2)));
            Outcome = ((Eval(e->e1)) & (Eval(e->e2)));
        }
        void visit(Xor_EXPR* e) {
             assert((Check(e->e1) == Check(e->e2)));
            Outcome = ((Eval(e->e1))^(Eval(e->e2)));
        }
        
        
   //The following functions returns a boolean logic result based on the expression inputs.
        void visit(Eq_EXPR* e) {
            assert((Check(e->e1) == Check(e->e2)));
            Outcome = ((Eval(e->e1)) == (Eval(e->e2)));
        }

        void visit(Neq_EXPR* e) {
            assert((Check(e->e1) == Check(e->e2)));
            Outcome = ((Eval(e->e1)) != (Eval(e->e2)));
        }
        
        
// The following functions returns a boolean logic result based on the expression inputs.
        void visit(Gt_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            Outcome = ((Eval(e->e1))>(Eval(e->e2)));
        }

        void visit(Lt_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            Outcome = ((Eval(e->e1))<(Eval(e->e2)));
        }

        void visit(Gteq_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            Outcome = ((Eval(e->e1)) >= (Eval(e->e2)));
        }

        void visit(Lteq_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            Outcome = ((Eval(e->e1)) <= (Eval(e->e2)));
        }
        
        
   //The following functions returns a result based on the boolen result of expression 1.
        void visit(Cond_EXPR* e) {
            assert(Check(e->e1) == e->Bool_Type);
            assert(Check(e->e2) == Check(e->e3));
            Outcome = (Eval(e->e1) ? Eval(e->e2) : Eval(e->e3));
        }

        void visit(AndThen_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Bool_Type);
            Outcome = (Eval(e->e1) ? Eval(e->e2) : false);
        }

        void visit(OrElse_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Bool_Type);
            Outcome = (Eval(e->e1) ? true : Eval(e->e2));
        }
        
        
        // The following functions checks arithmetic errors and overflow 
        // then returns a integer  based on the expression inputs.
        void visit(Add_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);

            if ((Eval(e->e1) > 0 && Eval(e->e2) > 0) && std::numeric_limits<int>::max() - Eval(e->e1) < Eval(e->e2)) {
                ExceptionThrow(Arithmetic_Error, "The two integers that are being added will be greater then the biggest integer.");
            } else if ((Eval(e->e1) < 0 && Eval(e->e2) < 0) && std::numeric_limits<int>::min() - Eval(e->e1) > Eval(e->e2)) {
                ExceptionThrow(Arithmetic_Error, "The two integers that are being added will be smaller then the smallest integer.");
            }
            Outcome = ((Eval(e->e1))+(Eval(e->e2)));
        }

        void visit(Minus_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            if (((Eval(e->e1) > 0)&& (Eval(e->e2) < 0)) &&(std::numeric_limits<int>::max() - Eval(e->e1) < -Eval(e->e2))) {
                ExceptionThrow(Arithmetic_Error, "The two integers that are being subtracted will be greater then the biggest integer.");
            } else if (((Eval(e->e1) < 0)&& (Eval(e->e2) > 0)) && std::numeric_limits<int>::min() - Eval(e->e1) >-Eval(e->e2)) {
                ExceptionThrow(Arithmetic_Error, "The two integers that are being subtracted will be smaller then the smallest integer.");
            }

            Outcome = ((Eval(e->e1))-(Eval(e->e2)));
        }

        void visit(Mul_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);

            if ((((Eval(e->e1) > 0 && (Eval(e->e2) > 0)))) || ((Eval(e->e1) < 0) && (Eval(e->e2)) < 0)) {
                if (std::numeric_limits<int>::max() / std::abs(Eval(e->e1)) < std::abs(Eval(e->e2))) {
                    ExceptionThrow(Arithmetic_Error, "The two integers that are being multiplied will be greater then the biggest integer.");
                }
            } else if ((Eval(e->e1) > 0 && Eval(e->e2) < 0) && std::numeric_limits<int>::min() / Eval(e->e1) > Eval(e->e2)) {
                ExceptionThrow(Arithmetic_Error, "The two integers that are being multiplied will be smaller then the smallest integer. 1");
            } else if ((Eval(e->e1) < 0 && Eval(e->e2) > 0) && std::numeric_limits<int>::min() / Eval(e->e2) > Eval(e->e1)) {
                ExceptionThrow(Arithmetic_Error, "The two integers that are being multiplied will be smaller then the smallest integer. 2");
            }


            Outcome = ((Eval(e->e1))*(Eval(e->e2)));
        }

        void visit(Div_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            if (Eval(e->e2) == 0) {
                ExceptionThrow(Arithmetic_Error, "Can't Divide by 0");
            }
            else if (Eval(e->e1) == std::numeric_limits<int>::min() && Eval(e->e2) == -1) {
                ExceptionThrow(Arithmetic_Error, "Max negative will result to overflow in positive.");
            }
            Outcome = ((Eval(e->e1)) / (Eval(e->e2)));
        }

        void visit(Mod_EXPR* e) {
            assert((Check(e->e1) && Check(e->e2)) == e->Int_Type);
            if (Eval(e->e2) == 0) {
                ExceptionThrow(Arithmetic_Error, "Can't Modulate by 0");
            }
            Outcome = ((Eval(e->e1)) % (Eval(e->e2)));
        }

        void visit(Negation_EXPR* e) {
            assert(Check(e->e1) == e->Int_Type);
            Outcome = (0 - (Eval(e->e1)));
        }
    };
    Visiting V;
    e->accept(V);
    return V.Outcome;

};


#endif /* EVAL_HPP */


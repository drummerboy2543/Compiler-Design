/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Print.hpp
 * Author: Andrew
 *
 * Created on February 11, 2017, 4:22 PM
 */
#//#include "EXPR_Bool.hpp"
#ifndef PRINT_HPP
#define PRINT_HPP

/*
 This Function checks if a expression needs parentheses.  
 The function returns true or false depending on the input of the expression. This helps for readability.
 */
bool Parenth_Cond(EXPR* e) {

    struct Parenth_database : EXPR::Visitor {
        bool value;

        void visit(Bool_EXPR* e) {
            value = false;
        }

        void visit(Int_EXPR* e) {
            value = false;
        }

        void visit(Not_EXPR* e) {
            value = true;
        }

        void visit(Or_EXPR* e) {
            value = true;
        }

        void visit(And_EXPR* e) {
            value = true;
        }

        void visit(Xor_EXPR* e) {
            value = true;
        }

        void visit(Eq_EXPR* e) {
            value = true;
        }

        void visit(Neq_EXPR* e) {
            value = true;
        }

        void visit(Gt_EXPR* e) {
            value = true;
        }

        void visit(Lt_EXPR* e) {
            value = true;
        }

        void visit(Gteq_EXPR* e) {
            value = true;
        }

        void visit(Lteq_EXPR* e) {
            value = true;
        }

        void visit(Cond_EXPR* e) {
            value = true;
        }

        void visit(AndThen_EXPR* e) {
            value = true;
        }

        void visit(OrElse_EXPR* e) {
            value = true;
        }

        void visit(Add_EXPR* e) {
            value = true;
        }

        void visit(Minus_EXPR* e) {
            value = true;
        }

        void visit(Mul_EXPR* e) {
            value = true;
        }

        void visit(Div_EXPR* e) {
            value = true;
        }

        void visit(Mod_EXPR* e) {
            value = true;
        }

        void visit(Negation_EXPR* e) {
            value = true;
        }
    };
    Parenth_database V;
    e->accept(V);
    // std::cout<<" The Value is "<<V.value;
    return V.value;

    ;
}

/*
 This Function Prints out the expression of each node. Using the Visitor Pattern
 There is two functions one to implement parentheses and one to print the expression itself.
 The visit function that prints the main expression will check if each sub expression need parentheses and then print its expression. 
 The Parenth_Check function is use to print parentheses if necessary and then print the subexpression.
 */
void Print(EXPR* e) {

    struct Visiting : EXPR::Visitor {

        void Parenth_Check(EXPR*e) {
            bool result = Parenth_Cond(e);
            if (result == true) {
                std::cout << "(";
                Print(e);
                std::cout << ")";

            } else {
                //std::cout<<"hi";
                Print(e);
            }

        }

        void visit(Bool_EXPR* e) {
            if (e->Value == true) {
                std::cout << "true";
            } else {
                std::cout << "false";
            }
        }

        void visit(Int_EXPR* e) {
            std::cout << e->Value;
        }

        void visit(Not_EXPR* e) {
            std::cout << "!";
            Parenth_Check(e->e1);
        }

        void visit(Or_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "|";
            Parenth_Check(e->e2);
        }

        void visit(And_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "&";
            Parenth_Check(e->e2);
        }

        void visit(Xor_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "^";
            Parenth_Check(e->e2);
        }

        void visit(Eq_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "=";
            Parenth_Check(e->e2);
        }

        void visit(Neq_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "!=";
            Parenth_Check(e->e2);
        }

        void visit(Gt_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << ">";
            Parenth_Check(e->e2);
        }

        void visit(Lt_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "<";
            Parenth_Check(e->e2);
        }

        void visit(Gteq_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << ">=";
            Parenth_Check(e->e2);
        }

        void visit(Lteq_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "<=";
            Parenth_Check(e->e2);
        }

        void visit(Cond_EXPR* e) {
            std::cout << "if(";
            Parenth_Check(e->e1);
            std::cout << ") then{";
            Parenth_Check(e->e2);
            std::cout << "} else{";
            Parenth_Check(e->e3);
            std::cout << "} ";
        }

        void visit(AndThen_EXPR* e) {
            std::cout << "if(";
            Parenth_Check(e->e1);
            std::cout << ")And then{";
            Parenth_Check(e->e2);
            std::cout << "} else{false}";
        }

        void visit(OrElse_EXPR* e) {
            std::cout << "if(";
            Parenth_Check(e->e1);
            std::cout << ") then{true}";
            std::cout << " or else{";
            Parenth_Check(e->e2);
            std::cout << "} ";
        }

        void visit(Add_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "+";
            Parenth_Check(e->e2);
        }

        void visit(Minus_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "-";
            Parenth_Check(e->e2);
        }

        void visit(Mul_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "*";
            Parenth_Check(e->e2);
        }

        void visit(Div_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "/";
            Parenth_Check(e->e2);
        }

        void visit(Mod_EXPR* e) {
            Parenth_Check(e->e1);
            std::cout << "%";
            Parenth_Check(e->e2);
        }

        void visit(Negation_EXPR* e) {
            std::cout << "-";
            Parenth_Check(e->e1);
        }

    };
    Visiting V;
    e->accept(V);
};


#endif /* PRINT_HPP */


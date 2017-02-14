/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ast.hpp
 * Author: Andrew
 *
 * Created on February 9, 2017, 6:34 PM
 */

#ifndef AST_HPP
#define AST_HPP
#include <cassert>
#include "ExceptionHandle.h"
#define Type_Error 0
#define Arithmetic_Error 1

/*
 This File  Creates the Abstract Syntax Tree for Integers and Boolean values. 
 * The AST uses the visitor pattern to expand functionality of each expression class
 *  The base class is a the EXPR class this class holds the implementation of visitor pattern and a destructor. 
 *  It also holds a variable that determines typing which is assigned based on what derived expression it is.
 *  The Derived class holds the value and creates expressions to hold more expressions.
 * Finally There is a function called check which checks the typing for each Subexpression .
 * This is to make sure they are well type in a expression .
 */
//Initialize Classes
class Bool_EXPR;
class Not_EXPR;
class Bool_Binary_EXPR;
class Or_EXPR;
class Xor_EXPR;
class And_EXPR;
class Int_EXPR;
class Eq_EXPR;
class Cond_EXPR;
class Neq_EXPR;
class Gt_EXPR;
class Lt_EXPR;
class Gteq_EXPR;
class Lteq_EXPR;
class AndThen_EXPR;
class OrElse_EXPR;
class Add_EXPR;
class Minus_EXPR;
class Mul_EXPR;
class Div_EXPR;
class Mod_EXPR;
class Negation_EXPR;
//Function to check typing before implementation. 
bool Check(int input, int EXPR);
//Base Class
//The typing is based on a Enum where Bool_Type=0 and Int_Type=1.
//The EXPR_type is a variable of the Enum which will hold the Enum value to compare in check functions.
class EXPR {
public:
    enum Types {
        Bool_Type, Int_Type
    };
    Types EXPR_type;
    struct Visitor;
    virtual ~EXPR() = default;
    virtual void accept(Visitor &v) = 0;
};
//Visitor to implement the visiting pattern
struct EXPR::Visitor {
    virtual void visit(Bool_EXPR*) = 0;
    virtual void visit(Int_EXPR*) = 0;
    virtual void visit(Not_EXPR*) = 0;
    virtual void visit(Or_EXPR*) = 0;
    virtual void visit(And_EXPR*) = 0;
    virtual void visit(Xor_EXPR*) = 0;
    virtual void visit(Eq_EXPR*) = 0;
    virtual void visit(Neq_EXPR*) = 0;
    virtual void visit(Cond_EXPR*) = 0;
    virtual void visit(Gt_EXPR*) = 0;
    virtual void visit(Lt_EXPR*) = 0;
    virtual void visit(Gteq_EXPR*) = 0;
    virtual void visit(Lteq_EXPR*) = 0;
    virtual void visit(AndThen_EXPR*) = 0;
    virtual void visit(OrElse_EXPR*) = 0;
    virtual void visit(Add_EXPR*) = 0;
    virtual void visit(Minus_EXPR*) = 0;
    virtual void visit(Mul_EXPR*) = 0;
    virtual void visit(Div_EXPR*) = 0;
    virtual void visit(Mod_EXPR*) = 0;
    virtual void visit(Negation_EXPR*) = 0;
};
//Bool Expression
//Derived class to hold boolean values and declare the type to bool.
class Bool_EXPR : public EXPR {
public:
    bool Value;

    Bool_EXPR(bool v1) : Value(v1) {
        EXPR_type = Bool_Type;
    };

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Int Expression
//Derived class to hold Integer values and declare the type to Int.
class Int_EXPR : public EXPR {
public:
    int Value;

    Int_EXPR(int v1) : Value(v1) {
        EXPR_type = Int_Type;
    };

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Not Expression
//The following derived classes boolean expressions values and changes the output in the Eval Function.
class Not_EXPR : public EXPR {
public:
    EXPR* e1;

    Not_EXPR(EXPR* a) : e1(a) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Not Error:Expression is not a Bool");
        }
        EXPR_type = Bool_Type;
    };

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Intermediate Class to deal modularize code for boolean operators holds both boolean expressions.
class Bool_Binary_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Bool_Binary_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        EXPR_type = Bool_Type;
    };
};
//And Expression
 // The following expressions are boolean operators and check if both expressions are type bool
class And_EXPR : public Bool_Binary_EXPR {
public:

    And_EXPR(EXPR* a, EXPR* b) : Bool_Binary_EXPR(a, b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST And Error:Expression 1 is not a Bool");
        }
        Type_Defined = Check(b->EXPR_type, b->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST And Error:Expression 2 is not a Bool");
        }

    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Or Expression
 // The following expressions are boolean operators and check if both expressions are type bool
class Or_EXPR : public Bool_Binary_EXPR {
public:

    Or_EXPR(EXPR* a, EXPR* b) : Bool_Binary_EXPR(a, b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Or Error:Expression 1 is not a Bool");
        }
        Type_Defined = Check(b->EXPR_type, b->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Or Error:Expression 2 is not a Bool");
        }
    };

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Xor Expression
 // The following expressions are boolean operators and check if both expressions are type bool
class Xor_EXPR : public Bool_Binary_EXPR {
public:

    Xor_EXPR(EXPR* a, EXPR* b) : Bool_Binary_EXPR(a, b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Xor Error:Expression 1 is not a Bool");
        }
        Type_Defined = Check(b->EXPR_type, b->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Xor Error:Expression 2 is not a Bool");
        }
    };

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Equal Expression
 // The following expressions are boolean operators and check if both expressions are the same type
class Eq_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Eq_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, b->EXPR_type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST EQ Error:Expression are not the same type.");
        }
        EXPR_type = Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Not Equal Expression
 // The following expressions are boolean operators and check if both expressions are the same type
class Neq_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Neq_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, b->EXPR_type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST NeQ Error:Expression are not the same type.");
        }
        EXPR_type = Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//If then Expression
 // The following expressions is a boolean operator and checks if the expressions are well typed.
class Cond_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;
    EXPR* e3;

    Cond_EXPR(EXPR* a, EXPR* b, EXPR* c) : e1(a), e2(b), e3(c) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST if Cond Error:If condition does not result into a bool");
        }
        Type_Defined = Check(b->EXPR_type, c->EXPR_type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST if Cond Error:IF and else Implementation is not the same type.");
        }
        EXPR_type = b->EXPR_type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};



//Greater Than Expression
// The following expressions are boolean operators and check if both expressions are type Int.
class Gt_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Gt_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Greater Than Error:Expression 1 is not a Int.");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Greater Than Error:Expression 2 is not a Int.");
        }
        EXPR_type = Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Less Than Expression
// The following expressions are boolean operators and check if both expressions are type Int.
class Lt_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Lt_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Less Than Error:Expression 1 is not a Int.");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Less Than Error:Expression 2 is not a Int.");
        }
        EXPR_type = Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Greater Than Equal To Expression
// The following expressions are boolean operators and check if both expressions are type Int.
class Gteq_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Gteq_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Greater Than or Equal To Error:Expression 1 is not a Int.");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Greater Than or Equal To Error:Expression 2 is not a Int.");
        }
        EXPR_type = Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};


//Less Than Equal To Expression
// The following expressions are boolean operators and check if both expressions are type Int.
class Lteq_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Lteq_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Less Than or Equal To :Expression 1 is not a Int.");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Less Than or Equal To Error:Expression 2 is not a Int.");
        }
        EXPR_type = Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//And Then Expression
// The following expressions is a boolean operator and checks if the expressions are well typed.
class AndThen_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    AndThen_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST And Then Cond Error: If condition does not result into a bool");
        }
        Type_Defined = Check(b->EXPR_type, b->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST And Then Cond Error: Expression 2 is not type bool");
        }
        EXPR_type = b->Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Or Else Expression
// The following expressions is a boolean operator and checks if the expressions are well typed.
class OrElse_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    OrElse_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Or Else Cond Error: If condition does not result into a bool");
        }
        Type_Defined = Check(b->EXPR_type, b->Bool_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, " in AST Or Else Cond Error: Expression 2 is not type bool");
        }
        EXPR_type = b->Bool_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Addition Expression
// The following expression is a Integer operator and check if both expressions are type Int.
class Add_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Add_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Add Error:Expression 1 is not a Int");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Add Error:Expression 2 is not a Int");
        }
        EXPR_type = b->Int_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
//Subtraction Expression
// The following expression is a Integer operator and check if both expressions are type Int.
class Minus_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Minus_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Minus Error:Expression 1 is not a Int");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Minus Error:Expression 2 is not a Int");
        }
        EXPR_type = b->Int_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Multiplication Expression
// The following expression is a Integer operator and check if both expressions are type Int.
class Mul_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Mul_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Multiply Error:Expression 1 is not a Int");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Multiply Error:Expression 2 is not a Int");
        }
        EXPR_type = b->Int_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Division Expression
// The following expression is a Integer operator and check if both expressions are type Int.
class Div_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Div_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Divide Error:Expression 1 is not a Int");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Divide Error:Expression 2 is not a Int");
        }
        EXPR_type = b->Int_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Modulation Expression
// The following expression is a Integer operator and check if both expressions are type Int.
class Mod_EXPR : public EXPR {
public:
    EXPR* e1;
    EXPR* e2;

    Mod_EXPR(EXPR* a, EXPR* b) : e1(a), e2(b) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Modulus Error:Expression 1 is not a Int");
        }
        Type_Defined = Check(b->EXPR_type, b->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Modulus Error:Expression 2 is not a Int");
        }
        EXPR_type = b->Int_Type;
    }

    void accept(Visitor& v) {
        return v.visit(this);
    }
};

//Negation Expression
// The following expression is a Integer operator and check if  expression is type Int.
class Negation_EXPR : public EXPR {
public:
    EXPR* e1;

    Negation_EXPR(EXPR* a) : e1(a) {
        bool Type_Defined = true;
        Type_Defined = Check(a->EXPR_type, a->Int_Type);
        if (Type_Defined != true) {
            ExceptionThrow(Type_Error, "in AST Negation Error:Expression is not a Int");
        }
        EXPR_type = Int_Type;
    };

    void accept(Visitor& v) {
        return v.visit(this);
    }
};
 //Uses this function to verify if both inputs (in this case type value) is the same.
bool Check(int input, int EXPR) {
    if (input == EXPR) {

        return true;
    } else {
        return false;
    }
}



#endif /* AST_HPP */


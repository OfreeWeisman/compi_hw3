//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_SEMANTICS_H
#define COMPI3_SEMANTICS_H

//define the semantics for all the rules
//use the Node* definition of yystype

#include "Tokens.h"
#include "ScopesTable.h"
#include "hw3_output.hpp"
#include "DataStructures.h"

extern int yylineno;


//extern Node* yylval;

//marker1
void setup(DataStructures* globalTables);

//rule 1 : Program -> Funcs
void cleanup (DataStructures* globalTables);

//rule 4 : FuncDecl -> 𝑅𝑒𝑡𝑇𝑦𝑝𝑒 𝐼𝐷 𝐿𝑃𝐴𝑅𝐸𝑁 𝐹𝑜𝑟𝑚𝑎𝑙𝑠 𝑅𝑃𝐴𝑅𝐸𝑁 𝐿𝐵𝑅𝐴𝐶𝐸 𝑆𝑡𝑎𝑡𝑒𝑚𝑒𝑛𝑡𝑠 𝑅𝐵𝑅𝐴𝐶
void openScope(Node* type, Node* id, DataStructures* globalTables, vector<string>* funcArgs);

void closeScope(DataStructures* globalTables);

//rule 5 : RetType -> TYPE
Node* semantics5(Node* type);

//rule 6 : RetTYpe -> VOID
Node* semantics6();

//rule 7 : Formals -> epsilon
void addEmptyParametersList() {}

//rule 8 : Formals -> FormalsList
Node* addParametersList(Node* formalsList ,DataStructures* tables, vector<string>* funcArgs);

//rule 9 : FormalsList -> FormalsDecl
Node* semantics9(Node* formalsDecl);

//rule 10 : FormalList -> FormalDecl COMMA FormalsList
Node* semantics10(Node* formalsDecl, Node* comma, Node* formalsList, DataStructures* tables, vector<string>* funcArgs);

//rule 11 : FormalDecl -> TYPE ID
Node* semantics11(Node *type, Node *id, DataStructures *tables);

//rule 15 : Statements -> TYPE ID SC
void semantics15(Node* type, Node* id, Node* sc, DataStructures* tables);

//rule 31 : Type -> INT
Node* semanticsTypeInt();

//rule 32 : Type -> BYTE
Node* semanticsTypeByte();

//rule 33 : Type -> BOOL
Node* semanticsTypeBool();

//rule 35 : Exp -> Exp BINOP Exp
Node* semantics35(Node* exp1, Node* BINOP, Node* exp2);

//rule 38 : Exp -> NUM
Node* semantics38(Node* num);

//rule 39 : Exp -> NUM B
Node* semantics39(Node* num, Node* b);

//rule 41 : Exp -> TRUE
Node* semanticsTrue();

//rule 42 : Exp -> FALSE
Node* semanticsFalse();

//rule 43 : Exp -> NOT Exp
Node* semantics43(Node* expression);

//rule 44 : Exp -> Exp AND Exp
Node* semantics44(Node* exp1, Node* AND, Node* exp2);

//rule 45 : Exp -> Exp OR Exp
Node* semantics45(Node* exp1, Node* OR, Node* exp2);

//rule 46 : Exp -> Exp RELOP Exp
Node* semantics46(Node* exp1, Node* RELOP, Node* exp2);



#endif //COMPI3_SEMANTICS_H

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

//Marker_open
void openScope(DataStructures* tables);

//rule 1 : Program -> Funcs
void cleanup (DataStructures* globalTables, vector<string>* funcArgs);

//rule 4 : FuncDecl -> 𝑅𝑒𝑡𝑇𝑦𝑝𝑒 𝐼𝐷 𝐿𝑃𝐴𝑅𝐸𝑁 𝐹𝑜𝑟𝑚𝑎𝑙𝑠 𝑅𝑃𝐴𝑅𝐸𝑁 𝐿𝐵𝑅𝐴𝐶𝐸 𝑆𝑡𝑎𝑡𝑒𝑚𝑒𝑛𝑡𝑠 𝑅𝐵𝑅𝐴𝐶
void openFuncScope(Node* type, Node* id, Node* formals, DataStructures* globalTables, vector<string>* funcArgs);

void closeScope(DataStructures* globalTables, vector<string>* funcArgs);

//rule 5 : RetType -> TYPE
Node* semantics5(Node* type);

//rule 6 : RetTYpe -> VOID
Node* semantics6();

//rule 7 : Formals -> epsilon
//void addEmptyParametersList() {}

//rule 8 : Formals -> FormalsList
Node* addParametersList(Node* formalsList ,DataStructures* tables, vector<string>* funcArgs);

//rule 9 : FormalsList -> FormalsDecl
Node* semantics9(Node* formalsDecl,vector<string>* funcArgs);

//rule 10 : FormalList -> FormalDecl COMMA FormalsList
Node* semantics10(Node* formalsDecl, Node* comma, Node* formalsList, DataStructures* tables, vector<string>* funcArgs);

//rule 11 : FormalDecl -> TYPE ID
Node* semantics11(Node *type, Node *id, DataStructures *tables);

//rule 14 : Statement -> LBRACE Statement RBRACE
void semantics14(Node* statement);

//rule 15 : Statements -> TYPE ID SC
void semantics15(Node* type, Node* id, Node* sc, DataStructures* tables);

//rule 16 : Statement -> TYPE ID ASSIGN Exp SC
void semantics16(Node* type, Node* id, Node* assign, Node* exp, Node* sc, DataStructures* tables);

//rule 17 : Statement -> ID ASSIGN Exp SC
void semantics17(Node* id, Node* assign, Node* exp, Node* sc,DataStructures* tables);

//rule 18 : Statement -> Call SC
void semantics18(Node* call, Node* sc);

//rule 19 : Statement -> RETURN SC
void semantics19(Node* ret, Node* sc, DataStructures* tables);

//rule 20 : Statement -> RETURN Exp SC
void semantics20(Node* ret, Node* exp, Node* sc, DataStructures* tables);

//rule 21 : Statement -> IF LPAREN Exp RPAREN Statement
void semantics21(Node* exp, DataStructures* tables);

//rule 22 : IF LPAREN Exp RPAREN Statement ELSE Statement
void semantics22(Node* exp, DataStructures* tables);

//rule 23 : Statement -> WHILE LPAREN Exp RPAREN Statement
void semantics23(Node* exp, DataStructures* tables,int* inWhile);

//rule 24 : WHILE LPAREN Exp RPAREN Statement ELSE Statement
void semantics24(Node* exp, DataStructures* tables,int* inWhile);

//rule 25 : Statement -> BREAK SC
void semantics25(Node* BREAK, Node* sc, int* inWhile);

//rule 26 : Statement -> CONTINUE SC
void semantics26(Node* cont, Node* sc, int* inWhile);

//rule 27 : Call -> ID LPAREN Explist RPAREN
void semantics27(Node* id, Node* lparen, Node* explist, Node* rparen, DataStructures* tables, vector<string>* args);

//rule 28 : Call -> ID LPAREN RPAREN
void semantics28(Node* id, DataStructures* tables,vector<string>* args);

//rule 29 : Explist -> Exp
Node* semantics29(Node* exp);

//rule 30 : Explist -> Exp COMMA Explist
Node* semantics30(Node* exp, Node* COMMA, Node* explist);

//rule 31 : Type -> INT
Node* semanticsTypeInt();

//rule 32 : Type -> BYTE
Node* semanticsTypeByte();

//rule 33 : Type -> BOOL
Node* semanticsTypeBool();

//rule 34 : Exp -> LPAREN Exp RPAREN
Node* semantics34(Node* lparen, Node* exp, Node* rparen);

//rule 35 : Exp -> Exp BINOP Exp
Node* semantics35(Node* exp1, Node* BINOP, Node* exp2,DataStructures* tables);

//rule 36 : Exp -> ID
Node* semantics36(Node* id,DataStructures* tables);

//rule 37 : Exp -> Call
Node* semantics37(Node* call);

//rule 38 : Exp -> NUM
Node* semantics38(Node* num);

//rule 39 : Exp -> NUM B
Node* semantics39(Node* num, Node* b);

//rule 40 : Exp -> STRING
Node* semantics40(Node* str);

//rule 41 : Exp -> TRUE
Node* semanticsTrue();

//rule 42 : Exp -> FALSE
Node* semanticsFalse();

//rule 43 : Exp -> NOT Exp
Node* semantics43(Node* expression,DataStructures* tables);

//rule 44 : Exp -> Exp AND Exp
Node* semantics44(Node* exp1, Node* AND, Node* exp2,DataStructures* tables);

//rule 45 : Exp -> Exp OR Exp
Node* semantics45(Node* exp1, Node* OR, Node* exp2,DataStructures* tables);

//rule 46 : Exp -> Exp RELOP Exp
Node* semantics46(Node* exp1, Node* RELOP, Node* exp2, DataStructures* tables);



#endif //COMPI3_SEMANTICS_H

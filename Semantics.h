//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_SEMANTICS_H
#define COMPI3_SEMANTICS_H

//define the semantics for all the rules
//use the Node* definition of yystype

#include "Tokens.h"
#include "ScopesTable.h"
//extern Node* yylval;

//rule 4 : FuncDecl -> 𝑅𝑒𝑡𝑇𝑦𝑝𝑒 𝐼𝐷 𝐿𝑃𝐴𝑅𝐸𝑁 𝐹𝑜𝑟𝑚𝑎𝑙𝑠 𝑅𝑃𝐴𝑅𝐸𝑁 𝐿𝐵𝑅𝐴𝐶𝐸 𝑆𝑡𝑎𝑡𝑒𝑚𝑒𝑛𝑡𝑠 𝑅𝐵𝑅𝐴𝐶
void OpenScope(Node* type, Node* id, ScopesTable* scopesTable);

//rule 5 : RetType -> TYPE
Node* semantics5(Node* type);

//rule 6 : RetTYpe -> VOID
Node* semantics6();

//rule 7 : Formals -> epsilon
Node* addEmptyParametersList(ScopesTable* scopesTable);

//rule 8 : Formals -> FormalsList
Node* addParametersList(Node* formalsList ,ScopesTable* scopesTable);

//rule 9 : FormalsList -> FormalsDecl
Node* semantics9(Node* formalsDecl);

//rule 10 : FormalList -> FormalDecl COMMA FormalsList
Node* semantics10(Node* formalsDecl, Node* comma, Node* formalsList, ScopesTable* scopesTable);

//rule 11 : FormalDecl -> TYPE ID
Node* semantics11(Node *type, Node *id, ScopesTable *scopesTable);




//rule 15 : Statements -> TYPE ID SC
void semantics15(Node* type, Node* id, Node* sc, ScopesTable* scopesTable);

//rule 31 : Type -> INT
Node* semanticsTypeInt();

//rule 32 : Type -> BYTE
Node* semanticsTypeByte();

//rule 33 : Type -> BOOL
Node* semanticsTypeBool();

//rule 38 : Exp -> NUM
Node* semantics38(Node* num);

//rule 39 : Exp -> NUM B
Node* semantics39(Node* num, Node* b);

//rule 41 : Exp -> TRUE
Node* semanticsTrue();

//rule 42 : Exp -> FALSE
Node* semanticsFalse();


#endif //COMPI3_SEMANTICS_H

//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_SEMANTICS_H
#define COMPI3_SEMANTICS_H

//define the semantics for all the rules
//use the Node* definition of yystype

#include "Tokens.h"
#include "ScopesTable.h"

extern Node* yylval;

//rule 4 : FuncDecl -> 𝑅𝑒𝑡𝑇𝑦𝑝𝑒 𝐼𝐷 𝐿𝑃𝐴𝑅𝐸𝑁 𝐹𝑜𝑟𝑚𝑎𝑙𝑠 𝑅𝑃𝐴𝑅𝐸𝑁 𝐿𝐵𝑅𝐴𝐶𝐸 𝑆𝑡𝑎𝑡𝑒𝑚𝑒𝑛𝑡𝑠 𝑅𝐵𝑅𝐴𝐶
void OpenScope(Node* type, Node* id, ScopesTable* scopesTable);

//rule 7 : Formals -> epsilon
void addEmptyParametersList(ScopesTable* scopesTable);

//rule 8 : Formals -> FormalsList
void addParametersList(list<TypesEnum>* parametersList ,ScopesTable* scopesTable);

//rule 15 : Statements -> TYPE ID SC
void semantics15(Node* type, Node* id, Node* sc, ScopesTable* scopesTable);

//rule 31 : Type -> INT
Node* semanticsTypeInt();

//rule 32 : Type -> BYTE
Node* semanticsTypeByte();

//rule 33 : Type -> BOOL
Node* semanticsTypeBool();

//rule 41 : Exp -> TRUE
Node* semanticsTrue();

//rule 42 : Exp -> FALSE
Node* semanticsFalse();


#endif //COMPI3_SEMANTICS_H

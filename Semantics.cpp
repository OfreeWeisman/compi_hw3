//
// Created by Ofree on 5/22/2020.
//

#include "Semantics.h"

Node *semanticsTypeInt() {
    return new Type(INT_ENUM);
}

void semantics15(Node *type, Node *id, Node *sc, ScopesTable *scopesTable) {
    //check if this id already exists in ths scopes table

    Scope* current_scope =scopesTable->getLastScope();
    string id_name = dynamic_cast<Id*>(id)->getIdName();
    if(current_scope->symbolExists(id_name)){
        //return error;
    }
    TypesEnum types_enum = dynamic_cast<Type*>(type)->getTypeName();
    Symbol* new_symbol = new Symbol(id_name, types_enum ,scopesTable->getRelativeLocation()+1, (int)current_scope->getMySymbols()->size()+1);
    scopesTable->addSymbol(new_symbol);


}

Node *semanticsTypeByte() {
    return new Type(BYTE_ENUM);
}

Node *semanticsTypeBool() {
    return new Type(BOOL_ENUM);
}

void OpenScope(Node *type, Node *id, ScopesTable *scopesTable) {
    //add the scope name to the current scope and then open the new scope
    string name = dynamic_cast<Id*>(id)->getIdName();
    TypesEnum types_enum = dynamic_cast<Type*>(type)->getTypeName();
    Scope* current_scope = scopesTable->getLastScope();
    if(current_scope->symbolExists(name)){
       //error already defined
    }
    //parameter list
    FunctionSymbol* new_symbol = new FunctionSymbol(name, types_enum ,scopesTable->getRelativeLocation(),(int)current_scope->getMySymbols()->size()+1, nullptr);
    scopesTable->addSymbol(new_symbol);

    Scope* new_scope = new Scope();
    scopesTable->getScopes()->push_back(new_scope);

}

void addEmptyParametersList(ScopesTable *scopesTable) {
    //do nothing
}

void addParametersList(list<TypesEnum> *parametersList, ScopesTable *scopesTable) {
    Scope* current_scope = scopesTable->getLastScope();
    //add all the parameters list as symbols but they need to be with negative relative location so we know that we can find their names
    int size =
}



//
// Created by Ofree on 5/22/2020.
//

#include "Semantics.h"
#include "Tokens.h"
#include "NonTerminals.h"



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

    Scope* new_scope = new Scope(current_scope);
    scopesTable->getScopes()->push_back(new_scope);

}

Node* addEmptyParametersList(ScopesTable *scopesTable) {
    return new Parameters();
}

Node* addParametersList(Node *formalsList, ScopesTable *scopesTable) {
    Parameters* p = dynamic_cast<Parameters*>(formalsList);
    list<TypesEnum>* parametersList = p->getParametersList();
    Scope* current_scope = scopesTable->getLastScope();
    //add all the parameters list as symbols but they need to be with negative relative location so we know that we can find their names
    //in the father scope the function symbol was added as the last symbol. to this function symbol we wish to add the parameters list
    FunctionSymbol* functionSymbol = (FunctionSymbol*)current_scope->getFatherScope()->getLastSymbol();
    functionSymbol->setParametersList(parametersList);
    return formalsList;
}

Node* semantics11(Node *type, Node *id, ScopesTable *scopesTable) {
    string name = dynamic_cast<Id*>(id)->getIdName();
    TypesEnum types_enum = dynamic_cast<Type*>(type)->getTypeName();
    Scope* current_scope = scopesTable->getLastScope();
    if(current_scope->symbolExists(name)){
        //error
    } else {
        current_scope->incParametersListSize();
        Symbol* new_symbol = new Symbol(name, types_enum ,-1, -1*(current_scope->getParametersListSize()));
        scopesTable->addSymbol(new_symbol);
    }
    return new Parameters(types_enum);


}

Node *semantics10(Node *formalsDecl, Node *comma, Node *formalsList, ScopesTable *scopesTable) {
    //cocongfl two lists to build the parameters list of the function
    Parameters* parameters1 = dynamic_cast<Parameters*>(formalsDecl);
    Parameters* parameters2 = dynamic_cast<Parameters*>(formalsList);
    list<TypesEnum>* list1 = parameters1->getParametersList();
    list<TypesEnum>* list2 = parameters2->getParametersList();
    list1->insert(list1->end(), list2->begin(), list2->end());
    delete(list2);
    delete(parameters2);
    return new Parameters(list1);



    //return new Parameters(parameters1, parameters2);

}

Node *semantics9(Node *formalsDecl) {
    return formalsDecl;
}

Node *semantics5(Node *type) {
    return type;
}

Node *semantics6() {
    return new Type(VOID_ENUM);
}

Node *semantics38(Node* num) {
    int value = dynamic_cast<Num*>(num)->getValue();
    return new NonTerminalNum(value);
}

Node *semantics39(Node *num, Node *b) {
    Byte* byte = dynamic_cast<Byte*>(num);
    if(byte->isValidByte()){
        return new NonTerminalByte(byte->getValue());
    } else {
        //error
    }
    //error instead
    return nullptr;
}



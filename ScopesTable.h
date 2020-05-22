//
// Created by Ofree on 5/21/2020.
//

#ifndef COMPI3_SCOPESTABLE_H
#define COMPI3_SCOPESTABLE_H

#include <list>
#include "Symbol.h"

using namespace std;

class Scope {
private:
    list<Scope*> innerScopes;
    list<Symbol*>* mySymbols;
    Scope* fatherScope;

    bool symbolExistsAux(string symbolName, Scope* scope){

        if (scope->mySymbols->size() == 0) {
            return false;
        }
        for(Symbol* s : *scope->mySymbols){
            if (s->getName() == symbolName){
                return true;
            }
        }
        if(!fatherScope) {
            return false;
        }
        return symbolExistsAux(symbolName ,scope->fatherScope);

    }

public:
    bool symbolExists(string symbolName){
        //assumption: we are looking for the symbol in the current scope and the scopes that contain the current scope
        return symbolExistsAux(symbolName, this);
    }

    list<Symbol *>* getMySymbols() const {
        return mySymbols;
    }
    //add/remove to my symbols and inner scopes while reading the code
};

class ScopesTable {
private:
    list<Scope*>* scopes;
    int relativeLocation;

public:
    ScopesTable();

    Scope* getLastScope();
    void incRelativeLocation();
    void addSymbol(Symbol* symbol);
    int getRelativeLocation() const;

    list<Scope *> *getScopes();
};


#endif //COMPI3_SCOPESTABLE_H

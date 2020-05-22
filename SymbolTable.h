//
// Created by Ofree on 5/21/2020.
//

#ifndef COMPI3_SYMBOLTABLE_H
#define COMPI3_SYMBOLTABLE_H


#include "Symbol.h"
#include <list>

using namespace std;


class SymbolTable {

private:
    list<Scope*> scopes;
    //int currentScope;
    list<Symbol*> SymbolsList;

public:
    SymbolTable(int currentScope, int SymbolsNum, const list<Symbol *> &SymbolsList);
    SymbolTable();
};


#endif //COMPI3_SYMBOLTABLE_H


function 1 {

};

function 2{
    int x;

    function 2.1{
        y=5
    }
    int y;
    function 2.2{

    };
};
//
// Created by Ofree on 5/21/2020.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable(int currentScope, int SymbolsNum, const list<Symbol *> &SymbolsList) : currentScope(
        currentScope), SymbolsNum(SymbolsNum), SymbolsList(SymbolsList) {}

SymbolTable::SymbolTable() {}


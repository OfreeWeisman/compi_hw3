//
// Created by Ofree on 5/21/2020.
//

#include "ScopesTable.h"

list<Scope *>* ScopesTable::getScopes()  {
    return scopes;
}

Scope *ScopesTable::getLastScope() {
    return *scopes->end();
}

void ScopesTable::incRelativeLocation() {
    relativeLocation++;
}

int ScopesTable::getRelativeLocation() const {
    return relativeLocation;
}

void ScopesTable::addSymbol(Symbol *symbol) {
    incRelativeLocation();
    Scope* current_scope = getLastScope();
    list<Symbol*>* symbols = current_scope->getMySymbols();
    symbols->push_back(symbol);
}

ScopesTable::ScopesTable() {
    scopes = nullptr;
    relativeLocation = -1;
}


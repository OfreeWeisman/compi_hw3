//
// Created by Ofree on 5/25/2020.
//

#include "DataStructures.h"

DataStructures::DataStructures() {
    offsetsTable = nullptr;
    symbolsTable = nullptr;

}

void DataStructures::pushNewScope() {
    symbolsTable->push(new list<Symbol*>());
    int last_offset = offsetsTable->top();
    offsetsTable->push(last_offset);
}

void DataStructures::popScope() {
    list<Symbol*> temp = symbolsTable->top();
    for(Symbol* s : temp){
        delete(s);
    }
    symbolsTable->pop();
    offsetsTable->pop();
}

void DataStructures::pushNewSymbol(Symbol *s) {
    list<Symbol*>* temp = symbolsTable->top();
    //check if needed (to pop and push or maybe just top
    symbolsTable->pop();
    temp->push_back(s);
    symbolsTable->push(temp);
}

Symbol::Symbol(const string &type, int offset, const string &name) : type(type), offset(offset), name(name) {}

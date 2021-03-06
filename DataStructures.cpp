//
// Created by Ofree on 5/25/2020.
//

#include <iostream>
#include "DataStructures.h"
using namespace std;

DataStructures::DataStructures() {
    offsetsTable = new stack<int>();
    symbolsTable = new stack<list<Symbol*>*>();

}

void DataStructures::pushNewScope() {
    symbolsTable->push(new list<Symbol*>());

    int last_offset;
    if(offsetsTable->size() == 0){
        last_offset = 0;
    }else{
        last_offset = offsetsTable->top();
    }
    offsetsTable->push(last_offset);

}

void DataStructures::popScope() {
    if(!symbolsTable->empty()) {


        list < Symbol * > temp = *symbolsTable->top();
        for (Symbol *s : temp) {
            //delete(s);
        }
        symbolsTable->pop();
        offsetsTable->pop();
    }
}

void DataStructures::pushNewSymbol(Symbol *s) {
    list<Symbol*>* temp = symbolsTable->top();
    //check if needed (to pop and push or maybe just top
    symbolsTable->pop();
    temp->push_back(s);
    symbolsTable->push(temp);
}

stack<int> *DataStructures::getOffsetsTable() const {
    return offsetsTable;
}

void DataStructures::setOffsetsTable(stack<int> *offsetsTable) {
    DataStructures::offsetsTable = offsetsTable;
}

stack<list<Symbol *> *> *DataStructures::getSymbolsTable() const {
    return symbolsTable;
}

void DataStructures::setSymbolsTable(stack<list<Symbol *> *> *symbolsTable) {
    DataStructures::symbolsTable = symbolsTable;
}



Symbol::Symbol(const string &type, int offset, const string &name) : type(type), offset(offset), name(name) {
}

const string &Symbol::getType() const {
    return type;
}

void Symbol::setType(const string &type) {
    Symbol::type = type;
}

int Symbol::getOffset() const {
    return offset;
}

void Symbol::setOffset(int offset) {
    Symbol::offset = offset;
}

const string &Symbol::getName() const {
    return name;
}

void Symbol::setName(const string &name) {
    Symbol::name = name;
}

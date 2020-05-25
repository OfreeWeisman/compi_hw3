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
    symbolsTable->pop();
    offsetsTable->pop();
}

//
// Created by Ofree on 5/21/2020.
//
/*
#include "Symbol.h"

Symbol::Symbol() {}

Symbol::Symbol(string name, TypesEnum type, int relativeLocation, int relativeLocationInScope) {
    this->name = name;
    this->type = type;
    this->relativeLocation = relativeLocation;
    this->relativeLocationInScope = relativeLocationInScope;
}

Symbol::Symbol(Symbol* s) {
    name = s->getName();
    type = s->getType();
    relativeLocation = s->getRelativeLocation();
    relativeLocationInScope = s->getRelativeLocationInScope();
}

const string &Symbol::getName() const {
    return name;
}

TypesEnum Symbol::getType() const {
    return type;
}

int Symbol::getRelativeLocation() {
    return relativeLocation;
}

int Symbol::getRelativeLocationInScope() {
    return relativeLocationInScope;
}


FunctionSymbol::FunctionSymbol(const string &name, TypesEnum type, int relativeLocation, int relativeLocationInScope,
                               list<TypesEnum> *parametersList) {

}

void FunctionSymbol::setParametersList(list<TypesEnum> *list) {
    parametersList = list;
}
*/
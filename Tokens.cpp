//
// Created by Ofree on 5/22/2020.
//

#include "Tokens.h"

Type::Type(TypesEnum typeName) : typeName(typeName) {}

TypesEnum Type::getTypeName() const {
    return typeName;
}



Id::Id(const string &idName) : idName(idName) {}

const string &Id::getIdName() const {
    return idName;
}

Bool::Bool(BoolEnum boolEnum) : boolEnum(boolEnum) {}

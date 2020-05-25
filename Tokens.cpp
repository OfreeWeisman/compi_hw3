//
// Created by Ofree on 5/22/2020.
//

#include "Tokens.h"


TypesEnum Type::getTypeName() const {
    return typeName;
}

Type::Type(string typeName) {
    if(typeName == "VOID"){
        this->typeName = VOID_ENUM;
    }

}


Id::Id(const string &idName) : idName(idName) {}

const string &Id::getIdName() const {
    return idName;
}

Bool::Bool(BoolEnum boolEnum) : boolEnum(boolEnum) {}

Parameters::Parameters(TypesEnum type) {
    parametersList->push_back(type);
}

list<TypesEnum> *Parameters::getParametersList() {
    return parametersList;
}

void Parameters::setParametersList(list<TypesEnum> *parameters) {
    Parameters::parametersList = parameters;
}

Parameters::Parameters(list<TypesEnum> *list) {
    parametersList = list;
}

Num::Num(string &strValue) : strValue(strValue) {
    value = atoi((char*)strValue);
}

int Num::getValue() const {
    return value;
}

void Num::setValue(int value) {
    Num::value = value;
}

const string &Num::getStrValue() const {
    return strValue;
}

void Num::setStrValue(const string &strValue) {
    Num::strValue = strValue;
}

int Byte::getValue() const {
    return value;
}

void Byte::setValue(int value) {
    Byte::value = value;
}

Byte::Byte(char *strValue) : strValue(strValue){
    value = atoi(strValue);

}

bool Byte::isValidByte() {
    if(value <= 255 && value > 0){
        return true;
    }
    return false;

}

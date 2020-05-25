//
// Created by Ofree on 5/22/2020.
//

#include "Tokens.h"






Id::Id(const string &idName) : idName(idName) {}

const string &Id::getIdName() const {
    return idName;
}

Bool::Bool(BoolEnum boolEnum) : boolEnum(boolEnum) {}


Num::Num(char* strValue) : strValue(strValue) {
    value = atoi(strValue);
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

const string &Parameter::getId() {
    return id;
}

Parameter::Parameter(const string &type, const string &id) : type(type), id(id) {
    names = new list<string>();
    types = new list<string>();
}

list<string> *Parameter::getNames() {
    return names;
}

void Parameter::setNames(list<string> *names) {
    Parameter::names = names;
}

list<string> *Parameter::getTypes()  {
    return types;
}

void Parameter::setTypes(list<string> *types) {
    Parameter::types = types;
}

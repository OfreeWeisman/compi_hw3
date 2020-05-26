//
// Created by Ofree on 5/22/2020.
//

#include "Tokens.h"






Id::Id(const string &idName) : idName(idName) {}

const string &Id::getIdName() const {
    return idName;
}

Bool::Bool(BoolEnum boolEnum) : boolEnum(boolEnum) {
    setType(BOOL_ENUM);

}

BoolEnum Bool::getBoolEnum() const {
    return boolEnum;
}

void Bool::setBoolEnum(BoolEnum boolEnum) {
    Bool::boolEnum = boolEnum;
}


Num::Num(char* strValue) : strValue(strValue) {
    value = atoi(strValue);
    setType(INT_ENUM);

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

Num::Num() {
    setType(INT_ENUM);
}

int Byte::getValue() const {
    return value;
}

void Byte::setValue(int value) {
    Byte::value = value;
}

Byte::Byte(char *strValue) : strValue(strValue){
    value = atoi(strValue);
    setType(BYTE_ENUM);


}

bool Byte::isValidByte() {
    if(value <= 255 && value > 0){
        return true;
    }
    return false;

}

Byte::Byte() {
    setType(BYTE_ENUM);
}

const string &Parameter::getId() {
    return id;
}

Parameter::Parameter(const string &type, const string &id) : type(type), id(id) {
    setType(NULL_ENUM);
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

Parameter::Parameter() {
    setType(NULL_ENUM);
    id = nullptr;
    type = nullptr;
    names = new list<string>();
    types = new list<string>();
}

Expression::Expression() {
    setType(NULL_ENUM);

}

Expression::Expression(const string &id, const string &type) : id(id), type(type) {
    setType(NULL_ENUM);

}

const string &Expression::getId() const {
    return id;
}

void Expression::setId(const string &id) {
    Expression::id = id;
}

const string &Expression::getType() const {
    return type;
}

void Expression::setTypeStr(const string &type) {
    Expression::type = type;
}

Relop::Relop() {
    setType(NULL_ENUM);

}

Relop::Relop(const string &relop) : relop(relop) {
    setType(NULL_ENUM);

}

const string &Relop::getRelop() const {
    return relop;
}

void Relop::setRelop(const string &relop) {
    Relop::relop = relop;
}

Binop::Binop(const string &binop) : binop(binop) {}

Binop::Binop() {}

const string &Binop::getBinop() const {
    return binop;
}

void Binop::setBinop(const string &binop) {
    Binop::binop = binop;
}

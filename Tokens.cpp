//
// Created by Ofree on 5/22/2020.
//

#include "Tokens.h"
#include <iostream>
using namespace std;






Id::Id(const string &idName) : idName(idName) {}

const string &Id::getIdName() const {
    return idName;
}

Bool::Bool(BoolEnum boolEnum) : boolEnum(boolEnum) {
    setType(BOOL_ENUM);
    setTypes("bool");

}

BoolEnum Bool::getBoolEnum() const {
    return boolEnum;
}

void Bool::setBoolEnum(BoolEnum boolEnum) {
    Bool::boolEnum = boolEnum;
}

Bool::Bool() {
    setType(BOOL_ENUM);
    setTypes("bool");
}


Num::Num(char* strValue) : strValue(strValue) {
    value = atoi(strValue);
    setType(INT_ENUM);
    setTypes("int");

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
    setTypes("int");
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
    setTypes("byte");


}

bool Byte::isValidByte() {
    if(value <= 255 && value > 0){
        return true;
    }
    return false;

}

Byte::Byte() {
    setType(BYTE_ENUM);
    setTypes("byte");

}

const string &Parameter::getId() {
    return id;
}

Parameter::Parameter(const string &type, const string &id) : type(type), id(id) {
    if(type == "STRING"){
        setType(STRING_ENUM);
    } else if (type == "INT"){
        setType(INT_ENUM);
    } else if (type == "BYTE"){
        setType(BYTE_ENUM);
    } else if(type == "VOID"){
        setType(VOID_ENUM);
    } else if ( type == "BOOL"){
        setType(BOOL_ENUM);

    }
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
   //types = new list<string>();


}

Expression::Expression(const string &id, const string &type) : id(id), type(type) {
    setType(NULL_ENUM);
    //types = new list<string>();

}

const string &Expression::getId() const {
    return id;
}

void Expression::setId(const string &id) {
    Expression::id = id;
}

const string &Expression::getExpType() const {
    return type;
}

void Expression::setTypeStr(const string &type) {
    Expression::type = type;
}
/*
list<string> *Expression::getTypes()  {
    return types;
}
*/
Expression::Expression(const string &id, const string &type, list<string> *types) : id(id), type(type) {}

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

String::String() {
    setType(STRING_ENUM);
    setTypes("STRING");
}

String::String(string str) : str(str) {
    setType(STRING_ENUM);

    setTypes("STRING");

}

const string &String::getStr() const {
    return str;
}

void String::setStr(const string &str) {
    String::str = str;
}


Str::Str(const string &str) : str(str) {
    setType(STRING_ENUM);
    setTypes("STRING");
}

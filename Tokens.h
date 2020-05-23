//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_TYPES_H
#define COMPI3_TYPES_H
#define YYSTYPE Node*

#include <string>
#include <list>
#include "Enums.h"

using namespace std;


class Node{
public:
    Node() = default;
    ~Node(){}
};

class Type : public Node{
private:
    TypesEnum typeName;
public:
    Type(TypesEnum typeName);
    TypesEnum getTypeName() const;
};

class Id : public Node {
private:
    string idName;
public:
    Id(const string &idName);
    const string &getIdName() const;

};

class Num : public Node {
private:
    int value;
    string strValue;
public:
    Num(string &strValue);
    int getValue() const;
    void setValue(int value);
    const string &getStrValue() const;
    void setStrValue(const string &strValue);

};

class Byte : public Node {
    int value;
    char* strValue;
public:
    Byte(char* strValue);
    int getValue() const;
    void setValue(int value);
    bool isValidByte();


};

class Bool : public Node {
public:
    Bool(BoolEnum boolEnum);
private:
    BoolEnum boolEnum;
};

class Parameters : public Node {
private:
    list<TypesEnum>* parametersList;
public:
    Parameters() {}
    Parameters(TypesEnum type);
    Parameters(list<TypesEnum>* list);
    list<TypesEnum> *getParametersList();
    void setParametersList(list<TypesEnum> *parameters);

};




#endif //COMPI3_TYPES_H

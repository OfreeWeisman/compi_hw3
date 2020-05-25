//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_TYPES_H
#define COMPI3_TYPES_H

#include <string>
#include <list>
#include "Enums.h"
//keep this !!!!!! VV
#define YYSTYPE Node*

using namespace std;


class Node{
private:
    TypesEnum type;
public:
    Node(){};
    virtual ~Node(){}

    TypesEnum getType() const {
        return type;
    }

    void setType(TypesEnum type) {
        Node::type = type;
    }
};

class Type : public Node{
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
    Num(char* strValue);
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


#define YYSTYPE Node*


#endif //COMPI3_TYPES_H

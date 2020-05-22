//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_TYPES_H
#define COMPI3_TYPES_H
#define YYSTYPE Node*

#include <string>
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

class Bool : public Node {
public:
    Bool(BoolEnum boolEnum);

private:
    BoolEnum boolEnum;
};




#endif //COMPI3_TYPES_H

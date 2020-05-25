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
    string getTypeAsString(TypesEnum t){
        switch (t) {
            case INT_ENUM : return "int";
            case BOOL_ENUM : return "bool";
            case BYTE_ENUM : return "byte";
        }
    }
};

class Type : public Node{
public:
    Type(TypesEnum t){}
    //TypesEnum getTypeName() ;
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

class Parameter : public Node {
private:
    string type;
    string id;
    list<string>* names;
    list<string>* types;

public:
    Parameter() {}

    Parameter(const string &type, const string &id);

    const string &getId();

    list<string> *getNames();

    void setNames(list<string> *names);

    list<string> *getTypes() ;

    void setTypes(list<string> *types);

};


#define YYSTYPE Node*


#endif //COMPI3_TYPES_H

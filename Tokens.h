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
    list<string>* types;

public:
    string str;
    Node(){
        type = NULL_ENUM;
    };
    virtual ~Node(){}
    TypesEnum getType() const {
        return type;
    }
    void setType(TypesEnum type) {
        Node::type = type;
    }
    string getTypeAsString(TypesEnum t){
        switch (t) {
            case INT_ENUM : return "INT";
            case BOOL_ENUM : return "BOOL";
            case BYTE_ENUM : return "BYTE";
            case VOID_ENUM : return "VOID";
            case STRING_ENUM: return "STRING";
        }
    }
    void setTypes(string t){
        types->push_back(t);
    }
    list<string> *getTypes() {
        return types;
    }
};

class Type : public Node{
public:
    Type(TypesEnum t){
        this->setType(t);
    }
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

    Num();

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

    Byte();

    int getValue() const;
    void setValue(int value);
    bool isValidByte();


};

class Bool : public Node {
public:
    Bool(BoolEnum boolEnum);

    Bool();

    BoolEnum getBoolEnum() const;
    void setBoolEnum(BoolEnum boolEnum);
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
    Parameter();
    Parameter(const string &type, const string &id);
    const string &getId();
    list<string> *getNames();
    void setNames(list<string> *names);
    list<string> *getTypes() ;
    void setTypes(list<string> *types);

};

class Expression : public Node {
public:
    Expression(const string &id, const string &type);
    Expression();

    Expression(const string &id, const string &type, list<string> *types);

    const string &getId() const;
    void setId(const string &id);
    const string &getExpType() const;
    void setTypeStr(const string &type);

   // list<string> *getTypes();

private:
    string id;
    string type;
   // list<string>* types;
};

class Relop : public Node{
private:
    string relop;
public:
    Relop();
    Relop(const string &relop);
    const string &getRelop() const;
    void setRelop(const string &relop);

};

class Binop : public Node {
public:
    Binop(const string &binop);

    const string &getBinop() const;

    void setBinop(const string &binop);

    Binop();

private:
    string binop;

};


class Str : public Node{
public:
    Str(const string &str);

private:
    string str;
public:
};



class String : public Node {
public:
    String();
    String(string str);
    const string &getStr() const;
    void setStr(const string &str);

private:
    string str;
};
#define YYSTYPE Node*


#endif //COMPI3_TYPES_H

//
// Created by Ofree on 5/22/2020.
//

#ifndef COMPI3_NONTERMINALS_H
#define COMPI3_NONTERMINALS_H


#include "Enums.h"
#include "Tokens.h"

class NonTerminalBool : public Node{
private:
    TypesEnum typesEnum;
public:
    bool canExpBeBool(Node* node);
};

class NonTerminalNum : public Node {
private:
    int value;
    TypesEnum type;
public:
    NonTerminalNum();
    NonTerminalNum(int value);
};

class NonTerminalByte : public Node{
private:
    int value;
    TypesEnum type;
public:
    NonTerminalByte();
    NonTerminalByte(int value);
};


#endif //COMPI3_NONTERMINALS_H

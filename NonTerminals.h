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


#endif //COMPI3_NONTERMINALS_H

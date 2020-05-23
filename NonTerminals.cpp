//
// Created by Ofree on 5/22/2020.
//

#include "NonTerminals.h"

bool NonTerminalBool::canExpBeBool(Node* node) {




    return false;
}

NonTerminalNum::NonTerminalNum(int value) {
    this->value = value;
    type = INT_ENUM;
}

NonTerminalNum::NonTerminalNum() {
    type = INT_ENUM;
}

NonTerminalByte::NonTerminalByte() {
    type = BYTE_ENUM;
}

NonTerminalByte::NonTerminalByte(int value) {
    this->value = value;
    type = BYTE_ENUM;
}



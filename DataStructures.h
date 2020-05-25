//
// Created by Ofree on 5/25/2020.
//

#ifndef COMPI3_DATASTRUCTURES_H
#define COMPI3_DATASTRUCTURES_H

#include <string>
#include <list>
#include <stack>

using namespace std;

class Symbol {
public:
    Symbol(const string &type, int offset, const string &name);

private:
    string type;
    int offset;
    string name;
public:

};

class DataStructures {
    stack<int>* offsetsTable;
    stack<list<Symbol*>*>* symbolsTable;


public:
    DataStructures();
    void popScope();
    void pushNewScope();
    void pushNewSymbol(Symbol* s);
};


#endif //COMPI3_DATASTRUCTURES_H

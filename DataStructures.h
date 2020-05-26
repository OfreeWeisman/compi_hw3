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
    const string &getType() const;
    void setType(const string &type);
    int getOffset() const;
    void setOffset(int offset);
    const string &getName() const;
    void setName(const string &name);

private:
    string type;
    int offset;
    string name;

};

class DataStructures {
    stack<int>* offsetsTable;
    stack<list<Symbol*>*>* symbolsTable;
public:
    DataStructures();
    void popScope();
    void pushNewScope();
    void pushNewSymbol(Symbol* s);
    stack<int> *getOffsetsTable() const;
    void setOffsetsTable(stack<int> *offsetsTable);
    stack<list<Symbol *> *> *getSymbolsTable() const;
    void setSymbolsTable(stack<list<Symbol *> *> *symbolsTable);
};


#endif //COMPI3_DATASTRUCTURES_H

//
// Created by Ofree on 5/25/2020.
//

#ifndef COMPI3_DATASTRUCTURES_H
#define COMPI3_DATASTRUCTURES_H

#include <string>
#include <list>
#include <stack>

using namespace std;

struct Symbol {
    string type;
    int offset;
    string name;
};

class DataStructures {
    stack<int>* offsetsTable;
    stack<list<Symbol*>*>* symbolsTable;

public:

    DataStructures();
    void pushNewScope();
    void popScope();
};


#endif //COMPI3_DATASTRUCTURES_H

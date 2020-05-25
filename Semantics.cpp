//
// Created by Ofree on 5/22/2020.
//

#include "Semantics.h"
#include "Tokens.h"
#include "NonTerminals.h"
extern int yylineno;


//-------------------------------------------------helper functions---------------------------------------------------//
/*
 * throws an error if that symbol already exists
 */
void symbolExistsinList(list<Symbol*>* currList, string name){
    list<Symbol*>::iterator it = currList->begin();
    for(it; it != currList->end(); it++){
        Symbol* temp = *it;
        if(temp->getName() == name){
            output::errorDef(yylineno, name);
            exit(0);
        }
    }
}

/*
 * throws an error if symbol already exists somewhere in the stack.
 */
void searchIfPreDefined(Node* id, DataStructures* tables) {
    Id *i = dynamic_cast<Id *>(id);
    string name = i->getIdName();

    stack<list<Symbol *> *> *symbolTables = tables->getSymbolsTable();
    //look through all lists in the stack. must create a copy and pop from there, then copy it back.
    DataStructures *tempDS = new DataStructures();
    stack<list<Symbol *> *> *tempSymbolTable = tempDS->getSymbolsTable();
    while (!symbolTables->empty()) {
        list<Symbol *> *currList = symbolTables->top();
        symbolExistsinList(currList, name);
        tempSymbolTable->push(currList);
        symbolTables->pop();
    }
    while (!tempSymbolTable->empty()) {
        list<Symbol *> *currList = tempSymbolTable->top();
        symbolTables->push(currList);
        tempSymbolTable->pop();
    }

}


list<string>* combineLists(list<string>* list1, list<string>* list2){
    //use new
    list<string>* new_list = new list<string>();
    list<string>::iterator it = list1->begin();
    for(it; it!=list1->end(); it++){
        new_list->push_back(*it);
    }
   it = list2->begin();
    for(it; it!=list2->end(); it++){
        new_list->push_back(*it);
    }
    return new_list;
}





//----------------------------------------------Type Checking Functions-----------------------------------------------//
//rule 2:

BoolEnum checkexpBool(Node* operand1){
    Bool* check = (dynamic_cast<Bool*>(operand1));
    if(dynamic_cast<Bool*>(operand1)){
        return check->getBoolEnum();
    }else{
        output::errorMismatch(yylineno);
        exit(0);
    }
}

//rule 8:
TypesEnum checkLegalRelop(Node* operand1, Node* operand2){
    //check both operands are numerical
    if((dynamic_cast<Num*>(operand1) || dynamic_cast<Byte*>(operand1)) &&
       (dynamic_cast<Num*>(operand2) || dynamic_cast<Byte*>(operand2))){
        return BOOL_ENUM;
    } else {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

//rule 9:
TypesEnum checkLogicalOp(Node* operand1, Node* operand2){
    if(dynamic_cast<Bool*>(operand1) && dynamic_cast<Bool*>(operand2)){
        return BOOL_ENUM;
    } else {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

//rule 10:
TypesEnum checkLegalBinop(Node* operand1, Node* operand2) {
    //check both operands are numerical
    TypesEnum type1 = operand1->getType();
    TypesEnum type2 = operand2->getType();

    if (type1 == type2) {
        return type1;
    } else if ((type1 == INT_ENUM || type1 == BYTE_ENUM) && (type2 == INT_ENUM || type2 == BYTE_ENUM)) {
        return INT_ENUM;
    } else {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

//rule 16:
bool checkIfWhileTypes(Node* exp){
    if(exp->getType() == BOOL_ENUM){
        return true;
    } else {
        output::errorMismatch(yylineno);
        exit(0);
    }
}




//-----------------------------------------------Semantics Functions--------------------------------------------------//

Node *semanticsTypeInt() {
    return new Type(INT_ENUM);
}

void semantics15(Node *type, Node *id, Node *sc, DataStructures* tables) {
    //check if this id already exists in the symbol table
    searchIfPreDefined(id, tables);


    TypesEnum t = dynamic_cast<Type*>(type)->getType();
    string typeString = type->getTypeAsString(t);
    string name = dynamic_cast<Id*>(id)->getIdName();

    int offset= tables->getOffsetsTable()->top();

    tables->getOffsetsTable()->push(offset+1);

    Symbol* new_symbol = new Symbol(typeString, offset+1 ,name );
    tables->pushNewSymbol(new_symbol);

}

Node *semanticsTypeByte() {
    return new Type(BYTE_ENUM);
}

Node *semanticsTypeBool() {
    return new Type(BOOL_ENUM);
}


void openScope(Node *type, Node *id, DataStructures* tables, vector<string>* functionArgs) {
    //add the scope name to the current scope and then open the new scope
    searchIfPreDefined(id, tables);
    string name = dynamic_cast<Id*>(id)->getIdName();
    TypesEnum types_enum = dynamic_cast<Type*>(type)->getType();
    string funcType = output::makeFunctionType(type->getTypeAsString(types_enum), *functionArgs);
    functionArgs->clear();
    Symbol* s = new Symbol(funcType, 0, name);
    tables->pushNewSymbol(s);
    tables->pushNewScope();
}


void closeScope(DataStructures* globalTables){
    globalTables->popScope();
}



Node* addParametersList(Node *formalsList, DataStructures* tables, vector<string>* funcArgs) {
    Parameter* p = dynamic_cast<Parameter*>(formalsList);
    list<string>* names = p->getNames();
    list<string>* types = p->getTypes();
    list<string>::iterator it1 = names->begin();
    list<string>::iterator it2 = types->begin();

    int offset = -1;
    int length = names->size();
    for(int i = 0; i < length; i++){
        Symbol* s = new Symbol(*it2++, offset--, *it1++);
        tables->pushNewSymbol(s);
    }
    return formalsList;
}

Node* semantics11(Node *type, Node *id, DataStructures *tables) {
    string id_name = dynamic_cast<Id*>(id)->getIdName();
    return new Parameter(type->getTypeAsString(type->getType()), id_name);

}

Node *semantics10(Node *formalsDecl, Node *comma, Node *formalsList, DataStructures* tables, vector<string>* funcArgs) {
    //cocongfl two lists to build the parameters list of the function
    Parameter* parameter1 = dynamic_cast<Parameter*>(formalsDecl);
    Parameter* parameter2 = dynamic_cast<Parameter*>(formalsList);
    string id1 = parameter1->getId();
    string type1 = parameter1->getTypeAsString(parameter1->getType());
    string id2 = parameter2->getId();
    string type2 = parameter2->getTypeAsString(parameter2->getType());
    Parameter* p = new Parameter(id1.append(",").append(id2), type1.append(",").append(type2));
    list<string>* names_temp = combineLists(parameter1->getNames(), parameter2->getNames());
    p->setNames(names_temp);
    list<string>* types_temp = combineLists(parameter1->getTypes(), parameter2->getTypes());
    p->setTypes(types_temp);
    funcArgs->insert(funcArgs->begin(), type1);

    delete parameter1->getNames();
    delete parameter2->getNames();
    delete parameter1->getTypes();
    delete parameter2->getTypes();

    return p;
}

Node *semantics9(Node *formalsDecl) {
    return formalsDecl;
}

Node *semantics5(Node *type) {
    return type;
}

Node *semantics6() {
    return new Type(VOID_ENUM);
}

Node *semantics38(Node* num) {
    int value = dynamic_cast<Num*>(num)->getValue();
    return new NonTerminalNum(value);
}

Node *semantics39(Node *num, Node *b) {
    Byte* byte = dynamic_cast<Byte*>(num);
    if(byte->isValidByte()){
        return new NonTerminalByte(byte->getValue());
    } else {
        //error
    }
    //error instead
    return nullptr;
}

Node* semanticsTrue(){
    return new Bool(TRUE_ENUM);
}

Node* semanticsFalse(){
    return new Bool(FALSE_ENUM);
}


void setup(DataStructures* globalTables) {
    globalTables->pushNewScope();
    Symbol* s1 = new Symbol("string -> void", 0, "print");
    globalTables->pushNewSymbol(s1);
    Symbol* s2 = new Symbol("int -> void", 0, "printi");
    globalTables->pushNewSymbol(s2);
}

void cleanup(DataStructures* globalTables) {
    globalTables->popScope();

}





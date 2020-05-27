//
// Created by Ofree on 5/22/2020.
//

#include "Semantics.h"
#include "Tokens.h"
#include "NonTerminals.h"
#include <iostream>
using namespace std;
extern int yylineno;


//-------------------------------------------------helper functions---------------------------------------------------//
/*
 * throws an error if that symbol already exists
 */
void symbolExistsinList(list<Symbol*>* currList, string name){
   // cout<<"SymbolExistsList"<<endl;
    list<Symbol*>::iterator it = currList->begin();
    for(it; it != currList->end(); it++){
        Symbol* temp = *it;
        if(temp->getName() == name){
            output::errorDef(yylineno, name);
            exit(0);
        }
    }
  //  cout<<"SymbolExistsListFINISH"<<endl;

}

/*
 * throws an error if symbol already exists somewhere in the stack.
 */
void searchIfPreDefined(Node* id, DataStructures* tables) {
    Id *i = dynamic_cast<Id*>(id);
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
  //  cout<<"push back intostack"<<endl;
    while (!tempSymbolTable->empty()) {
        list<Symbol *> *currList = tempSymbolTable->top();
        symbolTables->push(currList);
        tempSymbolTable->pop();
    }
  //  cout<<"searchIfPreDefinedFINISHED"<<endl;

}

Symbol* getSymbolinList(list<Symbol *> *currList, string name){
    list<Symbol*>::iterator it = currList->begin();
    Symbol* temp;
    for(it; it != currList->end(); it++){
        temp = *it;
        if(temp->getName() == name){
            return temp;
        }
    }
    return nullptr;
}
list<Symbol*>* getFuncUsingId(Node* id, DataStructures* tables){

    Id* i = dynamic_cast<Id*>(id);
    string func_name = i->getIdName();
    stack<list<Symbol*>*>* symbolTable = tables->getSymbolsTable();
    //look through all lists in the stack. must create a copy and pop from there, then copy it back.
    DataStructures *tempDS = new DataStructures();
    stack<list<Symbol *> *> *tempSymbolTable = tempDS->getSymbolsTable();

    list<Symbol *> *currList;
    Symbol* func = nullptr;
    list<Symbol*>* funcs_args = nullptr;

    while (!symbolTable->empty()) {
        currList = symbolTable->top();
        func = getSymbolinList(currList, func_name);
        tempSymbolTable->push(currList);
        symbolTable->pop();
    }
    list<Symbol *> *currListBack;
    while (!tempSymbolTable->empty()) {
        currListBack = tempSymbolTable->top();
        if(!symbolTable->empty()) {
            if (getSymbolinList(symbolTable->top(), func_name)) { //since if its here, then the func is the next one.
                funcs_args = currListBack;
            }
        }

        symbolTable->push(currListBack);
        tempSymbolTable->pop();
    }


    if(func == nullptr){
        output::errorUndefFunc(yylineno, func_name);
        exit(0);
    }


    return funcs_args;

}


/*
 * only returns the func's arguments.
 */
list<Symbol*>* getFunctionsArgs(Node* id, DataStructures* tables){

    list<Symbol*>* funcs_args = getFuncUsingId(id, tables);
    //I've got the paramter list. now I'll only take out the negative offsets which are the arguments of the function.
    list<Symbol*>* l = new list<Symbol*>();
    list<Symbol*>::iterator it = funcs_args->begin();

    Symbol* func;
    for(it; it != funcs_args->end(); it++){
        func = *it;
        if(func->getOffset() < 0){

            l->push_back(func);
        }
    }
    return l;

}

list<string>* combineLists(list<string>* list1, list<string>* list2){
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



//TODO:to finish this up
Node* getFunctionRetType(Node* id, DataStructures* tables){
    //find the function in the symbol table
    //get the retType of the function
    //return New of this type
    //type_name is the string of the type
    Id* i = dynamic_cast<Id*>(id);
    string func_name = i->getIdName();
    stack<list<Symbol*>*>* symbolTable = tables->getSymbolsTable();
    //look through all lists in the stack. must create a copy and pop from there, then copy it back.
    DataStructures *tempDS = new DataStructures();
    stack<list<Symbol *> *> *tempSymbolTable = tempDS->getSymbolsTable();
    list<Symbol *> *currList;
    Symbol* func = nullptr;
    while (!symbolTable->empty()) {
        currList = symbolTable->top();
        func = getSymbolinList(currList, func_name);
        tempSymbolTable->push(currList);
        symbolTable->pop();
    }
    list<Symbol *> *currListBack;
    while (!tempSymbolTable->empty()) {
        currListBack = tempSymbolTable->top();
        symbolTable->push(currListBack);
        tempSymbolTable->pop();
    }

    if(func == nullptr){
        output::errorUndefFunc(yylineno, func_name);
        exit(0);
    }

    string funcs_type = func->getType();
    std::size_t pos = funcs_type.find("->");      // position of "live" in str

    string ret_type = funcs_type.substr (pos);     // get from "live" to the end


    if(ret_type == "bool"){
        return new Bool();
    } else if(ret_type == "int"){
        return new Num();
    } else {
        return new Byte();
    }



//
}


//----------------------------------------------Type Checking Functions-----------------------------------------------//
//rule 2:

BoolEnum checkExpBool(Node* operand1){
    //cout<<operand1->getTypeAsString(operand1->getType())<<endl;

    Bool* check = (dynamic_cast<Bool*>(operand1));
    if(dynamic_cast<Bool*>(operand1)){
        return check->getBoolEnum();
    }else{
        cout<< "problem? "<<endl;
        output::errorMismatch(yylineno);
        exit(0);
    }
}

//rule 6+7:
//TODO: what else should we be checking here?
void checkLegalAssignment(Node* id, Node* exp){
    //it is legal to assign byte to int
    Id* i = dynamic_cast<Id*>(id);
    string id_type = i->getTypeAsString(i->getType());
    Num* num = dynamic_cast<Num*>(exp);
    Byte* byte = dynamic_cast<Byte*>(exp);
    Bool* b =  dynamic_cast<Bool*>(exp);
    if(id_type == "int" && (!num && !byte)){ //we've received an int, but the expression isn't int nor byte.
        output::errorMismatch(yylineno);
        exit(0);
    }else if(id_type == "bool" && !b){ //we've received a bool, but the expression isn't a bool.
        output::errorMismatch(yylineno);
        exit(0);
    }else if(id_type == "byte" && !byte){ //we've received a bool, but the expression isn't a bool.
        output::errorMismatch(yylineno);
        exit(0);
    }

}

//rule 8:
void checkLegalRelop(Node* operand1, Node* operand2){
    //check both operands are numerical
    if((dynamic_cast<Num*>(operand1) || dynamic_cast<Byte*>(operand1)) &&
       (dynamic_cast<Num*>(operand2) || dynamic_cast<Byte*>(operand2))){
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

//rule 14:
void checkValidArgs(list<string>* types, list<Symbol*>* args){
    //compare the lists
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

string getFunctionRetTypeFromTable(DataStructures* tables){
    list<Symbol*>* top_scope = tables->getSymbolsTable()->top();
    tables->getSymbolsTable()->pop();
    list<Symbol*>* inner_scope = tables->getSymbolsTable()->top();
    Symbol* function = inner_scope->back();
    string type = function->getType();
    tables->getSymbolsTable()->push(top_scope);

    return type;

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

void openScope(DataStructures* tables){
    tables->pushNewScope();

}

void openFuncScope(Node *type, Node *id, DataStructures* tables, vector<string>* functionArgs) {
    //add the scope name to the current scope and then open the new scope
    searchIfPreDefined(id, tables);

    string name = dynamic_cast<Id*>(id)->getIdName();
    TypesEnum types_enum = dynamic_cast<Type*>(type)->getType();
    //cout<<type->getTypeAsString(types_enum)<<endl;

   // cout<<"dynamic casts finished"<<endl;

    string funcType = output::makeFunctionType(type->getTypeAsString(types_enum), *functionArgs);
   // cout<<"makefunctiontype finished"<<endl;

    functionArgs->clear();
    Symbol* s = new Symbol(funcType, 0, name);
    tables->pushNewSymbol(s);
   // cout<<"push new symbolFinished"<<endl;
    tables->pushNewScope();
   // cout<<"push new scope finished"<<endl;

}

void closeScope(DataStructures* globalTables){
    //print the top scope
    output::endScope();
    list<Symbol*>* scope = globalTables->getSymbolsTable()->top();
    cout<<"yes"<<endl;
    Symbol* s;
    cout<<"the size is "<<scope->size()<<endl;
    list<Symbol*>::iterator it = scope->begin();
    for(it ; it != scope->end(); it++){
        s = *it;
        output::printID(s->getName(),s->getOffset(), s->getType());
    }
    cout<<"yes"<<endl;
    cout<<"before poping the table, the size of the top is "<<globalTables->getSymbolsTable()->top()->size()<<endl;

    globalTables->popScope();
    cout<<"after poping the table, the size of the top is "<<globalTables->getSymbolsTable()->top()->size()<<endl;
}

Node* addParametersList(Node *formalsList, DataStructures* tables, vector<string>* funcArgs) {
    Parameter* p = dynamic_cast<Parameter*>(formalsList);
    if(p==nullptr){
      //  cout <<"p is null"<< endl;
    }
    list<string>* names = p->getNames();
    list<string>* types = p->getTypes();
    list<string>::iterator it1 = names->begin();
    list<string>::iterator it2 = types->begin();

    cout<<"enter"<<endl;
    int offset = -1;
    int length = names->size();
    cout<<"enter- names size "<<length<<endl;

    for(int i = 0; i < length; i++){
        cout<<*it1<<" "<<*it2<<endl;
        Symbol* s = new Symbol(*it2++, offset--, *it1++);
        tables->pushNewSymbol(s);
    }
    return formalsList;
}

Node* semantics11(Node *type, Node *id, DataStructures *tables) {
    string id_name = dynamic_cast<Id*>(id)->getIdName();
    cout<<"name of the one with no type is "<<id_name <<endl;
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

  //  delete parameter1->getNames();
  //  delete parameter2->getNames();
  //  delete parameter1->getTypes();
  //  delete parameter2->getTypes();

    return p;
}

Node *semantics9(Node *formalsDecl) {
    cout<<"9"<<endl;
    Parameter* parameter1 = dynamic_cast<Parameter*>(formalsDecl);

    string id1 = parameter1->getId();
    list<string>* names_temp = new list<string>();
    names_temp->push_back(id1);

    cout<<"before type 1 is "<<endl;
    if(parameter1->getType() == NULL_ENUM){
        cout<<"null"<<endl;
    }
    string type1 = parameter1->getTypeAsString(parameter1->getType());
    cout<<"type 1 is "<<type1<<endl;

    list<string>* types_temp = new list<string>();

    types_temp->push_back(type1);
    cout<<"fail"<<endl;

    parameter1->setNames(names_temp);
    parameter1->setTypes(types_temp);
    cout<<"end of 9 "<<endl;
    return formalsDecl;
}

Node *semantics5(Node *type) {
    return type;
}

Node *semantics6() {
    return new Type(VOID_ENUM);
}

Node *semantics38(Node* num) {
    return num;
}

Node *semantics39(Node *num, Node *b) {
    Byte* byte = dynamic_cast<Byte*>(num);
    if(byte->isValidByte()){
        return num;
    } else {
        //error
    }
}

Node* semanticsTrue(){
    return new Bool(TRUE_ENUM);
}

Node* semanticsFalse(){
    return new Bool(FALSE_ENUM);
}

void setup(DataStructures* globalTables) {
    globalTables->pushNewScope();
   // cout<<"1"<<std::endl;
    vector<string>* temp = new vector<string>();
    temp->push_back("STRING");
    Symbol* s1 = new Symbol(output::makeFunctionType("VOID", *temp), 0, "print");
    temp->clear();
  //  cout<<"2"<<std::endl;

    globalTables->pushNewSymbol(s1);
   // cout<<"3"<<std::endl;
    temp->push_back("INT");
    Symbol* s2 = new Symbol(output::makeFunctionType("VOID", *temp), 0, "printi");
  //  cout<<"1"<<std::endl;
    temp->clear();

    globalTables->pushNewSymbol(s2);
    /*
    list<Symbol*>* scope = globalTables->getSymbolsTable()->top();
    list<Symbol*>::iterator it = scope->begin();
    for(it; it != scope->end(); it++ ){
        Symbol* s = *it;
        output::printID(s->getName(),s->getOffset(), s->getType());

    }
     */

   // cout<<"end of setup"<<std::endl;
}

void cleanup(DataStructures* globalTables) {
    globalTables->popScope();

}

Node *semantics43(Node *expression) {
    BoolEnum b = checkExpBool(expression);
    if(FALSE_ENUM == b){
        dynamic_cast<Bool*>(expression)->setBoolEnum(TRUE_ENUM);
        return expression;
    } else {
        dynamic_cast<Bool*>(expression)->setBoolEnum(FALSE_ENUM);
        return expression;
    }
}

Node *semantics44(Node *exp1, Node *AND, Node *exp2) {
    BoolEnum b1 = checkExpBool(exp1);
    BoolEnum b2 = checkExpBool(exp2);

    if(b1 == b2){
     //   delete(exp2);
        return exp1;
    } else if(b1 == FALSE_ENUM) {
     //   delete(exp2);
        return exp1;
    } else {
     //   delete(exp1);
        return exp2;
    }

}

Node *semantics45(Node *exp1, Node *OR, Node *exp2) {
    BoolEnum b1 = checkExpBool(exp1);
    BoolEnum b2 = checkExpBool(exp2);

    if(b1 == TRUE_ENUM){
      //  delete(exp2);
        return exp1;
    } else {
      //  delete(exp1);
        return exp2;
    }
}

Node *semantics46(Node *exp1, Node *RELOP, Node *exp2) {

    //check if the expressions are ok to relop
    checkLegalRelop(exp1, exp2);
    int v1;
    int v2;

    if(exp1->getType() == BYTE_ENUM){
        v1 = dynamic_cast<Byte*>(exp1)->getValue();
    } else {
        v1 = dynamic_cast<Num*>(exp1)->getValue();
    }

    if(exp2->getType() == BYTE_ENUM){
        v2 = dynamic_cast<Byte*>(exp2)->getValue();
    } else {
        v2 = dynamic_cast<Num*>(exp2)->getValue();
    }

    string r = dynamic_cast<Relop*>(RELOP)->getRelop();

  //  delete(exp1);
   // delete(exp2);
  //  delete(RELOP);

    if(r == "<"){
        if (v1 < v2){
            return new Bool(TRUE_ENUM);
        } else {
            return new Bool(FALSE_ENUM);
        }
    } else if (r == ">"){
        if (v1 < v2){
            return new Bool(FALSE_ENUM);
        } else {
            return new Bool(TRUE_ENUM);
        }
    } else if (r == "<="){
        if (v1 <= v2){
            return new Bool(TRUE_ENUM);
        } else {
            return new Bool(FALSE_ENUM);
        }
    } else if (r == ">="){
        if (v1 <= v2){
            return new Bool(FALSE_ENUM);
        } else {
            return new Bool(TRUE_ENUM);
        }
    } else if (r == "=="){
        if (v1 == v2){
            return new Bool(TRUE_ENUM);
        } else {
            return new Bool(FALSE_ENUM);
        }
    } else if (r == "!="){
        if (v1 != v2){
            return new Bool(TRUE_ENUM);
        } else {
            return new Bool(FALSE_ENUM);
        }
    }

}

Node *semantics35(Node *exp1, Node *BINOP, Node *exp2) {
    TypesEnum type = checkLegalBinop(exp1, exp2);

    int v1;
    int v2;

    if(exp1->getType() == BYTE_ENUM){
        v1 = dynamic_cast<Byte*>(exp1)->getValue();
    } else {
        v1 = dynamic_cast<Num*>(exp1)->getValue();
    }

    if(exp2->getType() == BYTE_ENUM){
        v2 = dynamic_cast<Byte*>(exp2)->getValue();
    } else {
        v2 = dynamic_cast<Num*>(exp2)->getValue();
    }
    string b = dynamic_cast<Relop*>(BINOP)->getRelop();

  //  delete(exp1);
  //  delete(exp2);
  //  delete(BINOP);

    if(b == "+"){
        if (type == INT_ENUM){
            Num* n = new Num();
            n->setValue(v1+v2);
            return n;

        } else {
            Byte* b = new Byte();
            b->setValue(v1+v2);
            return b;
        }
    } else if (b == "-"){
        if (type == INT_ENUM){
            Num* n = new Num();
            n->setValue(v1-v2);
            return n;

        } else {
            Byte* b = new Byte();
            b->setValue(v1-v2);
            return b;
        }
    } else if (b == "*"){
        if (type == INT_ENUM){
            Num* n = new Num();
            n->setValue(v1+v2);
            return n;

        } else {
            Byte* b = new Byte();
            b->setValue(v1*v2);
            return b;
        }
    }
}

Node *semantics40(Node *str) {
   // cout<<"in 40"<<endl;
    String* s = dynamic_cast<String*>(str);
    Expression* e = new Expression(s->getStr(), "STRING");
    return e;
}

Node *semantics34(Node *lparen, Node *exp, Node *rparen) {
    return exp;
}

Node *semantics36(Node *id) {
   // cout<<"exp->id"<<endl;

    return id;
}

Node *semantics37(Node *call) {
   // cout<<"in 37"<<endl;

    return call;
}

Node* semantics28(Node *id, DataStructures* tables) {
    Id* i = dynamic_cast<Id*>(id);
    vector<string>* args = new vector<string>();
    list<Symbol*>* s = getFunctionsArgs(id, tables); // search if id exists
    if(!s->empty()){
        output::errorPrototypeMismatch(yylineno, i->getIdName(), *args);
    }
    return getFunctionRetType(id, tables);


}

Node *semantics29(Node *exp) {
   // cout<<"in 29"<<endl;
    return exp;
}

Node *semantics30(Node *exp, Node *COMMA, Node *explist) {
    Expression* e1 = dynamic_cast<Expression*>(exp);
    Expression* e2 = dynamic_cast<Expression*>(explist);

    list<string>* temp = combineLists(e1->getTypes(), e2->getTypes());
    Expression* expression = new Expression(e1->getId(), e1->getExpType(), temp);
 //   delete(exp);
 //   delete(explist);
  //  delete(COMMA);
    return expression;
}

Node* semantics27(Node *id, Node *lparen, Node *explist, Node *rparen, DataStructures* tables) {
    Expression* e = dynamic_cast<Expression*>(explist);
   // cout<<"dynamic cast"<<endl;
    list<string>* types = e->getTypes();
  //  cout<<"get types"<<endl;
    list<Symbol*>* s = getFunctionsArgs(id, tables);
   // cout<<"create s"<<endl;

    checkValidArgs(types, s); //throw error if mismatch
  //  cout<<"valid args"<<endl;

    //find the function in the symbol table
    //get the retType of the function
    //return New of this type
    return getFunctionRetType(id,tables);

}

void semantics26(Node *cont, Node *sc, int inWhile) {
    if(!inWhile){
        output::errorUnexpectedContinue(yylineno);
        exit(0);
    }
}

void semantics25(Node *BREAK, Node *sc, int inWhile) {
    if(!inWhile){
        output::errorUnexpectedBreak(yylineno);
        exit(0);
    }
}

void semantics18(Node *call, Node *sc) {
  //  delete(call);
}

void semantics17(Node *id, Node *assign, Node *exp, Node *sc) {
    checkLegalAssignment(id,exp);
  //  delete(id);
  //  delete(exp);
}

void semantics16(Node *type, Node *id, Node *assign, Node *exp, Node *sc, DataStructures* tables) {
    searchIfPreDefined(id, tables);

    TypesEnum t = dynamic_cast<Type*>(type)->getType();
    string typeString = type->getTypeAsString(t);
    string name = dynamic_cast<Id*>(id)->getIdName();

    int offset = tables->getOffsetsTable()->top();

    tables->getOffsetsTable()->push(offset+1);

    Symbol* new_symbol = new Symbol(typeString, offset+1 ,name );
    tables->pushNewSymbol(new_symbol);

    checkLegalAssignment(id,exp);
  //  delete(id);
  //  delete(exp);
  //  delete(type);

}

void semantics19(Node *ret, Node *sc, DataStructures *tables) {
    string returnType = getFunctionRetTypeFromTable(tables);
    if (returnType != "void") {
        output::errorMismatch(yylineno);
        exit(0);
    }
   // delete(ret);
}

void semantics20(Node *ret, Node *exp, Node *sc, DataStructures *tables) {
    string returnType = getFunctionRetTypeFromTable(tables);
    if (returnType == "void") {
        output::errorMismatch(yylineno);
        exit(0);
    }
  //  delete(ret);
 //   delete(exp);
}

void semantics14(Node* statement){
 //   delete(statement);
}

void checkExpBoolFromExpression(Node* operand1){
    Id* check = (dynamic_cast<Id*>(operand1));
    if(!check){
        cout<<"check is not an id"<<endl;
    }
    if(check->getIdName() != "bool"){
        output::errorMismatch(yylineno);
        exit(0);
    }
}


void semantics21(Node *exp) {
    checkExpBoolFromExpression(exp);
   // delete(exp);
}

void semantics22(Node *exp) {
    checkExpBool(exp);
 //   delete(exp);
}

void semantics23(Node *exp) {
    checkExpBool(exp);
    //delete(exp);
}

void semantics24(Node *exp) {
    checkExpBool(exp);
  //  delete(exp);
}





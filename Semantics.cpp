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
    cout<<"searchIfPreDefined"<<endl;

    Id *i = dynamic_cast<Id*>(id);
    if(!i){
         cout<<"i is not id"<<endl;

    }
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
    cout<<"searchIfPreDefinedFINISHED"<<endl;

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
        cout<<"error getFuncUsingId"<<endl;
        output::errorUndefFunc(yylineno, func_name);
        exit(0);
    }


    return funcs_args;

}


/*
 * only returns the func's arguments.
 */
list<Symbol*>* getFunctionsArgs(Node* id, DataStructures* tables, vector<string>* args){

    list<Symbol*>* funcs_args = getFuncUsingId(id, tables);
    if(funcs_args == nullptr){
        cout<<"funcargs == null"<<endl;
    }
    //I've got the paramter list. now I'll only take out the negative offsets which are the arguments of the function.
    list<Symbol*>* l = new list<Symbol*>();
    list<Symbol*>::iterator it = funcs_args->begin();

    Symbol* func;
    for(it; it != funcs_args->end(); it++){
        func = *it;
        if(func->getOffset() < 0){
            cout<<"function args? "<<func->getType()<<endl;
            l->push_back(func);
            args->push_back(func->getType());
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
string getFunctionRetType(Node* id, DataStructures* tables){
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
        cout<<"error getFunctionRetType"<<endl;
        output::errorUndefFunc(yylineno, func_name);
        exit(0);
    }

    string funcs_type = func->getType();
    std::size_t pos = funcs_type.find("->");      // position of "live" in str

    string ret_type = funcs_type.substr (pos);     // get from "live" to the end

    return ret_type;



//
}

string getIdType(Node* id, DataStructures* tables) {

    //only for ids (ignore the name func)

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
        if(func == nullptr){
            func = getSymbolinList(currList, func_name);
        }
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
        cout<<"error getIdType"<<endl;
        output::errorUndef(yylineno, func_name);
        exit(0);
    }


    return func->getType();
//    cout<<"ret type is "<<ret_type<<endl;
//
//    if(ret_type == "BOOL"){
//        return new Bool();
//    } else if(ret_type == "INT"){
//        return new Num();
//    } else {
//        return new Byte();
//    }
}


//----------------------------------------------Type Checking Functions-----------------------------------------------//
//rule 2:

void checkExpBool(Node* operand1, DataStructures* tables){
    //cout<<operand1->getTypeAsString(operand1->getType())<<endl;
    Id* i = dynamic_cast<Id*>(operand1);
    string type;
    if(i){
        type = getIdType(operand1, tables);
    } else {
        type = operand1->getTypeAsString(operand1->getType());
    }
    if(type != "BOOL"){
        cout<< "checkExpBool "<<type<<endl;
        output::errorMismatch(yylineno);
        exit(0);
    }
//    Bool* check = (dynamic_cast<Bool*>(operand1));
//    if(dynamic_cast<Bool*>(operand1)){
//        return check->getBoolEnum();
//    }else{
//        cout<< "checkExpBool "<<endl;
//        output::errorMismatch(yylineno);
//        exit(0);
//    }
}

//rule 6+7:
//TODO: what else should we be checking here?
void checkLegalAssignment(Node* id, Node* exp ,DataStructures* tables){
    cout<<"checkLegalAssignment"<<endl;
    //it is legal to assign byte to int
    Id* i = dynamic_cast<Id*>(id);
    if(i == nullptr){
        cout<<"i isnt id "<<endl;
    }
    string id_type = getIdType(id,tables);
    cout<<"id type "<<id_type << endl;

    string exp_type = exp->getTypeAsString(exp->getType());
    cout << "exp type is "<<exp_type<<endl;

//    Num* num = dynamic_cast<Num*>(exp);
//    Byte* byte = dynamic_cast<Byte*>(exp);
//    Bool* b =  dynamic_cast<Bool*>(exp);


    if(id_type == "INT" && (exp_type!= "INT" && exp_type!="BYTE")){ //we've received an int, but the expression isn't int nor byte.
        output::errorMismatch(yylineno);
        exit(0);
    }else if(id_type == "BOOL" && exp_type!="BOOL"){ //we've received a bool, but the expression isn't a bool.
        output::errorMismatch(yylineno);
        exit(0);
    }else if(id_type == "BYTE" && exp_type!="BYTE"){ //we've received a bool, but the expression isn't a bool.
        output::errorMismatch(yylineno);
        exit(0);
    }

    cout<<"endcheckLegalAssignment"<<endl;

}




void checkLegalAssignmentWhenTypeGiven(Node* type, Node* exp){
    cout<<"checkLegalAssignmentwhentypegiven"<<endl;
    //it is legal to assign byte to int
    Type* t = dynamic_cast<Type*>(type);


    string id_type =  t->getTypeAsString(t->getType());
    cout<<"id type "<<id_type << endl;


//    Num* num = dynamic_cast<Num*>(exp);
//    Byte* byte = dynamic_cast<Byte*>(exp);
//    Bool* b =  dynamic_cast<Bool*>(exp);
    auto it = exp->getTypes()->begin();
    string exp_type = *it;

    if(id_type == "INT" && (exp_type!= "INT" && exp_type!="BYTE")){ //we've received an int, but the expression isn't int nor byte.
        output::errorMismatch(yylineno);
        exit(0);
    }else if(id_type == "BOOL" && exp_type!="BOOL"){ //we've received a bool, but the expression isn't a bool.
        output::errorMismatch(yylineno);
        exit(0);
    }else if(id_type == "BYTE" && exp_type!="BYTE"){ //we've received a bool, but the expression isn't a bool.
        output::errorMismatch(yylineno);
        exit(0);
    }
//    if(id_type == "INT" && (!num && !byte)){ //we've received an int, but the expression isn't int nor byte.
//        output::errorMismatch(yylineno);
//        exit(0);
//    }else if(id_type == "BOOL" && !b){ //we've received a bool, but the expression isn't a bool.
//        output::errorMismatch(yylineno);
//        exit(0);
//    }else if(id_type == "BYTE" && !byte){ //we've received a bool, but the expression isn't a bool.
//        output::errorMismatch(yylineno);
//        exit(0);
//    }

    cout<<"endcheckLegalAssignmentwhentypegiven"<<endl;

}

//rule 8:
void checkLegalRelop(Node* operand1, Node* operand2,  DataStructures* tables){
    //check both operands are numerical
    Id* i1= dynamic_cast<Id*>(operand1);
    Id* i2= dynamic_cast<Id*>(operand2);
    string s1;
    string s2;
    if(i1) {
        s1 = getIdType(operand1, tables);
    } else {
        s1 = operand1->getTypeAsString(operand1->getType());
    }

    if(i2) {
        s2 = getIdType(operand2, tables);
    } else {
        s2 = operand2->getTypeAsString(operand2->getType());
    }


    cout<<"s1 is "<<s1<<" s2 is "<<s2<<endl;

    if((s1 == "INT" || s1 =="BYTE") && (s2 == "INT" || s2 =="BYTE")){

    }else {
        cout<<"checkLegalRelop"<<endl;
        output::errorMismatch(yylineno);
        exit(0);
    }

//    if((dynamic_cast<Num*>(operand1) || dynamic_cast<Byte*>(operand1)) &&
//       (dynamic_cast<Num*>(operand2) || dynamic_cast<Byte*>(operand2))){
//
//    }else {
//            cout<<"checkLegalRelop"<<endl;
//            output::errorMismatch(yylineno);
//            exit(0);
//    }
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
void checkLegalBinop(Node* operand1, Node* operand2,  DataStructures* tables) {
    //check both operands are numerical
    Id* i1= dynamic_cast<Id*>(operand1);
    Id* i2= dynamic_cast<Id*>(operand2);
    string s1;
    string s2;
    if(i1) {
        s1 = getIdType(operand1, tables);
    } else {
        s1 = operand1->getTypeAsString(operand1->getType());
    }

    if(i2) {
        s2 = getIdType(operand2, tables);
    } else {
        s2 = operand2->getTypeAsString(operand2->getType());
    }



//    TypesEnum type1 = operand1->getType();
//    TypesEnum type2 = operand2->getType();
//
    if (s1 == s2) {
        return ;
    } else if ((s1 == "INT" || s1 == "BYTE") && (s2 == "INT" || s2 == "BYTE")) {
        return;
    } else {
        output::errorMismatch(yylineno);
        exit(0);
    }
}

//rule 14:
void checkValidArgs(list<string>* types,Node* id, list<string>* args){
    //compare the lists
    cout<<"checkValidArgs"<<endl;
    cout<<*types->begin()<<endl; // got STRING! :)
    Id* i = dynamic_cast<Id*>(id);
    if(i->getIdName() == "print"){
        string type = *types->begin();
        if(types->size() != 1 || type != "STRING"){
            vector<string>* vec = new vector<string>();
            vec->push_back("STRING");
            output::errorPrototypeMismatch(yylineno,i->getIdName(),*vec);
            exit(0);
        } else {
            return;
        }
    } else if (i->getIdName() == "printi"){
        string type = *types->begin();
        if(types->size() != 1 || type != "INT" && type != "BYTE"){
            vector<string>* vec = new vector<string>();
            vec->push_back("INT");
            output::errorPrototypeMismatch(yylineno,i->getIdName(),*vec);
            exit(0);
        } else {
            return;
        }
    }

    auto it = args->begin();

    vector<string>* vec = new vector<string>();
    for(it; it != args->end(); it++){
        //Symbol* s = *it;
        cout<<"creating the vector now - "<<*it<<endl;
        vec->push_back(*it);
    }
    cout<<"one size is "<<types->size()<<" two size is "<<args->size()<<endl;

    if(types->size() != args->size()){
        output::errorPrototypeMismatch(yylineno,i->getIdName(),*vec);
        exit(0);
    }



    auto itt = types->begin();
    auto itt2 = args->begin();
    string s;
    string name;
    for(itt; itt!=types->end(); itt++,itt2++){
        name = *itt;
        s = *itt2;

        cout<<"args  is  "<<s<<endl;
        cout<<"types  is "<<name<<endl;
        if(s == "INT" && name == "BYTE"){ ///changed this !!
            continue;
        }

        if(s!= name){
            output::errorPrototypeMismatch(yylineno,i->getIdName(),*vec);
            exit(0);
        }
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
    cout<<"semanticsTypeInt"<<endl;
    return new Type(INT_ENUM);
}

void semantics15(Node *type, Node *id, Node *sc, DataStructures* tables) {
    cout<<"semantics15"<<endl;
    //check if this id already exists in the symbol table
    searchIfPreDefined(id, tables);


    TypesEnum t = dynamic_cast<Type*>(type)->getType();
    string typeString = type->getTypeAsString(t);
    string name = dynamic_cast<Id*>(id)->getIdName();

    int offset= tables->getOffsetsTable()->top();
    tables->getOffsetsTable()->pop();
    tables->getOffsetsTable()->push(offset+1);

    Symbol* new_symbol = new Symbol(typeString, offset ,name );
    tables->pushNewSymbol(new_symbol);

    cout<<"end of semantics15"<<endl;


}

Node *semanticsTypeByte() {
    cout<<"semanticsTypeByte"<<endl;
    return new Type(BYTE_ENUM);
}

Node *semanticsTypeBool() {
    cout<<"semanticsTypeBool"<<endl;

    return new Type(BOOL_ENUM);
}

void openScope(DataStructures* tables){
    cout<<" open scope  "<<endl;
    tables->pushNewScope();

}

void openFuncScope(Node *type, Node *id, Node* formals, DataStructures* tables, vector<string>* functionArgs) {
    //add the scope name to the current scope and then open the new scope
    searchIfPreDefined(id, tables);

    Parameter* p  = dynamic_cast<Parameter*>(formals);
    if(p){
        if(p->getNames()){
            cout<<"in open func names size is "<<p->getNames()->size()<<endl;
            cout<<"in open func types size is "<<p->getTypes()->size()<<endl;
        }
    }


    Id* i =  dynamic_cast<Id*>(id);

    string name = dynamic_cast<Id*>(id)->getIdName();

    TypesEnum types_enum = dynamic_cast<Type*>(type)->getType();
    cout<<type->getTypeAsString(types_enum)<<endl;

   // cout<<"dynamic casts finished"<<endl;

    string funcType = output::makeFunctionType(type->getTypeAsString(types_enum), *functionArgs);
    cout<<"makefunctiontype in open funcscope returns "<< funcType<<endl;

    functionArgs->clear();

    //fill here the functionArgs vector with the functType

//
//    int i = 0;
//    int j = 0;
//    string parameter;
//    while(i < funcType.length()){
//        i = funcType.find(",");
//        parameter = funcType.substr(j,i);
//        j=i;
//        functionArgs->push_back(parameter);
//    }


//edit:
    Symbol* s = new Symbol(funcType, 0, name);
    //Symbol* s = new Symbol(type->getTypeAsString(types_enum), 0, name); // so only its return type.
    tables->pushNewSymbol(s);
    tables->pushNewScope();



    //insert here the functions' parameters in the new scope
    if(p){
        if(p->getTypes()){
            auto it1 = p->getTypes()->begin();
            auto it2 = p->getNames()->begin();
            int offset = -1;
            string curr_name ;
            string curr_type;

            for(it1; it1 != p->getTypes()->end(); it1++,it2++){
                curr_name = *it2;
                curr_type = *it1;
                cout<<"inserting the symbol to the functions list. type is  "<<curr_type<<" name is "<<curr_name<<" offset "<< offset<<endl;
                Symbol* s = new Symbol(curr_type, offset--, curr_name);
                tables->pushNewSymbol(s);
            }
        }
    }


}

void closeScope(DataStructures* globalTables, vector<string>* funcArgs){
    //print the top scope
    output::endScope();
    list<Symbol*>* scope = globalTables->getSymbolsTable()->top();
    cout<<"closescope"<<endl;
    Symbol* s;
    cout<<"the number of symbols in this scope is "<<scope->size()<<endl;
    list<Symbol*>::iterator it = scope->begin();
    for(it ; it != scope->end(); it++){
        s = *it;
        output::printID(s->getName(),s->getOffset(), s->getType());
    }
    funcArgs->clear();
    globalTables->popScope();
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

    int offset = -1;
    int length = names->size();
    vector<string>::iterator it3 = funcArgs->begin();
    for(it3; it3 != funcArgs->end(); it3++){
        string k  = *it3;
        cout<<"print out "<< k <<endl;
    }
//    for(int i = 0; i < length; i++){
//        cout<<*it1<<" "<<*it2<<endl;
//        Symbol* s = new Symbol(*it2++, offset--, *it1++);
//        tables->pushNewSymbol(s);
//    }
    return p;
}

Node* semantics11(Node *type, Node *id, DataStructures *tables) {
    string id_name = dynamic_cast<Id*>(id)->getIdName();
    Type* temp = dynamic_cast<Type*>(type);
    string typestring =temp->getTypeAsString(temp->getType());

    return new Parameter(type->getTypeAsString(type->getType()), id_name);

}

Node *semantics10(Node *formalsDecl, Node *comma, Node *formalsList, DataStructures* tables, vector<string>* funcArgs) {
    //cocongfl two lists to build the parameters list of the function
    cout<<"semantics 10 "<<endl;
    Parameter* parameter1 = dynamic_cast<Parameter*>(formalsDecl);
    Parameter* parameter2 = dynamic_cast<Parameter*>(formalsList);
    string id1 = parameter1->getId();

    string type1 = parameter1->getTypeAsString(parameter1->getType());
    string id2 = parameter2->getId();
    cout<<"id2 before appending is  "<<id2<< " and id 1 is " << id1<<endl;

    string type2 = parameter2->getTypeAsString(parameter2->getType());

   // cout<<"length of type 2 +1 "<<(id2.append(",").append(id1)).size()<<endl;
    string s;
    cout<<"max size "<<s.max_size()<<endl;

    cout<<"before appending -type 2   "<<type2<<" type 1-  "<<type1<<endl;


    string tnew =type2+","+(type1);
    string idnew = id2+","+(id1);
    cout<<"now they are  "<<tnew << " and    " <<idnew<<endl;

    Parameter* p = new Parameter(tnew,idnew);
    cout<<"semantics parameter "<<endl;

    list<string>* names_temp = combineLists(parameter1->getNames(),parameter2->getNames());
    p->setNames(names_temp);
    list<string>* types_temp = combineLists(parameter1->getTypes(),parameter2->getTypes());
    auto it = types_temp->begin();
    cout<<*it << " 1 "<< *(++it) << "2"<<endl;
    p->setTypes(types_temp);
    //funcArgs->push_back(type1);
    funcArgs->insert(funcArgs->begin(), type1);

  //  delete parameter1->getNames();
  //  delete parameter2->getNames();
  //  delete parameter1->getTypes();
  //  delete parameter2->getTypes();

    return p;
}

Node *semantics9(Node *formalsDecl,vector<string>* funcArgs) {
    cout<<"semantics 9"<<endl;
    Parameter* parameter1 = dynamic_cast<Parameter*>(formalsDecl);

   // int s = parameter1->getTypes()->size();
   // int s2 = parameter1->getNames()->size();

    string id1 = (parameter1->getId());
    list<string>* names_temp = new list<string>();
    names_temp->push_back(id1);

    if(parameter1->getType() == NULL_ENUM){
        cout<<"null"<<endl;
    }
    string type1 = parameter1->getTypeAsString(parameter1->getType());
    cout<<"im in semantics 9 the type is "<<type1<<" and id is  "<<id1<<endl;

    funcArgs->push_back(type1);

    return parameter1;
}

Node *semantics5(Node *type) {
    return type;
}

Node *semantics6() {
    return new Type(VOID_ENUM);
}

Node *semantics38(Node* num) {
    //return new Num();
    return num;
}

Node *semantics39(Node *num, Node *b) {

  //  Byte* byte = dynamic_cast<Byte*>(num);

    Num* number = dynamic_cast<Num*>(num);
    int value = number->getValue();
    if(value<= 255 && value > 0){
        cout<<"the byte value is "<<value<<endl;
        return num;
    } else {
        output::errorByteTooLarge(yylineno,number->getStrValue());
        exit(0);
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
    //maketemp->clear();
  //  cout<<"2"<<std::endl;
    temp->clear();
    globalTables->pushNewSymbol(s1);
   // cout<<"3"<<std::endl;
    temp->push_back("INT");
    Symbol* s2 = new Symbol(output::makeFunctionType("VOID", *temp), 0, "printi");
  //  cout<<"1"<<std::endl;
    temp->clear();

    globalTables->pushNewSymbol(s2);

}

void cleanup(DataStructures* globalTables, vector<string>* funcArgs) {
//    Id* i = new Id("main");
//    string type = getIdType(i,globalTables);
    //find main
    list<Symbol*>* list = globalTables->getSymbolsTable()->top();
    auto it = list->begin();
    bool is_main = false;
    for(it; it != list->end(); it++){
        Symbol* s = *it;
        cout<<"check main "<<s->getName()<<"  "<<s->getType()<<endl;
        if(s->getName() == "main" && s->getType()=="()->VOID"){
            is_main = true;
            break;
        }
    }
    if(!is_main){
        output::errorMainMissing();
        exit(0);
    }

    cout<<"cleanup"<<endl;
    closeScope(globalTables, funcArgs);
  //  globalTables->popScope();

}

Node *semantics43(Node *expression,DataStructures* tables) {
    checkExpBool(expression, tables);
//    if(FALSE_ENUM == b){
//        dynamic_cast<Bool*>(expression)->setBoolEnum(TRUE_ENUM);
//        return expression;
//    } else {
//        dynamic_cast<Bool*>(expression)->setBoolEnum(FALSE_ENUM);
//        return expression;
//    }
    return new Bool();
}

Node *semantics44(Node *exp1, Node *AND, Node *exp2,DataStructures* tables) {
    checkExpBool(exp1, tables);
    checkExpBool(exp2, tables);
    return new Bool();


//    if(b1 == b2){
//     //   delete(exp2);
//        return exp1;
//    } else if(b1 == FALSE_ENUM) {
//     //   delete(exp2);
//        return exp1;
//    } else {
//     //   delete(exp1);
//        return exp2;
//    }

}

Node *semantics45(Node *exp1, Node *OR, Node *exp2,DataStructures* tables) {
    checkExpBool(exp1,tables);
    checkExpBool(exp2,tables);
    return new Bool();


//    if(b1 == TRUE_ENUM){
//      //  delete(exp2);
//        return exp1;
//    } else {
//      //  delete(exp1);
//        return exp2;
//    }
}

Node *semantics46(Node *exp1, Node *RELOP, Node *exp2, DataStructures* tables) {
    //check if the expressions are ok to relop

    checkLegalRelop(exp1, exp2, tables);

    int v1;
    int v2;


   // string typeName1 = dynamic_cast<Id*>(exp1)->getIdName(); //should check if its "BYTE" OR "INT"
    //string typeName2 = dynamic_cast<Id*>(exp2)->getIdName();//should check if its "BYTE" OR "INT"


    return new Bool();
//    Expression* exp = new Expression();
//    exp->setTypes("BOOL");

/*
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

    cout<<"Semantics46yes"<<endl;

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
    */

}

Node *semantics35(Node *exp1, Node *BINOP, Node *exp2,DataStructures* tables) {
    checkLegalBinop(exp1, exp2,tables);

    cout<<"back from check binop"<<endl;

    string t1;
    string t2;

    Id* i1 = dynamic_cast<Id*>(exp1);
    Id* i2 = dynamic_cast<Id*>(exp2);
     if(i1){
         t1 = getIdType(exp1, tables);
     } else {
         t1 = exp1->getTypeAsString(exp1->getType());
     }
    if(i2){
        t2 = getIdType(exp2, tables);
    } else {
        t2= exp2->getTypeAsString(exp2->getType());
    }

    if(t1 == "BYTE" && t2 == "BYTE"){
         return new Byte();
     } else {
         return new Num();
     }
//    if(exp1->getType() == BYTE_ENUM){
//        v1 = dynamic_cast<Byte*>(exp1)->getValue();
//    } else {
//        v1 = dynamic_cast<Num*>(exp1)->getValue();
//    }
//
//    if(exp2->getType() == BYTE_ENUM){
//        v2 = dynamic_cast<Byte*>(exp2)->getValue();
//    } else {
//        v2 = dynamic_cast<Num*>(exp2)->getValue();
//    }
//    string b = dynamic_cast<Relop*>(BINOP)->getRelop();

  //  delete(exp1);
  //  delete(exp2);
  //  delete(BINOP);
//
//    if(b == "+"){
//        if (type == INT_ENUM){
//            Num* n = new Num();
//            n->setValue(v1+v2);
//            return n;
//
//        } else {
//            Byte* b = new Byte();
//            b->setValue(v1+v2);
//            return b;
//        }
//    } else if (b == "-"){
//        if (type == INT_ENUM){
//            Num* n = new Num();
//            n->setValue(v1-v2);
//            return n;
//
//        } else {
//            Byte* b = new Byte();
//            b->setValue(v1-v2);
//            return b;
//        }
//    } else if (b == "*"){
//        if (type == INT_ENUM){
//            Num* n = new Num();
//            n->setValue(v1+v2);
//            return n;
//
//        } else {
//            Byte* b = new Byte();
//            b->setValue(v1*v2);
//            return b;
//        }
//    }
}

Node *semantics40(Node *str) {
   // cout<<"in 40"<<endl;
    String* s = dynamic_cast<String*>(str);
    Expression* e = new Expression(s->getStr(), "STRING");
    //
    e->setTypes("STRING");
    //
    return e;
}

Node *semantics34(Node *lparen, Node *exp, Node *rparen) {
    return exp;
}

Node *semantics36(Node *id,DataStructures* tables) {
   // cout<<"exp->id"<<endl;
    string type = getIdType(id, tables);
    id->setTypes(type);
    return id;
}

Node *semantics37(Node *call) {
   // cout<<"in 37"<<endl;

    return call;
}

Node* semantics28(Node *id, DataStructures* tables,vector<string>* functionArgs) {
    Id* i = dynamic_cast<Id*>(id);
    vector<string>* args = new vector<string>();
    list<Symbol*>* s = getFunctionsArgs(id, tables,functionArgs); // search if id exists
    if(!s->empty()){
        output::errorPrototypeMismatch(yylineno, i->getIdName(), *args);
    }
    //return getFunctionRetType(id, tables);
    string retType = getFunctionRetType(id,tables);
    Expression* expression= new Expression();
    expression->setTypes(retType);
    return expression;


}

Node *semantics29(Node *exp) {
   // cout<<"in 29"<<endl;
    return exp;
}

Node *semantics30(Node *exp, Node *COMMA, Node *explist) {
  //  Expression* e1 = dynamic_cast<Expression*>(exp);
   // Expression* e2 = dynamic_cast<Expression*>(explist);

    list<string>* l1 = exp->getTypes();


    list<string>* l2 = explist->getTypes();

    list<string>* temp = combineLists(l1, l2);

    exp->setTypesList(temp);

   // list<string>* temp = combineLists(e1->getTypes(), e2->getTypes());
   // Expression* expression = new Expression(e1->getId(), e1->getExpType(), temp);
 //   delete(exp);
 //   delete(explist);
  //  delete(COMMA);
    return exp;
}

Node* semantics27(Node *id, Node *lparen, Node *explist, Node *rparen, DataStructures* tables, vector<string>* args) {
    //Expression* e = dynamic_cast<Expression*>(explist);
   // cout<<"dynamic cast"<<endl;
    list<string>* types = explist->getTypes();

    list<Symbol*>* s = getFunctionsArgs(id, tables, args);
    Id* i = dynamic_cast<Id*>(id);
    list<string>* arguments = new list<string>();

    if(i->getIdName() != "print" && i->getIdName()!="printi"){
        string type_list = getIdType(id,tables);
        //type lis is (BOOL,INT,INT)->VOID . break the type list
        cout<<type_list<<endl;
        int pos = type_list.find(")");      // position of "live" in str

        string ret_type = type_list.substr(1,pos-1);
        int len = ret_type.size();
        string param_type;
        cout<<ret_type<<endl;
        pos = 0;

        while(pos<len){
            pos = ret_type.find(",");
            param_type = ret_type.substr(0,pos);
            ret_type = ret_type.substr(pos+1, len-1);
            len = ret_type.size();

            arguments->push_back(param_type);
            cout<<param_type<<endl;


        }
        arguments->push_back(ret_type);
    }


    //cout<<"ofree: "<< symbol->getType()<<endl;

    // cout<<"create s"<<endl;

    checkValidArgs(types,id, arguments); //throw error if mismatch
  //  cout<<"valid args"<<endl;

    //find the function in the symbol table
    //get the retType of the function
    //return New of this type
    //return getFunctionRetType(id,tables);
    string retType = getFunctionRetType(id,tables);

    cout<<retType<<endl;
    Expression* expression= new Expression();
    expression->setTypes(retType);
    return expression;


}

void semantics26(Node *cont, Node *sc, int* inWhile) {
    if(*inWhile == 0){
        output::errorUnexpectedContinue(yylineno);
        exit(0);
    }
}

void semantics25(Node *BREAK, Node *sc, int* inWhile) {
    cout<<"in whileeeeee " <<*inWhile<<endl;

    if(*inWhile == 0){
        output::errorUnexpectedBreak(yylineno);
        exit(0);
    }
}

void semantics18(Node *call, Node *sc) {
  //  delete(call);
}

void semantics17(Node *id, Node *assign, Node *exp, Node *sc,DataStructures* tables) {
    checkLegalAssignment(id,exp,tables);
  //  delete(id);
  //  delete(exp);
}

void semantics16(Node *type, Node *id, Node *assign, Node *exp, Node *sc, DataStructures* tables) {
    cout<<"Semantics 16"<<endl;
    searchIfPreDefined(id, tables);

    TypesEnum t = dynamic_cast<Type*>(type)->getType();

    string typeString = type->getTypeAsString(t);

    string name = dynamic_cast<Id*>(id)->getIdName();

    checkLegalAssignmentWhenTypeGiven(type,exp);

    int offset;
    if(!tables->getOffsetsTable()->empty()){
       offset = tables->getOffsetsTable()->top();
    }else{
        offset = 0;
    }
    tables->getOffsetsTable()->pop();
    tables->getOffsetsTable()->push(offset+1);

    Symbol* new_symbol = new Symbol(typeString, offset ,name );
    tables->pushNewSymbol(new_symbol);

    //checkLegalAssignmentWhenTypeGiven(type,exp);

    //  delete(id);
  //  delete(exp);
  //  delete(type);

}

void semantics19(Node *ret, Node *sc, DataStructures *tables) {
    string returnType = getFunctionRetTypeFromTable(tables);
    cout<<returnType<<endl;
    int pos = returnType.find("->");      // position of "live" in str

    string ret_type = returnType.substr(pos+2, returnType.size());
    cout<<ret_type<<endl;

    if (ret_type != "VOID") {
        output::errorMismatch(yylineno);
        exit(0);
    }
   // delete(ret);
}

void semantics20(Node *ret, Node *exp, Node *sc, DataStructures *tables) {
    string returnType = getFunctionRetTypeFromTable(tables);
    int pos = returnType.find("->");      // position of "live" in str

    string ret_type = returnType.substr(pos+2, returnType.size());
    cout<<ret_type<<endl;

    if (ret_type == "VOID") {
        output::errorMismatch(yylineno);
        exit(0);
    }
  //  delete(ret);
 //   delete(exp);
}

void semantics14(Node* statement){
 //   delete(statement);
}

void checkExpBoolFromExpression(Node* operand1, DataStructures* tables){
    Id* check = (dynamic_cast<Id*>(operand1));
    string type;
    if(!check){
        cout<<"check is not an id"<<endl;
        type = operand1->getTypeAsString(operand1->getType());
    } else {
        type = getIdType(operand1, tables);

    }


    //Bool* b = dynamic_cast<Bool*>(n);
    if(type != "BOOL"){
        output::errorMismatch(yylineno);
        exit(0);
    }
    cout<<"id name is "<<type<<endl;
    //if(check->getIdName() != "BOOL"){
    //    output::errorMismatch(yylineno);
     //   exit(0);
    //}
}


void semantics21(Node *exp, DataStructures* tables) {
    checkExpBoolFromExpression(exp, tables);
   // delete(exp);
}

void semantics22(Node *exp,DataStructures* tables) {
    checkExpBool(exp,tables);
 //   delete(exp);
}

void semantics23(Node *exp,DataStructures* tables, int* inWhile) {
    int i = *inWhile;
    i--;
    *inWhile = i;
    checkExpBool(exp,tables);
    //delete(exp);
}

void semantics24(Node *exp,DataStructures* tables, int* inWhile) {
    int i = *inWhile;
    i--;
    *inWhile = i;
    checkExpBool(exp,tables);
  //  delete(exp);
}





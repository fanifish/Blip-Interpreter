#ifndef _Blip_h
#define _Blip_h

#include "Parse.h"
#include "String.h"
#include "funcSymbol.h"


// runs the parser and executes the blip code
void run();
// handles text output to the string
void textHandler(String out);
// handles number output to the screen
void numHandler(int x);
// checks if a string is not an operator 
int isValidVarName(String name);
// handles a function call by creating a parameters vector and calls for the parsing of a function body
void functionHandler(tree& symbolTable, funcS& funcTable);
// evaluates the value of expressions including function calls
int evaluateOpFunc(opNode* exp, tree& symbolTable, tree& localVar, funcS& funcTable);
// used in evaluateOpFunc for calculating the appropriate value
int result(String ex, int x, int y);
// goes through every element in a vector of statments and executes each instruction
void evaluateif(String name, doVector& vec, tree& symbolTable, tree& localVar, funcS& funcTable);
// executes the body of an else statment
void evaluateElse(doVector& vec, tree& symbolTable, tree& localVar, funcS& funcTable);
// creates an image of all the statments inside functions , if statments and do statments
doVector* statmentOp(tree& symbolTable, tree& localVar, funcS& funcTable);
// executes every statment inside a function
void evaluateFunc(String name, tree& symbolTable, funcS& funcTable);
// creates an image of all the statments inside a main program
doVector* mainStatmentOp(tree& symbolTable, tree& localVar, funcS& funcTable);
// executes statments inside a main program
void evaluateMain(String name, doVector& vec, tree& symbolTable, tree& localVar, funcS& funcTable);
// parses the body of an else statment
doVector* elseStatmentOp(tree& symbolTable, tree& localVar, funcS& funcTable);
// temporary function declaration tree to indicate functions that were not declared yet
funcS tempFunc;
// signals a return statment
bool function_return = false;




#endif /*Blip*/

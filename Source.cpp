/* 
*
*Name Faniel Ghirmay
*Ut eid: ffg92 
*Project  9 Phase C  Blip programming language main Program
*
*/
#include "Blip.h"
#include "MemHeap.h"

int main(int argc, char* argv[]){

	printf("running %s\n", argv[1]); 
	set_input(argv[1]);
	run();	
/*				
	printf("running test2.blip\n"); 
	set_input("test2.blip");
	run();

	printf("running test3.blip\n"); 
	set_input("test3.blip");
	run();

	printf("running test4.blip\n"); 
	set_input("test4.blip");
	run();
	printf("running test5.blip\n"); 
	set_input("test5.blip");
	run();
	printf("running test6.blip\n"); 
	set_input("test6.blip");
	run();

	printf("running test7.blip\n"); 
	set_input("test7.blip");
	run();

	printf("running test8.blip\n"); 
	set_input("test8.blip");
	run();
	printf("running test9.blip\n");
	set_input("test9.blip");
	run();
	printf("running test10.blip\n");
        set_input("test10.blip");
        run();
        printf("running test11.blip\n");
        set_input("test11.blip");
        run();

        printf("running test12.blip\n");
        set_input("test12.blip");
        run();

        printf("running test13.blip\n");
        set_input("test13.blip");
        run();

        printf("running test14.blip\n");
        set_input("test14.blip");
        run();
        printf("running test15.blip\n");
        set_input("test15.blip");
        run();
*/
}
void run(){
	tree symbolTable;
	tree localVar; //dummy local variable
	funcS funcSymbolTable;
	peek_next_token();
	// creates  and executes an image of the whole program
	doVector* mainbody = mainStatmentOp(symbolTable, localVar, funcSymbolTable);
	evaluateMain("main" , *mainbody, symbolTable, localVar, funcSymbolTable);
	delete mainbody;
}
void textHandler(String out){
	const char * x = out.c_str();
	while(*x != 0){
		printf("%c", *x);
		x += 1;
	}	
}
void numHandler(int x){
	printf("%d", x);
}
int isValidVarName(String name){
	if(name == "&&"){return 0;}
	if(name == "||"){return 0;}
	if(name == ">="){return 0;}
	if(name == "<="){return 0;}
	if(name == "=="){return 0;}
	if(name == "+"){return 0;}
        if(name == "-"){return 0;}
        if(name == "*"){return 0;}
        if(name == "/"){return 0;}
        if(name == "%"){return 0;}
	if(name == ">"){return 0;}
        if(name == "<"){return 0;}
        if(name == "~"){return 0;}
        if(name == "!"){return 0;}
	if(name == "!="){return 0;}
	return 1;
}

doVector* statmentOp(tree& symbolTable, tree& localVar, funcS& funcTable){
	doVector* ifStatments;
	ifStatments = new doVector(20);// 20 default starting capacity
	opNode exp;
        read_next_token();
	if(String (next_token()) == "nufed"){return 0;}
	doVector::statment loop;
        while(String (next_token()) != "fi" || String(next_token()) != "od" || String (next_token()) != "nufed"){
		String next(next_token());
                if(next == "output"){
                        loop.c = output;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(next == "set"){
                        loop.c = set;
                        read_next_token();
                        loop.text = String (next_token());
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(next == "var"){
                        loop.c = var;
                        read_next_token();
                        loop.text = String (next_token());
                        loop.text = String (next_token());
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(next == "text"){
                        loop.c = text;
                        read_next_token();
                        loop.text = String (next_token());
                        ifStatments->push_back(loop);
                }else if(next == "do"){
                        loop.c = dos;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			loop.block = statmentOp(symbolTable, localVar, funcTable);
                        ifStatments->push_back(loop);
		}else if(next == "else"){
			loop.c = elses;
			loop.block = elseStatmentOp(symbolTable, localVar, funcTable);
			ifStatments->push_back(loop);
		}else if(next == "if"){
			loop.c = ifs;
		        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			loop.block = statmentOp(symbolTable, localVar, funcTable);
                        ifStatments->push_back(loop);
		}else if(next  == "call"){
			loop.c = call;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			ifStatments->push_back(loop);				
		}else if(next == "return"){
			loop.c = returns;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			ifStatments->push_back(loop);		
		}else if(next == "defun"){
			loop.c = func;
			peek_next_token();
			loop.text = String (next_token());
			ifStatments->push_back(loop);
			functionHandler(symbolTable, tempFunc);
		}
		peek_next_token();
		if(String (next_token()) == "fi" || String (next_token()) == "od" || String (next_token()) == "nufed" || next_token_type == END){  read_next_token(); break;}else{
        	read_next_token();
		}	
        }
	return ifStatments;
}
void functionHandler(tree& symbolTable, funcS& funcTable){
        tree localVar;
	param* parameter = new param(20);
	param::statment  in;
        read_next_token();
        String name(next_token());
        read_next_token();
        if(String(next_token()) == "params"){
                read_next_token();
		int i = 1;
               	while(String (next_token()) != "smarap"){// puts all the local variables in a local symbol table
                       	if(next_token_type == NAME){
				in.para = String (next_token());
				in.value = 0;
				parameter->push_back(in);
				i += 1;
                       	}
			read_next_token();		
		}
            }
        // after we got all the local variables set the function body
        funcTable.insert(name, 0 , statmentOp(symbolTable,  localVar, funcTable), 0 , parameter);
}
void evaluateif(String name, doVector& vec, tree& symbolTable, tree& localVar, funcS& funcTable){
	 for(int i = 0; i < vec.len(); i+=1){
                if(vec.op[i].c == output){
                     numHandler(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                }else if(vec.op[i].c == text){
                     textHandler(vec.op[i].text);
                }else if(vec.op[i].c == set){
			if(localVar.isMember(vec.op[i].text)){
                                localVar.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                        }else if(symbolTable.isMember(vec.op[i].text)){
                                symbolTable.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                        }else{
				localVar.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
				printf("variable %s not declared\n", vec.op[i].text.c_str());
                        }
                }else if(vec.op[i].c == ifs){
			if(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable)){
				evaluateif(name,*(vec.op[i].block), symbolTable, localVar, funcTable);
				if(function_return){
					return;
				}
			}else{
				evaluateElse(*(vec.op[i].block),symbolTable, localVar, funcTable);
				if(function_return){
					return;
				}		
			}
		}else if(vec.op[i].c == var){
			if(symbolTable.isMember(vec.op[i].text)){
				 printf("variable %s incorrectly re-initialized\n", vec.op[i].text.c_str());
			}
			symbolTable.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
		}else if(vec.op[i].c == dos){
			while(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable)){
                                evaluateif(name, *(vec.op[i].block), symbolTable, localVar, funcTable);
				if(function_return){
					return;
				}
                        }
		}else if(vec.op[i].c == call){
			evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable);
			if(function_return){return;}			
		}else if(vec.op[i].c == returns){
			funcTable.addVal(name, evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
			function_return = true;
			return;
		}else if(vec.op[i].c == func){
			if(funcTable.isMember(vec.op[i].text)){
                                printf("WARNING: function %s redefined \n", vec.op[i].text.c_str());
                        }
                        funcTable.addFunc(tempFunc, vec.op[i].text);
		}
		function_return = false;
        }
}
// skips to the else part of the statment
void evaluateElse(doVector& vec, tree& symbolTable, tree& localVar, funcS& funcTable){
	for(int j = 0; j < vec.len(); j += 1){
		if(vec.op[j].c ==  elses){
		      evaluateif("else", *(vec.op[j].block), symbolTable, localVar, funcTable);
			return;
		}
	}
}
void evaluateFunc(String name, tree& symbolTable, funcS& funcTable){
	if(!(funcTable.getBlock(name))){
		return; // if a function with no body
	}
	doVector vec = *(funcTable.getBlock(name));
	tree localVar = *(funcTable.getParams(name));
	 for(int i = 0; i < vec.len(); i+=1){
                if(vec.op[i].c == output){
                     numHandler(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                }else if(vec.op[i].c == text){
                     textHandler(vec.op[i].text);
                }else if(vec.op[i].c == set){
			if(localVar.isMember(vec.op[i].text)){// if the variable is a local variable
                        	localVar.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
			}else if(symbolTable.isMember(vec.op[i].text)){// else if it is local
				symbolTable.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
			}else{
				 printf("variable %s not declared\n", vec.op[i].text.c_str());
			}
                }else if(vec.op[i].c == ifs){
			if(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable)){
                                evaluateif(name, *(vec.op[i].block), symbolTable, localVar, funcTable);
				if(function_return){return;}
                        }
		}else if(vec.op[i].c == returns){
			funcTable.addVal(name, evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
			function_return = true;
			return;
		}else if(vec.op[i].c == dos){
			while(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable)){
                                evaluateif(name, *(vec.op[i].block), symbolTable, localVar, funcTable);
				if(function_return){return;}
                        }
		}else if(vec.op[i].c == var){
			if(localVar.isMember(vec.op[i].text)){
				 printf("variable %s incorrectly re-initialized\n", vec.op[i].text.c_str());	
			}
                     	localVar.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
		}else if(vec.op[i].c == call){
                        evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable);
                        if(function_return){return;}
		}else if(vec.op[i].c == func){
			if(funcTable.isMember(vec.op[i].text)){
				printf("WARNING: function %s redefined \n", vec.op[i].text.c_str());
			}
			funcTable.addFunc(tempFunc, vec.op[i].text);
		}
        }
	function_return = false;
	funcTable.addVal(name, 0);// if there is no return statment it returns 0
}
// 
//
//  calculates expressions stored in a parse Tree
//
// 
int evaluateOpFunc(opNode* exp, tree& symbolTable, tree& localVar, funcS& funcTable){
                int rights;
                int lefts ;
                String s = exp->stringOp();
                if(s == "NONE"){
                    return exp->val();
                }else if(isValidVarName(s)){// if s is not an operation
			if(s == "call"){
                                exp = exp->leftNode();
                                String funcName = exp->stringOp();// gets function name
				param* parameter;
				if(funcTable.isMember(funcName)){
                                	 parameter = funcTable.getParameters(funcName);// passing arguments
				}else{

					printf("WARNING: Function %s is not declared \n", funcName.c_str());
					return 0;
				}
				int i = 0;
				opNode* params = exp->leftNode();
				if(params->stringOp() != "Ecall"){
					while(params->stringOp() != "Ecall"){
						parameter->op[i].value = evaluateOpFunc(params->rightNode(), symbolTable, localVar, funcTable);
						params = params->leftNode();
						i += 1;	
					}
				}
				tree* newTree = new tree;
			        for(int j =0; j < i ; j+=1){
                			newTree->insert(parameter->op[j].para, parameter->op[j].value);
        			}
				if(funcTable.isMember(funcName)){
        				funcTable.addLocalVar(funcName, newTree);
					evaluateFunc(funcName, symbolTable, funcTable);
                                	return  funcTable.getVal(funcName);
				}else{

					printf("Warning: function %s is not declared \n", funcName.c_str());
				}		
                        }
			if(localVar.isMember(s)){
                        	return localVar.getVal(s);
			}else if(symbolTable.isMember(s)){
				return symbolTable.getVal(s);
			}
                }
                if(exp->leftNode()){
                         lefts = evaluateOpFunc(exp->leftNode(), symbolTable, localVar, funcTable);
			if(s == "~" || s == "!"){return result(s, lefts, rights);}
                }
		if(exp->rightNode()){
                         rights = evaluateOpFunc(exp->rightNode(), symbolTable, localVar, funcTable);
                }
                return result(s,lefts,rights);
}

int result(String ex, int x, int y){	
        if(ex == "&&"){return x && y;}
	if(ex == "||"){return x || y;}
	if(ex == ">="){return x >= y;}
	if(ex == "<="){return x <= y;}
	if(ex == "=="){return x == y;}
	if(ex == "+"){return x + y;}
        if(ex == "-"){return x - y;}
        if(ex == "*"){return x * y;}
        if(ex == "/"){return x / y;}
        if(ex == "%"){return x % y;}
	if(ex == ">"){return x > y;}
        if(ex == "<"){return x < y;}
        if(ex == "~"){return -x;}
        if(ex == "!"){return !x;}
	if(ex == "!="){return x != y;}
	return 0;
}

//
//
// This function creates an image of the main program and returns a pointer to the block of statments
//
//
//
doVector* mainStatmentOp(tree& symbolTable, tree& localVar, funcS& funcTable){
	doVector* ifStatments;
	ifStatments = new doVector(20);// 20 default starting capacity
	opNode exp;
	peek_next_token();
	if(String (next_token()) != "call"){
        	read_next_token();
	}
	doVector::statment loop;
        while(next_token_type != END){
               	 if(String(next_token()) == "output"){
                        loop.c = output;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(String(next_token()) == "set"){
                        loop.c = set;
                        read_next_token();
                        loop.text = String (next_token());
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(String(next_token()) == "var"){
                        loop.c = var;
                        read_next_token();
                        loop.text = String (next_token());
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(String(next_token()) == "text"){
                        loop.c = text;
                        read_next_token();
                        loop.text = String (next_token());
                        ifStatments->push_back(loop);
                }else if(String (next_token()) == "do"){
                        loop.c = dos;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			loop.block = statmentOp(symbolTable, localVar, funcTable);
                        ifStatments->push_back(loop);
		}else if(String (next_token()) == "else"){
			loop.c = elses;
			loop.block = elseStatmentOp(symbolTable, localVar, funcTable);
			ifStatments->push_back(loop);
		}else if(String (next_token()) == "if"){
			loop.c = ifs;
		        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			loop.block = statmentOp(symbolTable, localVar, funcTable);
                        ifStatments->push_back(loop);
		}else if(String (next_token())  == "call"){
			loop.c = call;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			ifStatments->push_back(loop);						
		}else if(String (next_token()) == "defun"){
			loop.c = func;
			functionHandler(symbolTable, funcTable);
		}else if(String (next_token()) == "return"){
                        loop.c = returns;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
		}
		peek_next_token();
		if(String (next_token()) != "call"){
			read_next_token();
		}
        }
	return ifStatments;

}

void evaluateMain(String name, doVector& vec, tree& symbolTable, tree& localVar, funcS& funcTable){
	 for(int i = 0; i < vec.len(); i+=1){
                if(vec.op[i].c == output){
                     numHandler(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                }else if(vec.op[i].c == text){
                     textHandler(vec.op[i].text);
                }else if(vec.op[i].c == set){
			if(localVar.isMember(vec.op[i].text)){
                                localVar.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                        }else if(symbolTable.isMember(vec.op[i].text)){
                                symbolTable.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
                        }else{
				symbolTable.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
				printf("variable %s not declared\n", vec.op[i].text.c_str());
                        }
                }else if(vec.op[i].c == ifs){
			if(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable)){
				evaluateif(name,*(vec.op[i].block), symbolTable, localVar, funcTable);
			}else{
				evaluateElse(*(vec.op[i].block),symbolTable, localVar, funcTable);		
			}
		}else if(vec.op[i].c == var){
			if(symbolTable.isMember(vec.op[i].text)){
				 printf("variable %s incorrectly re-initialized\n", vec.op[i].text.c_str());
			}
			symbolTable.insert(vec.op[i].text,evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
		}else if(vec.op[i].c == dos){
			while(evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable)){
                                evaluateif(name, *(vec.op[i].block), symbolTable, localVar, funcTable);
                        }
		}else if(vec.op[i].c == call){
			evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable);	
		}else if(vec.op[i].c == returns){
			funcTable.addVal(name, evaluateOpFunc(vec.op[i].operate, symbolTable, localVar, funcTable));
			function_return = false;
			return;
		}else if(vec.op[i].c == func){
			
		}
		function_return = false;
        }
}
doVector* elseStatmentOp(tree& symbolTable, tree& localVar, funcS& funcTable){
	doVector* ifStatments;
	ifStatments = new doVector(20);// 20 default starting capacity
	opNode exp;
        read_next_token();
	doVector::statment loop;// temporary place holder of the elements to be pushed to the vector
        while(String (next_token()) != "fi"){
		String next(next_token());
                if(next == "output"){
                        loop.c = output;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(next == "set"){
                        loop.c = set;
                        read_next_token();
                        loop.text = String (next_token());
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(next == "var"){
                        loop.c = var;
                        read_next_token();
                        loop.text = String (next_token());
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
                        ifStatments->push_back(loop);
                }else if(next == "text"){
                        loop.c = text;
                        read_next_token();
                        loop.text = String (next_token());
                        ifStatments->push_back(loop);
                }else if(next == "do"){
                        loop.c = dos;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			loop.block = statmentOp(symbolTable, localVar, funcTable);
                        ifStatments->push_back(loop);
		}else if(next == "else"){
			loop.c = elses;
			loop.block = statmentOp(symbolTable, localVar, funcTable);
			ifStatments->push_back(loop);
		}else if(next == "if"){
			loop.c = ifs;
		        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			loop.block = statmentOp(symbolTable, localVar, funcTable);
                        ifStatments->push_back(loop);
			loop.c = call;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			ifStatments->push_back(loop);				
		}else if(next == "return"){
			loop.c = returns;
                        exp.parseOperateTemp(String (next_token()), 0,  symbolTable, loop.operate);
			ifStatments->push_back(loop);		
		}else if(next == "defun"){
			loop.c = func;
			peek_next_token();
			loop.text = String (next_token());
			ifStatments->push_back(loop);
			functionHandler(symbolTable, tempFunc);
		}
		peek_next_token();
		if(String (next_token()) == "fi"){  break;}else{
        		read_next_token();
		}	
        }
	return ifStatments;
}

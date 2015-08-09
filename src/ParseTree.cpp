#include <stdio.h>
#include <stdlib.h>
#include "ParseTree.h"
#include "Parse.h"
#include "MemHeap.h"
// Reads Expressions and performs the approprate commands and uses a parse tree to perform the process
void  opNode::parseOperateTemp(String x, int value, tree& var, opNode*& parse){
	peek_next_token();
	String s(next_token());
	if(s == "output"){ return; }
	if(s == "text"){ return; }	
	if(s == "var"){ return; } 
        if(s == "set"){ return; }
	if(s == "fi"){return ;}
	if(s == "else"){return;}
	if(s == "od") {return;}
	if(s == "if"){return;}
	if(s == "do"){return;}
	if(s == "defun"){return;}
	if(s == "sgra"){return;}
		if(String (next_token()) == "call"){// special function call parsing keep saving call statments to the left parser
                      parse  = new opNode;
                      opNode* p = parse;
                      read_next_token();
                      String s(next_token());
                      p->operation = s; // save the instruction call
                      p->value = 0;
                      p->left = new opNode;
                      read_next_token();
                      p = p->left;
                      p->operation = String (next_token()); // save name of the called function
                      p->value = 0;
                      read_next_token();
                      p->left = new opNode;
                      p = p->left;
                      peek_next_token();
                      while(String (next_token()) != "sgra"){ // save the parameters
                            parseOperateTemp(String (next_token()), 0, var, p->right);// save the expression to the right:
                            p->left = new opNode;
                            p = p->left;
                            peek_next_token();
                            if(String (next_token()) == "sgra"){
                                break;
                            }
                       }
			read_next_token();
                       	p->operation = "Ecall";
                        return;
                }
		if(String (next_token()) == "od"){ return; }else{ read_next_token();}
		String none("NONE");
		parse = new opNode;

		if(next_token_type == SYMBOL){
			parse->operation = String(next_token());
			parse->value = 0;
			parseOperateTemp(String (next_token()), 0, var, parse->left);
			if(s == "~" || s == "!"){
				return;
			}
			peek_next_token();
			if(next_token_type == NUMBER){
				parseOperateTemp(none, token_number_value, var, parse->right);
			}else if(next_token_type == NAME){

				if(String (next_token()) == "call"){// special function call parsing keep saving call statments to the left parser
                        	parse->right = new opNode;
				opNode* p = parse->right;
                        	read_next_token();
                        	String s(next_token());
                        	p->operation = s; // save the instruction call
                        	p->value = 0;
                        	p->left = new opNode;
                        	read_next_token();
                        	p = p->left;
                        	p->operation = String (next_token()); // save name of the called function
                        	p->value = 0;
				read_next_token();
				p->left = new opNode;
				p = p->left;
				peek_next_token();
                        	while(String (next_token()) != "sgra"){ // save the parameters
                                	parseOperateTemp(String (next_token()), 0, var, p->right);// save the expression to the right:
					p->left = new opNode;
					p = p->left;
					peek_next_token();
                                        if(String (next_token()) == "sgra"){
                                                break;
                                        }
                           //     	read_next_token();
                        	}
				p->operation = "Ecall";
                        	return;
                	}

			        parseOperateTemp(none, var.getVal(next_token()), var, parse->right);
			}else if(next_token_type == SYMBOL){
	          	        parseOperateTemp(String (next_token()), 0, var, parse->right);
				
			}
		 }else if(next_token_type == NUMBER){
			parse->operation = none;
			parse->value = token_number_value;
			return;					
                }else if(next_token_type == NAME){
			if(String (next_token()) == "call"){// special function call parsing keep saving call statments to the left parser
				opNode* p = parse;
                        	read_next_token();
                        	String s(next_token());
                        	p->operation = s; // save the instruction call
                        	p->value = 0;
                        	p->left = new opNode;
                        	read_next_token();
                        	p = p->left;
                        	p->operation = String (next_token()); // save name of the called function
                        	p->value = 0;
				read_next_token();
                                p->left = new opNode;
                                p = p->left;
                                peek_next_token();
                                while(String (next_token()) != "sgra"){ // save the parameters
                                        parseOperateTemp(String (next_token()), 0, var, p->right);// save the expression to the right:
                                        p->left = new opNode;
                                        p = p->left;
                                        peek_next_token();
                                        if(String (next_token()) == "sgra"){
                                                break;
                                        }
                                }
                                p->operation = "Ecall";
                                return;

                	}	

				parse->operation = String (next_token());
                        	parse->value = var.getVal(next_token());
				return;
                }
}
int opNode::expReturn(String ex, int x, int y){
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
        return 0;
}


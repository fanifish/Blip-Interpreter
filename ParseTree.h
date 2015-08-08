#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"

// Struct opNode for expression parsing

struct opNode{
private:
	String operation;
	opNode* left;
	opNode* right;
	int value;
	int expReturn(String ex, int x, int y);
	void destroy(opNode* root){// recursive destroy
		if(!root){return;}
		destroy(root->left);
		destroy(root->right);
		delete root;
	}
public:
	opNode(void){
		operation = "";
		left = 0;
		right = 0;		
	}
	opNode(char x){
		operation = String (&x);
		left = 0;
		right = 0;
	}
	~opNode(void){
		destroy(this->left);
		destroy(this->right);
	}
	void  parseOperateTemp(String x, int value, tree& var, opNode*& parse);
 
	String stringOp(){
		return operation;
	}
	opNode* leftNode(){
		return left;
	}
	opNode* rightNode(){
		return right;
	}
        int val(){
		return value;
	}
	void setOp(String x){
		operation = x;
	}
};

// The enum comman holds all the instruction type indicators
enum Command{text,output,var,set,dos,ifs,elses, returns, call, func};



/*
	doVector struc is mainly for holding a block of statments that can also point to another block of statments

*/
struct doVector{
    uint32_t length;
    uint32_t capacity;
    struct statment{
        Command c;  // holds the type of command to be performed
        opNode* operate; // points to an expression tree
        doVector* block; // points to a block of statments if c is an if or do statment bock points to the body of the statments
        String text; // holds name of a function call or a variable to be set or assigned
	void destroy(){
	//	if(operate){delete operate;}
	//	if(block){delete block;}
	}
	public:
		statment(void){
			operate = 0;
			block = 0;
		}
		~statment(void){
			   destroy();
		}
    };
    statment* op; 
    void copy(const doVector& x) {
        this->length = x.length;
        this->capacity = x.length;
        if (x.length == 0) { this->op = nullptr; }
        else {
	    this->op = new statment[this->capacity];
        }
        for (uint32_t k = 0; k < x.length; k += 1) {
	    this->op[k] = x.op[k]; 
        }
    }
    void destroy(void) {
	delete[] this->op;
    }
public:
   doVector(void) {
        length = 0;
        capacity = 0;
	op = nullptr;
    }
    doVector(const doVector& that) {
        copy(that);
    }

    ~doVector(void) {
        destroy();
    }

    doVector& operator=(const doVector& that) {
        if (this != &that) { 
            destroy();
            copy(that);
        }
        return *this;
    }


    doVector(uint32_t sz) {
        if (sz == 0) {
            this->length = 0;
            this->capacity = 0;
            this->op = nullptr;
	}else{
		this->length = 0;
		this->capacity = sz;
		this->op = new statment[sz];
	}
    }
    void push_back(statment& s) {
     if (this->capacity == length) {
        capacity *= 2;
        if (capacity == 0) { capacity = 1; }
        statment* p = new statment[capacity];
        for (uint32_t k = 0; k < length; k += 1) {
            p[k] = op[k];	
        }
        delete[] op;
        op = p;
    }
    this->op[this->length] = s;
         length += 1;
    }
    void pop_back(void) {
        assert(length != 0);
        length -= 1;
    }
    int len(){
		return length;
	}
    int cap(){return capacity;}
    void addBlock(doVector* in){// adding blocks to statments
	     op->block = in;
    }
    doVector* statmentBlock(){
	 return op->block;
    }
};







// a parameter struct is Used as a vector for parameter passing to reserve the order of the parameter passing eventually all parameters are on 
// The BST 
struct param{

    uint32_t length;
    uint32_t capacity;
    struct statment{
       	String para;// name of the parameter variable
	int32_t value;// The value stored by the parameter
    };
    statment* op; 
    void copy(const param& x) {
        this->length = x.length;
        this->capacity = x.length;
        if (x.length == 0) { this->op = nullptr; }
        else {
	    this->op = new statment[this->capacity];
        }

        for (uint32_t k = 0; k < x.length; k += 1) {
	    this->op[k] = x.op[k]; 
        }
    }

    void destroy(void) {
	delete[] this->op;
    }
public:
   param(void) {
        length = 0;
        capacity = 0;
	op = nullptr;
    }
    param(const param& that) {
        copy(that);
    }

    ~param(void) {
        destroy();
    }

    param& operator=(const param& that) {
        if (this != &that) { 
            destroy();
            copy(that);
        }
        return *this;
    }


    param(uint32_t sz) {
        if (sz == 0) {
            this->length = 0;
            this->capacity = 0;
            this->op = nullptr;
	}else{
		this->length = 0;
		this->capacity = sz;
		this->op = new statment[sz];
	}
    }
    void push_back(statment& s) {
     if (this->capacity == length) {
        capacity *= 2;
        if (capacity == 0) { capacity = 1; }
        statment* p = new statment[capacity];
        for (uint32_t k = 0; k < length; k += 1) {
            p[k] = op[k];	
        }
        delete[] op;
        op = p;
    }
    this->op[this->length] = s;
         length += 1;
    }
    void pop_back(void) {
        assert(length != 0);
        length -= 1;
    }
    int len(){
		return length;
	}
    int cap(){return capacity;}
    

};

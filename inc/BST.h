#include <stdio.h>
#include "String.h"
#include <stdlib.h>
struct tree{
private:
	String key;
	int32_t value;
	tree* bigger;
	tree* smaller;
	void recursiveDelete(){
		if(!this){return;}
    		this->bigger->recursiveDelete();
    		this->smaller->recursiveDelete();
		delete this->bigger;
		delete this->smaller;
	}
public:
	tree(void){   // initializes an empty tree
		key = ""; 
		value = 0;
		bigger = 0;
		smaller = 0;
	}
	~tree(void){
//		recursiveDelete();
	}
	void insert(String x, int32_t val){// put 
		if(this->key == ""){
			this->key = x;
			this->value = val;
			this->bigger = 0;
			this->smaller = 0;
			return;
		}else if(x < this->key){
			if(this->smaller == 0){
				this->smaller = new tree;
			}
			(*(this->smaller)).insert(x, val);
	
		}else if(x > this->key){
			if(this->bigger == 0){
				this->bigger = new tree;
			}
			(*(this->bigger)).insert(x, val);
		}else if(x == this->key){
			this->key = x;
			this->value = val;
		}				
	}
	bool isMember(String x){
		bool result = false;
		if(this->key == ""){return false;}// empty tree
		if(this->key == x){return true;}
		else if(x < this->key){
			if(this->smaller == 0){return false; }
			else{
				result = (*(this->smaller)).isMember(x);
			}
		}else if(x > this->key){
                        if(this->bigger == 0){return false;}
                        else{
                                result = (*(this->bigger)).isMember(x);
                        }
                }
		return result;
	}
	int32_t getVal(String x){
		if(this->key == ""){
			return 0;// returns empty tree
		}
		if(x < this->key && this->smaller != 0){
			return this->smaller->getVal(x);
		}else if(x > this->key && this->bigger != 0){
			return this->bigger->getVal(x);
		}else if(x == this->key){
			return this->value;
		}
		return 0;
	}
	int32_t getVal(tree* x){
		return x->value;
	}
};



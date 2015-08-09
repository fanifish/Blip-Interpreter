#include "ParseTree.h"
#include <stdlib.h>

struct funcS{
private:
	String key;
	int32_t value;// used for return value
	doVector* func;
	param* parameters;
	tree* locals;
	funcS* bigger;
	funcS* smaller;
public:
	funcS(void){   // initializes an empty tree
		key = ""; 
		value = 0;
		bigger = 0;
		smaller = 0;
	}
	~funcS(void){
		delete this->bigger;
		delete this->smaller;
	}

	void insert(String x, int32_t val, doVector* in, tree* params, param* pIn){// put 
		if(this->key == ""){
			this->key = x;
			this->value = val;
			this->func = in;
			this->parameters = pIn;
			this->locals = params;
			this->bigger = 0;
			this->smaller = 0;
			return;
		}else if(x < this->key){
			if(this->smaller == 0){
				this->smaller = new funcS;
			}
			(*(this->smaller)).insert(x, val, in, params, pIn);
	
		}else if(x > this->key){
			if(this->bigger == 0){
				this->bigger = new funcS;
			}
			(*(this->bigger)).insert(x, val, in, params, pIn);
		}else if(x == this->key){
			this->key = x;
			this->value = val;
			this->func = in;
                        this->parameters = pIn;
                        this->locals = params;
		}
		// balancing the tree		
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
	int32_t getVal(funcS* x){
		return x->value;
	}
	funcS* smallest(){
		if(this->key == ""){
			return this;
		}else if(this->smaller){
			return this->smaller->smallest();
		}else{
			return this;
		}
		return 0;
	}
	doVector* getBlock(String x){
		if(this->key == ""){
                        return 0;// returns empty tree
                }
                if(x < this->key && this->smaller != 0){
                        return this->smaller->getBlock(x);
                }else if(x > this->key && this->bigger != 0){
                        return this->bigger->getBlock(x);
                }else if(x == this->key){
                        return this->func;
                }
                return 0;

	}
	tree* getParams(String x){
		if(this->key == ""){
                        return 0;// returns empty tree
                }
                if(x < this->key && this->smaller != 0){
                        return this->smaller->getParams(x);
                }else if(x > this->key && this->bigger != 0){
                        return this->bigger->getParams(x);
                }else if(x == this->key){
                        return this->locals;
                }
                return 0;
	}
	void addVal(String x, int val){
		if(this->key == ""){
                        return;// returns empty tree
                }
                if(x < this->key && this->smaller != 0){
                        this->smaller->addVal(x, val);
                }else if(x > this->key && this->bigger != 0){
                        this->bigger->addVal(x, val);
                }else if(x == this->key){
                        this->value = val;
                }
                return;
	}
	void addLocalVar(String x, tree* localVar){
		if(this->key == ""){
                        return;// returns empty tree
                }
                if(x < this->key && this->smaller != 0){
                        this->smaller->addLocalVar(x, localVar);
                }else if(x > this->key && this->bigger != 0){
                        this->bigger->addLocalVar(x, localVar);
                }else if(x == this->key){
                        this->locals = localVar;
                }
                return;
	}
	param* getParameters(String x){
		if(this->key == ""){
                        return 0;// returns empty tree
                }
                if(x < this->key && this->smaller != 0){
                        return this->smaller->getParameters(x);
                }else if(x > this->key && this->bigger != 0){
                        return this->bigger->getParameters(x);
                }else if(x == this->key){
                        return this->parameters;
                }
                return 0;
	}
	void addFunc(funcS& temp, String name){
		
		insert(name, temp.getVal(name), temp.getBlock(name), temp.getParams(name), temp.getParameters(name));
	}

};

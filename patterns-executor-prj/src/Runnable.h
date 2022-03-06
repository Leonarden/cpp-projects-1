
#ifndef RUNNABLE_H_
#define RUNNABLE_H_


#include "Meta.h"

class Runnable:public Meta {
public:
	Runnable(const char* name, const char* type, const char* description):Meta(name,type,description){}
	virtual ~Runnable() {}
	virtual int run(char* args, int argc){ return 0;}
    virtual int run(){ return 0;}
};


#endif

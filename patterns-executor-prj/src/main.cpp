//============================================================================
// Name        : practice-6.cpp
// Author      : david
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "mediator.h"
#include "state.h"
#include "strategy.h"
#include "visitor.h"
#include "templatemethod.h"
#include "observer.h"
#include "command.h"
#include <string>
#include <string.h>
#include "Log.h"
#include "Executor.h"

using namespace std;

/*
int main() {

	 LOG::LOGCFG.headers= true;
	 LOG::LOGCFG.level = DEBUG;

	 LOG logger;






	 //---------------------------
	    string a = " Hello ";
	    logger << a ;


	    a = +  " from Debug ";

	    logger << a;

}
*/

Runnable * createOne(string  n){
	Runnable * r = NULL;
	string name = "";
	string type = "";
	string desc = "";
	if(n == "Mediator"){
		name = "Mediator";
		type = "Behavioural";
		desc = "Allows you connect n with m";
		r = new MediatorRun(name.c_str(),type.c_str(),desc.c_str());
		return r;
	}
	if( n== "State"){
		name = "State";
		type = "Behavioural";
		desc = " Execution of different states";
		r = new StateRun(name.c_str(),type.c_str(),desc.c_str());
		return r;
	}
	if( n== "Strategy"){
			name = "Strategy";
			type = "Behavioural";
			desc = " Execution of context executes different algorithms that share same interface";
			r = new StrategyRun(name.c_str(),type.c_str(),desc.c_str());
			return r;
		}

	if( n== "Visitor"){
				name = "Visitor";
				type = "Behavioural";
				desc = " Visitor allows apply uniform treatment to different interface objects";
				r = new VisitorRun(name.c_str(),type.c_str(),desc.c_str());
				return r;
			}

  	if( n== "TemplateMethod"){
					name = "TemplateMethod";
					type = "Behavioural";
					desc = " Changes a part of an algorithm by subclassing";
					r = new TemplateMethodRun(name.c_str(),type.c_str(),desc.c_str());
					return r;
				}

	if( n== "Observer"){
					name = "Observer";
					type = "Behavioural";
					desc = " Allows communication one to many between a subject and its observers";
					r = new ObserverRun(name.c_str(),type.c_str(),desc.c_str());
					return r;
	}

	if( n== "Command"){
						name = "Command";
						type = "Behavioural";
						desc = " Loose coupled execution of commands ";
						r = new CommandRun(name.c_str(),type.c_str(),desc.c_str());
						return r;
		}

	return r;

}




vector<Runnable*> * create(vector<string> & names) {
	vector<string>::iterator it;
	vector<Runnable*>* runnables = new vector<Runnable*>;
	for(it=names.begin();it<names.end();it++){
     if((*it) != ""){
    	 Runnable * r =	createOne(*it);
    	 if(r)
    		 runnables->push_back(r);
     	 }
    }

	return runnables;
}


int main() {
vector<Runnable *> *patterns;
vector<string> names;
vector<int> rindex;
//1
string pn = "Mediator";
names.push_back(pn);
//2
pn = "State";
names.push_back(pn);
//3
pn = "Strategy";
names.push_back(pn);
//4
pn = "Visitor";
names.push_back(pn);

//5
pn = "TemplateMethod";
names.push_back(pn);
//6
pn = "Observer";
names.push_back(pn);
//7
pn = "Command";
names.push_back(pn);

patterns = create(names);

Executor exec(patterns);

int i = 0;
	while(1) {
		for(int j=0;j<names.size();j++)
			cout << j+1 << ": " << names[j] << endl;
		cout << "Select a number: (10 to end selection,11 to execute all) " << endl;
		cin >> i;
		if(i<=0 || i==10 || i==11)
			break;
		else if(i > names.size())
			continue;
		else {
			rindex.push_back(i-1);
		}
	}
   if((i<=0 || i==10) && rindex.size()>0){

	   cout << "Executing selection" << endl;

	   exec.execute(rindex);
   }
   else if(i==11){
	   cout << "Executing all" << endl;
	   exec.executeAll();

   }

cout << "Ending application" << endl;

	return 0;
}



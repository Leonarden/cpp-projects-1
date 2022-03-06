/*
 * Executor.cpp
 *
 *  Created on: Jul 25, 2021
 *      Author: david
 */

#include "Executor.h"

Executor::Executor() {
	// TODO Auto-generated constructor stub

}

Executor::Executor(vector<Runnable*> * runs) {
	_runnables = runs;

}

Executor::~Executor() {
	// TODO Auto-generated destructor stub
}

//Executor::logger;

int Executor::execute(vector<int> index) {
    Runnable *r;
	int status = -1;
	vector<int>::iterator it;
	for(it=index.begin();it<index.end();it++){

		r = this->_runnables->at((*it));
		logger << "--------------"<< " ";
		logger << r->getName() << " ";
		logger << "--------------"<< " ";
		string s = "";
		s = r->getType();
		logger << s << "" << " ";
		logger << "--------------"<< " ";
		s = r->getDescription();
		logger << s << "" << " ";
		logger <<" Running..."<< " ";
    	try{

    		status = r->run();

    		status = 0;

    		logger << "...End running"<< ":status="<< status << " ";

    	}catch(int e){
    		status = e;
    		logger.LOGCFG.level = ERROR;
    		logger << "An error ocurred" << " ";
    		logger.LOGCFG.level = DEBUG;

    	}

	}//for



	return status;

}

int Executor::executeAll(){
	vector<int> v;
	for(int i=0;i<this->_runnables->size();i++)
		v.push_back(i);
	return execute(v);
}

